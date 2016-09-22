#pragma once

#include <type_traits>
#include <utility>

#include "BasicMacros.h"
#include "PreprocessorMakros.h"

namespace stdext
{
	//From http://stackoverflow.com/questions/17201329/c11-ways-of-finding-if-a-type-has-member-function-or-supports-operator
	template <typename C, typename F, typename = void>
	struct is_call_possible : public std::false_type {};

	template <typename C, typename R, typename... A>
	struct is_call_possible<C, R(A...),
		typename std::enable_if<
		std::is_same<R, void>::value ||
		std::is_convertible<decltype(
			std::declval<C>().operator()(std::declval<A>()...)
			//                ^^^^^^^^^^ replace this with the member you need.
			), R>::value
		>::type
	> : public std::true_type {};

	//TODO: Remove if supported by MS compiler
	
	template<class F, class...Args>
	struct is_callable
	{
		template<class U> static constexpr auto test(U* p) -> decltype((*p)(std::declval<Args>()...), void(), std::true_type()) {};
		template<class U> static constexpr auto test(...) -> decltype(std::false_type()) {};

		static constexpr bool value = decltype(test<F>(0))::value;
	};

	template<class F, class...Args>
	using is_callable_v = typename is_callable<F, Args&&...>::value;


	//template<class Fun, class Class, class...Args>
	//struct has_member_fun
	//{
	//	/*template<class U> static constexpr std::enable_if_t<is_callable<Fun, Class, Args&&..>, decltype(auto)> test(U* p) { return std::true_type{}; };
	//	template<class U> static constexpr std::enable_if_t<!is_callable<Fun, Class, Args&&..>, decltype(auto)> test(...) { return std::false_type{}; };
	//	*/
	//	static constexpr bool value = decltype(test<F>())::value;
	//};
}
