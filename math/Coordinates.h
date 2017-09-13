#pragma once

#include <cmath>

#include <Eigen/Core>

#include "math_constants.h"


namespace math::coordinates
{
	using namespace math::constants;

	template<typename Precision>
	using Vec2D = Eigen::Matrix<Precision, 2, 1>;
	template<typename Precision>
	using Vec3D = Eigen::Matrix<Precision, 2, 1>;

	namespace helpers
	{
		template<typename T>
		std::enable_if_t<std::is_arithmetic_v<T>, T> NonNegativRemquo(const T& val, const T& mod, int &quo)
		{
			T modulus = std::remquo(val, std::abs(mod), quo);
			if (modulus < 0)
				modulus = mod - modulus;
			return modulus;
		};

		template<typename T>
		std::enable_if_t<std::is_arithmetic_v<T>, T> NonNegativModulus(const T &val, const T &mod)
		{
			auto modulus = std::fmod(val, std::abs(mod));
			if (modulus < 0)
				modulus = mod + modulus;
			return modulus;
		};
	};

	template<typename Derived>
	inline Vec2D<typename Derived::Scalar> Wrap2DSphericalCoordinates(const Eigen::MatrixBase<Derived>& vec2d)
	{
		using Precision = typename Derived::Scalar;
		Vec2D<Precision> res;
		res(0) = helpers::NonNegativModulus(vec2d(0), two_pi<Precision>);
		if (res(0) > pi<Precision>)
		{
			res(0) = two_pi<Precision> - res(0);
			res(1) = helpers::NonNegativModulus<Precision>(vec2d(1) - pi<Precision>, two_pi<Precision>);
		}
		else
		{
			res(1) = helpers::NonNegativModulus<Precision>(vec2d(1), two_pi<Precision>);
		}
		return res;
	}

	template<typename Derived>
	inline Eigen::MatrixBase<Derived>& Wrap2DSphericalCoordinatesInplace(const Eigen::MatrixBase<Derived>& vec2d)
	{
		using Precision = typename Derived::Scalar;

		const_cast<Eigen::MatrixBase<Derived>&>(vec2d)(0) = helpers::NonNegativModulus(vec2d(0), two_pi<Precision>);
		if (vec2d(0) > pi<Precision>)
		{
			const_cast<Eigen::MatrixBase<Derived>&>(vec2d)(0) = two_pi<Precision> - vec2d(0);
			const_cast<Eigen::MatrixBase<Derived>&>(vec2d)(1) = helpers::NonNegativModulus<Precision>(vec2d(1) - pi<Precision>, two_pi<Precision>);
		}
		else
		{
			const_cast<Eigen::MatrixBase<Derived>&>(vec2d)(1) = helpers::NonNegativModulus<Precision>(vec2d(1), two_pi<Precision>);
		}
		return const_cast<Eigen::MatrixBase<Derived>&>(vec2d);
	}

	template<typename Derived>
	inline Vec3D<typename Derived::Scalar> calcPointOnSphere(const Eigen::MatrixBase<Derived>& vec2d)
	{
		static_assert((Derived::RowsAtCompileTime == 2 && Derived::ColsAtCompileTime == 1) ||
			(Derived::RowsAtCompileTime == 1 && Derived::ColsAtCompileTime == 2), "Used matrix of wrong dimensions for this function!");

		Vec3D<typename Derived::Scalar> res;
		const auto &theta = vec2d(0);
		const auto &phi = vec2d(1);

		//avoiding two evaluations!
		const auto sintheta = std::sin(theta);

		res(0) = sintheta*std::cos(phi);
		res(1) = sintheta*std::sin(phi);
		res(2) = std::cos(theta);

		return res;
	};
};