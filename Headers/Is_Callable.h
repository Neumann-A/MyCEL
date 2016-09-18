#pragma once

#include <type_traits>
#include <utility>

#include "BasicMacros.h"
#include "PreprocessorMakros.h"

namespace stdext
{
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

#define HAS_MEMBER_FUNC(Class, Fun, ...) stdext::is_callable<decltype(std::mem_fn(& CONCATTHREE_LTR(Class,::,Fun) )), ## Class ## , ##__VA_ARGS__ >::value
#define FUNC_EXIST(Fun, ...) stdext::is_callable<decltype(std::bind(CONCAT(&,Fun), ADDBRACES(__VA_ARGS__))), ##__VA_ARGS__ >::value
