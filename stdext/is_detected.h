#pragma once

#include <type_traits>

namespace stdext
{

	// Fix for MSVC 2017 decltype issues!
	template<typename...>
	struct my_void {
		using type = void;
	};
	template<typename... T>
	using void_t = typename my_void<T...>::type;

	// N4502 detection proposal C++17
	struct nonesuch
	{
		nonesuch() = delete;
		~nonesuch() = delete;
		nonesuch(nonesuch const&) = delete;
		void operator=(nonesuch const&) = delete;
	};

	template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
	struct DETECTOR
	{ // exposition only
		using value_t = std::false_type;
		using type = Default;
	};

	template <class Default, template<class...> class Op, class... Args>
	struct DETECTOR<Default, void_t<Op<Args...>>, Op, Args...> 
	{ // exposition only
		using value_t =std::true_type;
		using type = Op<Args...>;
	};

	template <template<class...> class Op, class... Args>
	using is_detected = typename DETECTOR<nonesuch, void, Op, Args...>::value_t;
	template <template<class...> class Op, class... Args>
	using detected_t = typename DETECTOR<nonesuch, void, Op, Args...>::type;
	template <class Default, template<class...> class Op, class... Args>
	using detected_or = DETECTOR<Default, void, Op, Args...>;
	template <template<class...> class Op, class... Args>
	constexpr bool is_detected_v = is_detected<Op, Args...>::value;
	template <class Default, template<class...> class Op, class... Args>
	using detected_or_t = typename detected_or<Default, Op, Args...>::type;
	template <class Expected, template<class...> class Op, class... Args>
	using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;
	template <class Expected, template<class...> class Op, class... Args>
	constexpr bool is_detected_exact_v	= is_detected_exact<Expected, Op, Args...>::value;
	template <class To, template<class...> class Op, class... Args>
	using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;
	template <class To, template<class...> class Op, class... Args>
	constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;

}