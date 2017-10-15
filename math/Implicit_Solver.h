#pragma once

#include <cstddef>
#include <limits>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/LU>

template <typename prec>
class Implicit_Solver
{

public:
	using Precision = prec;

	Implicit_Solver(Precision abserr, Precision relerr, std::size_t maxiter) : AbsErrorGoal(abserr), RelErrorGoal(relerr), MaxIterations(maxiter) 
	{
		//TODO check errors in comparison with expected value;
	};

	template<class Derived, class f_functor, class fd_functor, class fdf_functor>
	auto getDeltaNextIteration(Eigen::MatrixBase<Derived>& lastx, const f_functor&, const fd_functor&, fdf_functor&& fdfx)
	{
		//TODO: add static assert to check correctness of the functors returntype in correspondence with the dimension of the input vector lastx
		//Since the solve method only returns an expression to be solved we need to find out the correct type it should evaluate into!
		using PlainVector = std::decay_t<typename Derived::PlainObject>;
	
		//auto jacobi = funcjacobix(lastx);
		//const auto fx = funcx(lastx);
		
		auto func_eval = fdfx(lastx);
		const auto fx = std::get<0>(func_eval);
		auto jacobi = std::get<1>(func_eval);
				
		PlainVector dx = jacobi.fullPivLu().solve(-fx);

		//TODO: check if it is really a solution!
		//std::cout << "fx:" << fx << "\n";
		//std::cout << "Jac_fx:" << jacobi << "\n";
		//std::cout << "dx:"<<dx << "\n";
		//std::cout << "dxnorm:" << dx.norm() << "\n";

		//PlainVector dx = jacobi.lu().solve(-fx); // does not work for all cases and might give strange results
		return dx;
	}

	template<class Derived, class Derived2>
	bool reachedGoal(const Eigen::MatrixBase<Derived>& dx, const Eigen::MatrixBase<Derived2>& x)
	{
		const auto dxnorm = dx.norm();
		const auto relnorm = dxnorm/x.norm();

		if (dxnorm < AbsErrorGoal || relnorm < RelErrorGoal)
			return true;

		return false;
	}

	//TODO: Use outcome here, either the solver converged or it did not and should say so with an error!
	template<class Derived, class f_functor, class fd_functor, class fdf_functor>
	auto getResult(f_functor&& funcx, fd_functor&& funcjacobix, fdf_functor&& fdfx, const Eigen::MatrixBase<Derived>& guessx)
	{
		Derived resx{ guessx };

		auto counter{ 0ull };
		for (; ++counter < MaxIterations;)
		{
			const auto dx = getDeltaNextIteration(resx, std::forward<f_functor>(funcx), std::forward<fd_functor>(funcjacobix), std::forward<fdf_functor>(fdfx));
			resx += dx;
			//std::cout << "res:" << resx << "\n";
			//std::cout << "resnorm:" << resx.norm() << "\n";
			if (reachedGoal(dx, resx))
				break;
		}
		if (counter >= MaxIterations)
			std::cout << "Implicit solver did not reach requested error goal within Iterationlimit! Number of Iterations: " << counter << "Last dx_"<<"\n";

		return resx;
	};

	//template<class Derived, class FDF_FuncFunctor>
	//auto getResult(FDF_FuncFunctor&& funcx, const Eigen::MatrixBase<Derived>& guessx)
	//{
	//	Derived resx{ guessx };

	//	auto counter{ 0 };
	//	for (; ++counter < MaxIterations;)
	//	{
	//		const auto dx = getDeltaNextIteration(resx, std::forward<FuncFunctor>(funcx), std::forward<FuncJacobiFunctor>(funcjacobix));
	//		resx += dx;
	//		if (reachedGoal(dx, resx))
	//			break;
	//	}
	//	if (counter == MaxIterations)
	//		std::cout << "Implicit solver did not reach requested error goal within Iterationlimit! Number of Iterations: " << counter << "\n";

	//	return resx;
	//};

private:
	Precision	AbsErrorGoal{std::numeric_limits<Precision>::epsilon()};
	Precision	RelErrorGoal{ std::numeric_limits<Precision>::epsilon() };
	std::size_t	MaxIterations{ 1000 };

};