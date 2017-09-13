///---------------------------------------------------------------------------------------------------
// file:		math\Geometry.h
//
// summary: 	Declares the geometry namespace
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 07.07.2017

#ifndef INC_Geometry_H
#define INC_Geometry_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <cmath>
#include <type_traits>
#include <utility>

#include "math_constants.h"


namespace math::geometry
{
	using namespace math::constants;

	namespace sphere
	{
		template<typename precision>
		inline static constexpr precision calcSurfaceArea(const precision& radius) noexcept { return pi<precision>*std::pow(radius, 2); };
		template<typename precision>
		inline static constexpr precision calcRadiusFromSurfaceArea(const precision& area) noexcept { return std::sqrt(area*inv_four_pi<precision>); };

		template<typename precision>
		inline static constexpr precision calcVolume(const precision& radius) noexcept { return four_third_pi<precision>*std::pow(radius, 3); };
		template<typename precision>
		inline static constexpr precision calcRadiusFromVolume(const precision& volume) noexcept { return std::cbrt(volume*inv_four_third_pi<precision>); };
	}

	template<typename precision>
	class Sphere
	{		
		static_assert(std::is_arithmetic<precision>::value, "Sphere class must be of arithmetic type");
	private:
		precision _radius;
	public:
		using value_type = precision;

		constexpr explicit Sphere(precision radius) noexcept : _radius(std::move(radius)) {};

		inline const precision& getRadius() const noexcept { return _radius };
		inline void setRadius(precision radius) noexcept { _radius = std::move(radius) };

		inline precision getVolume() const noexcept { return sphere::calcVolume(_radius); };
		inline precision getSurfaceArea() const noexcept { return sphere::calcSurfaceArea(_radius); };
		
	};

	namespace circle
	{
		template<typename precision>
		inline static constexpr precision calcArea(const precision& radius) noexcept { return  pi<precision>*std::pow(radius, 2); };
		template<typename precision>
		inline static constexpr precision calcRadiusArea(const precision& area) noexcept { return std::sqrt(area*inv_pi<precision>, 2); };

		template<typename precision>
		inline static constexpr precision calcCircumference(const precision& radius) noexcept { return two_pi<precision>*radius; };
		template<typename precision>
		inline static constexpr precision calcRadiusFromCircumference(const precision& length) noexcept { return inv_two_pi<precision>*length; };
	}

	template<typename precision>
	class Circle
	{
		static_assert(std::is_arithmetic<precision>::value, "Circle class must be of arithmetic type");
	private:
		precision _radius;
	public:
		using value_type = precision;

		constexpr explicit Circle(precision radius) noexcept : _radius(std::move(radius)) {};

		inline const precision& getRadius() const noexcept { return _radius };
		inline void setRadius(precision radius) noexcept { _radius = std::move(radius) };

		inline precision getArea() const noexcept { return calcArea(_radius); };
		inline precision getCircumference() const noexcept { return calcCircumference(_radius); };
	};

}


#endif	// INC_Geometry_H
// end of math\Geometry.h
///---------------------------------------------------------------------------------------------------

