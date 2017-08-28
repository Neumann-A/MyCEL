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



namespace math::geometry
{
	template<typename T>
	extern constexpr T math_pi() { return static_cast<T>(3.1415926535897932384626433832795); };
	
	template<typename T>
	extern constexpr T math_1_pi() { return static_cast<T>(0.31830988618379067153776752674503); };

	// Two underscroes __{var} means 1/{var}
//#define M_PI		3.1415926535897932384626433832795
#define M_4PI		12.566370614359172953850573533118;   // 4 * PI
#define M__4PI      0.07957747154594766788444188168626   // 1/4PI 
#define M_2PI       6.283185307179586476925286766559   // 2 * PI 
#define M__2PI      0.15915494309189533576888376337251   // 1/2PI 
#define M_4PI_3     4.1887902047863909846168578443727   // 4 * PI / 3
#define M_3__4PI    0.23873241463784300365332564505877   // 3 / (PI * 4)

	namespace sphere
	{
		template<typename precision>
		inline static constexpr precision calcSurfaceArea(const precision& radius) noexcept { return math_pi<precision>*std::pow(radius, 2); };
		template<typename precision>
		inline static constexpr precision calcRadiusFromSurfaceArea(const precision& area) noexcept { return std::sqrt(area*M__4PI); };

		template<typename precision>
		inline static constexpr precision calcVolume(const precision& radius) noexcept { return M_4PI_3*std::pow(radius, 3); };
		template<typename precision>
		inline static constexpr precision calcRadiusFromVolume(const precision& volume) noexcept { return std::cbrt(volume*M_3__4PI); };
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
		inline static constexpr precision calcArea(const precision& radius) noexcept { return  math_pi<precision>()*std::pow(radius, 2); };
		template<typename precision>
		inline static constexpr precision calcRadiusArea(const precision& area) noexcept { return std::sqrt(area*math_1_pi<precision>(), 2); };

		template<typename precision>
		inline static constexpr precision calcCircumference(const precision& radius) noexcept { return M_2PI*radius; };
		template<typename precision>
		inline static constexpr precision calcRadiusFromCircumference(const precision& length) noexcept { return M__2PI*length; };
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

