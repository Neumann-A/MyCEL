#pragma once

// Two underscroes __{var} means 1/{var}
//#define M_4PI		12.566370614359172953850573533118;   // 4 * PI
//#define M__4PI      0.07957747154594766788444188168626   // 1/4PI 
//#define M_2PI       6.283185307179586476925286766559   // 2 * PI 
//#define M__2PI      0.15915494309189533576888376337251   // 1/2PI 
//#define M_4PI_3     4.1887902047863909846168578443727   // 4 * PI / 3
//#define M_3__4PI    0.23873241463784300365332564505877   // 3 / (PI * 4)

namespace math::constants
{
	namespace detail
	{
		template<typename T>
		extern constexpr T pi() { return static_cast<T>(3.1415926535897932384626433832795); };

		template<typename T>
		extern constexpr T two_pi() { return static_cast<T>(2.0*pi()); };

		template<typename T>
		extern constexpr T four_third_pi() { return static_cast<T>((4.0 / 3.0)*pi()); };

		template<typename T>
		extern constexpr T inv_pi() { return static_cast<T>(1.0 / pi()); };

		template<typename T>
		extern constexpr T inv_two_pi() { return static_cast<T>(0.5 * inv_pi()); };

		template<typename T>
		extern constexpr T inv_four_pi() { return static_cast<T>(0.25 * inv_pi()); };

		template<typename T>
		extern constexpr T inv_four_third_pi() { return static_cast<T>((3.0 / 4.0)*inv_pi()); };
	}

	template<typename T>
	static constexpr T pi = detail::pi<T>();

	template<typename T>
	static constexpr T two_pi = 2.0*pi<T>;

	template<typename T>
	static constexpr T four_third_pi = (4.0/3.0)*pi<T>;

	template<typename T>
	static constexpr T inv_pi = 1/pi<T>;

	template<typename T>
	static constexpr T inv_two_pi = 0.5*inv_pi<T>;

	template<typename T>
	static constexpr T inv_four_pi = 0.25*inv_pi<T>;

	template<typename T>
	static constexpr T inv_four_third_pi = 3.0/4.0*inv_pi<T>;

}
