///---------------------------------------------------------------------------------------------------
// file:		math\ApproxJacobian.h
//
// summary: 	Helper to Approximate the Jacobian of a function
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 13.10.2017

#ifndef INC_ApproxJacobian_H
#define INC_ApproxJacobian_H
///---------------------------------------------------------------------------------------------------
#pragma once

namespace math
{
	template<typename Func, typename X, typename DX, typename JacOut>
	void approximateJacobian(Func&& func, const X& x, const DX& dx, JacOut& out)
	{
		//const auto funcx = func(x);
		const auto xsize = x.size();
		//const auto funcxsize = funcx.size();

		for (auto i = 0; i < x.size(); ++i)
		{
			auto dx1 = x;
			auto dx2 = x;
			dx1(i) -= dx(i)/2;
			dx2(i) += dx(i)/2;
			const auto funcdx1 = func(dx1);
			const auto funcdx2 = func(dx2);
			const auto dfuncdxi = ((funcdx2 - funcdx1) / dx(i));

			//std::cout << "x: " << x.transpose() << '\n';
			//std::cout << "dx: " << dx.transpose() << '\n';
			//std::cout << "dx1: " << dx1.transpose() << '\n';
			//std::cout << "dx2: " << dx2.transpose() << '\n';
			//std::cout << "funcdx1: " << funcdx1.transpose() << '\n';
			//std::cout << "funcdx2: " << funcdx2.transpose() << '\n';
			//std::cout << "size: " << xsize << '\n';
			//std::cout << "block: " << out.block(i, 0, 1, xsize) << '\n';
			//std::cout << "dfuncxi: " << dfuncdxi.transpose() << '\n';

			out.block(0, i, xsize, 1) = dfuncdxi;
		}
	}
}


#endif	// INC_ApproxJacobian_H
// end of math\ApproxJacobian.h
