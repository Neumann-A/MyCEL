#pragma once

//#include <gtest/gtest.h>

#include <iostream>

#include "../basics/BasicMacros.h"

#include <Eigen/Core>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_blas.h>

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment (lib, "gsld")
#pragma comment (lib, "gslcblasd")
#else
#pragma comment (lib, "gsl")
#pragma comment (lib, "gslcblas")
#endif
#endif


template<class Func,class FuncJacobi, class FuncJacobiFunc>
struct Evaluators
{
	Func f;
	FuncJacobi df;
	FuncJacobiFunc fdf;
};

enum class gsl_solver_type {undefined, newton, gnewton, hybridsj, hybridj};

template <typename prec>
class GSL_Implicit_Solver
{

public:
	using Precision = prec;

	GSL_Implicit_Solver(Precision abserr, Precision relerr, std::size_t maxiter, std::size_t dims, gsl_solver_type gslsolvertype) 
		: AbsErrorGoal(abserr), RelErrorGoal(relerr), MaxIterations(maxiter)
	{
		const gsl_multiroot_fdfsolver_type * solvertype = nullptr; 

		switch (gslsolvertype)
		{
		case gsl_solver_type::newton:
			solvertype = gsl_multiroot_fdfsolver_newton;
			break;
		case gsl_solver_type::gnewton:
			solvertype = gsl_multiroot_fdfsolver_gnewton;
			break;
		case gsl_solver_type::hybridj:
			solvertype = gsl_multiroot_fdfsolver_hybridj;
			break;
		case gsl_solver_type::hybridsj:
			solvertype = gsl_multiroot_fdfsolver_hybridsj;
			break;
		default:
			throw std::runtime_error{ "GSL solver not known!" };
		}

		solver = gsl_multiroot_fdfsolver_alloc(solvertype, dims);
		auto errorhandler = [](const char * reason, const char * file, int line, int gsl_errno) -> void
		{
			gsl_stream_printf("ERROR", file, line, reason);
			throw std::runtime_error{"Error in GSL!"};
		};
		gsl_set_error_handler(errorhandler);

		fdf.n = dims;
	};

	~GSL_Implicit_Solver() noexcept
	{
		gsl_multiroot_fdfsolver_free(solver);
	}

	DISALLOW_COPY_AND_MOVE(GSL_Implicit_Solver)

	//TODO: Use outcome here, either the solver converged or it did not and should say so with an error!
	template<class Derived, class f_functor, class fd_functor, class fdf_functor>
	auto getResult(f_functor&& funcx, fd_functor&& funcjacobix, fdf_functor&& fdfx, const Eigen::MatrixBase<Derived>& guessx)
	{
		Eigen::Map<Derived>(solver->x->data) = guessx;
		
		using EvalFunctor = Evaluators<f_functor, fd_functor, fdf_functor>;
		const EvalFunctor Eval { std::forward<f_functor>(funcx), std::forward<fd_functor>(funcjacobix), std::forward<fdf_functor>(fdfx) };
				
		auto gsl_to_eigen_converter_fdf = [](const gsl_vector * x, void * params, gsl_vector * f, gsl_matrix * df) -> int
		{
			const EvalFunctor& func{ *static_cast<EvalFunctor*>(params) };
			Eigen::Map<Derived> xivec(x->data); // GSL to Eigen
			const auto res_fdf = func.fdf(xivec);
			Eigen::Map<Derived>(f->data) = std::get<0>(res_fdf); // Eigen To GSL
			Eigen::Map<std::decay_t<decltype(std::get<1>(res_fdf))>, Eigen::Unaligned, Eigen::Stride<1, Derived::RowsAtCompileTime> >(df->data) = std::get<1>(res_fdf); //Eigen to GSL (Eigen column major; GSL row major)
			return 0; 
		};
		auto gsl_to_eigen_converter_f = [](const gsl_vector * x, void * params, gsl_vector * f) -> int
		{
			const EvalFunctor& func{ *static_cast<EvalFunctor*>(params) };
			Eigen::Map<Derived> xivec(x->data); // GSL to Eigen
			Eigen::Map<Derived>(f->data) = func.f(xivec); // Eigen To GSL
			return 0;
		};
		auto gsl_to_eigen_converter_df = [](const gsl_vector * x, void * params,  gsl_matrix * df) -> int
		{
			const EvalFunctor& func{ *static_cast<EvalFunctor*>(params) };
			Eigen::Map<Derived> xivec(x->data); // GSL to Eigen
			Eigen::Map<decltype(func.df(xivec)), Eigen::Unaligned, Eigen::Stride<1, Derived::RowsAtCompileTime> >(df->data) = func.df(xivec); //Eigen to GSL (Eigen column major; GSL row major)
			return 0;
		};
				
		fdf.f = gsl_to_eigen_converter_f;
		fdf.df = gsl_to_eigen_converter_df;
		fdf.fdf = gsl_to_eigen_converter_fdf;
		fdf.params = (void*)(&Eval);

		MAYBE_UNUSED auto errset = gsl_multiroot_fdfsolver_set(solver, &fdf, solver->x);
	 
		auto counter{ 0ull };
		for (; ++counter < MaxIterations;)
		{
			MAYBE_UNUSED const auto err = gsl_multiroot_fdfsolver_iterate(solver); //One step of the solver iteration (Error codes: GSL_EBADFUNC, GSL_ENOPROG)
			const auto res = gsl_multiroot_fdfsolver_root(solver); //Gets the current root
			const auto dx =  gsl_multiroot_fdfsolver_dx(solver); // gets the last stepsize
			const auto check = gsl_multiroot_test_delta(dx, res, AbsErrorGoal, RelErrorGoal); // Return GSL_SUCCESS if step is below specific epsilons else GSL_CONTINUE 

			//const auto norm = gsl_blas_dnrm2(dx);
			//std::cout << "dxnorm: " << norm << "\n";

			if (check == GSL_SUCCESS /*|| err == GSL_ENOPROG*/)
				break;
		}
		if (counter == MaxIterations)
			std::cout << "Implicit solver did not reach requested error goal within Iterationlimit! Number of Iterations: " << counter << "\n";

		//std::cout << "Success after Iteration: " << counter << "\n";
		//const auto res = gsl_multiroot_fdfsolver_root(solver);

		return Eigen::Map<Derived>(solver->x->data);
	};
private:
	Precision	AbsErrorGoal{ std::numeric_limits<Precision>::epsilon() };
	Precision	RelErrorGoal{ std::numeric_limits<Precision>::epsilon() };
	const std::size_t	MaxIterations{ 1 };

	gsl_multiroot_fdfsolver * solver = nullptr;
	gsl_multiroot_function_fdf fdf;
};