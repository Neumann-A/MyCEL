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

	template<class Derived, class FuncFunctor, class FuncJacobiFunctor>
	auto getDeltaNextIteration(const Eigen::MatrixBase<Derived>& lastx, const FuncFunctor& funcx, const FuncJacobiFunctor& funcjacobix)
	{
		//TODO: add static assert to check correctness of the functors returntype in correspondence with the dimension of the input vector lastx
		//Since the solve method only returns an expression to be solved we need to find out the correct type it should evaluate into!
		using PlainVector = std::decay_t<typename Derived::PlainObject>;
	
		auto jacobi = funcjacobix(lastx);
		const auto fx = funcx(lastx);

		PlainVector dx = jacobi.fullPivLu().solve(-fx);
		//TODO: check if it is really a solution!

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
	template<class Derived, class FuncFunctor, class FuncJacobiFunctor>
	auto getResult(FuncFunctor&& funcx, FuncJacobiFunctor&& funcjacobix, const Eigen::MatrixBase<Derived>& guessx)
	{
		Derived resx{ guessx };

		auto counter{ 0 };
		for (; ++counter < MaxIterations;)
		{
			const auto dx = getDeltaNextIteration(resx, std::forward<FuncFunctor>(funcx), std::forward<FuncJacobiFunctor>(funcjacobix));
			resx += dx;
			if (reachedGoal(dx, resx))
				break;
		}
		if (counter >= MaxIterations)
			std::cout << "Implicit solver did not reach requested error goal within Iterationlimit! Number of Iterations: " << counter << "\n";

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