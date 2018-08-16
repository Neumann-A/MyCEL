///---------------------------------------------------------------------------------------------------
// file:		math\GSL_Implicit_Solver_Derivative_Free.h
//
// summary: 	Declares the gsl implicit solver derivative free solver class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 03.09.2017

#ifndef INC_GSL_Implicit_Solver_Derivative_Free_H
#define INC_GSL_Implicit_Solver_Derivative_Free_H
///---------------------------------------------------------------------------------------------------
#pragma once

#pragma once

//#include <gtest/gtest.h>

#include "../basics/BasicMacros.h"

#include <iostream>
#include <type_traits>

#include <Eigen/Core>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multiroots.h>
//#include <gsl/gsl_blas.h>

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment (lib, "gsld")
#pragma comment (lib, "gslcblasd")
#else
#pragma comment (lib, "gsl")
#pragma comment (lib, "gslcblas")
#endif
#endif
enum class gsl_solver_type_derivative_free { undefined, hybrids, hybrid, dnewton, broyden };

template <typename prec>
class GSL_Implicit_Solver_Derivative_Free
{

public:
	using Precision = prec;

	GSL_Implicit_Solver_Derivative_Free(Precision abserr, Precision relerr, std::size_t maxiter, std::size_t dims, gsl_solver_type_derivative_free gslsolvertype)
		: AbsErrorGoal(abserr), RelErrorGoal(relerr), MaxIterations(maxiter)
	{
		const gsl_multiroot_fsolver_type * solvertype = nullptr;

		switch (gslsolvertype)
		{
		case gsl_solver_type_derivative_free::hybrids:
			solvertype = gsl_multiroot_fsolver_hybrids;
			break;
		case gsl_solver_type_derivative_free::hybrid:
			solvertype = gsl_multiroot_fsolver_hybrid;
			break;
		case gsl_solver_type_derivative_free::dnewton:
			solvertype = gsl_multiroot_fsolver_dnewton;
			break;
		case gsl_solver_type_derivative_free::broyden:
			solvertype = gsl_multiroot_fsolver_broyden; // do not use! only for testing porpouses! Instable!
			break;
		default:
			throw std::runtime_error{ "GSL solver not known!" };
		}

		solver = gsl_multiroot_fsolver_alloc(solvertype, dims);
		auto errorhandler = [](const char * reason, const char * file, int line, int gsl_errno) -> void
		{
			gsl_stream_printf("ERROR", file, line, reason);
			throw std::runtime_error{ "Error in GSL!" };
		};
		gsl_set_error_handler(errorhandler);

		f.n = dims;
	};

	~GSL_Implicit_Solver_Derivative_Free() noexcept	{	
		gsl_multiroot_fsolver_free(solver);
	}

	DISALLOW_COPY_AND_MOVE(GSL_Implicit_Solver_Derivative_Free)

	//TODO: Use outcome here, either the solver converged or it did not and should say so with an error!
	template<class Derived, class FuncFunctor>
	auto getResult(FuncFunctor&& funcx, const Eigen::MatrixBase<Derived>& guessx)
	{
		using FuncType = std::decay_t<FuncFunctor>;
		Eigen::Map<Derived>(solver->x->data) = guessx;

		auto gsl_to_eigen_converter_f = [](const gsl_vector * x, void * params, gsl_vector * res) -> int
		{
			const FuncType& func{ *static_cast<FuncType*>(params) };
			Eigen::Map<Derived> xivec(x->data); // GSL to Eigen
			//std::cout << "xivec before: " << xivec.transpose() << '\n';
			Eigen::Map<Derived>(res->data) = func(xivec); // Eigen To GSL
			//std::cout << "xivec after: " << xivec.transpose() << '\n';
			return 0;
		};
		
		f.f = gsl_to_eigen_converter_f;

		f.params = static_cast<void*>(&funcx);

		MAYBE_UNUSED auto errset = gsl_multiroot_fsolver_set(solver, &f, solver->x);

		auto counter{ 0ull };
		for (; ++counter < MaxIterations;)
		{
			MAYBE_UNUSED const auto err = gsl_multiroot_fsolver_iterate(solver); //One step of the solver iteration (Error codes: GSL_EBADFUNC, GSL_ENOPROG)
			const auto res = gsl_multiroot_fsolver_root(solver); //Gets the current root
			const auto dx = gsl_multiroot_fsolver_dx(solver); // gets the last stepsize
			const auto check = gsl_multiroot_test_delta(dx, res, AbsErrorGoal, RelErrorGoal); // Return GSL_SUCCESS if step is below specific epsilons else GSL_CONTINUE 

			//Eigen::Map<Derived> dxeigen(dx->data); // GSL to Eigen
			//std::cout << "dx: " << dxeigen.transpose() << '\n';
			//std::cout << "dxnorm: " << dxeigen.norm() << '\n';
			//Eigen::Map<Derived> reseigen(res->data); // GSL to Eigen
			//std::cout << "res: " << reseigen.transpose() << '\n';

			if (check == GSL_SUCCESS /*|| err == GSL_ENOPROG*/) {
				break;
			}

		}
		if (counter == MaxIterations)
			std::cout << "Implicit solver did not reach requested error goal within Iterationlimit! Number of Iterations: " << counter << "\n";
		
		//std::cout << "GSL_DF Solver Number of Iterations: " << counter << '\n';
		
		return Eigen::Map<Derived>(solver->x->data);
	};
private:
	Precision	AbsErrorGoal{ std::numeric_limits<Precision>::epsilon() };
	Precision	RelErrorGoal{ std::numeric_limits<Precision>::epsilon() };
	const std::size_t	MaxIterations;

	gsl_multiroot_fsolver * solver = nullptr;
	gsl_multiroot_function f;
};

#endif	// INC_GSL_Implicit_Solver_Derivative_Free_H
// end of math\GSL_Implicit_Solver_Derivative_Free.h
///---------------------------------------------------------------------------------------------------
