#pragma once

#ifndef _BASICMACROS_H_
#define _BASICMACROS_H_

#include <locale>
#include <type_traits>

#define BASIC_NOEXCEPT noexcept

#ifdef _MSC_VER
	#define BASIC_ALWAYS_INLINE __forceinline
	#define BASIC_NOINLINE		__declspec(noinline)
#elif __GNUC__ || __clang__ || __llvm__
	#define BASIC_ALWAYS_INLINE		__attribute__((always_inline)) inline
	#define BASIC_NOINLINE			__attribute__((noinline))
#else
	#define BASIC_ALWAYS_INLINE
	#define BASIC_NOINLINE
#endif

#define BASIC_CONSTEXPR constexpr

#if _MSC_VER >= 1900

#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]
#define FALLTHROUGH [[fallthrough]]
#define DEPRECATED [[deprecated]]
#define DEPRECATEDREASON(x) [[deprecated(#x)]]
#define NORETURN [[noreturn]]


#elif __GNUC__ || __clang__ || __llvm__

#if __has_cpp_attribute(nodiscard)
#define NODISCARD [[nodiscard]]
#elif __has_cpp_attribute(gnu::warn_unused_result)
#define NODISCARD [[gnu::warn_unused_result]]
#endif

#if __has_cpp_attribute(fallthrough)
#define FALLTHROUGH [[fallthrough]]
#elif __has_cpp_attribute(clang::fallthrough)
#define FALLTHROUGH [[clang::fallthrough]]
#else
#define FALLTHROUGH
#endif

#if __has_cpp_attribute(maybe_unused)
#define MAYBE_UNUSED [[maybe_unused]]
#elif __has_cpp_attribute(gnu::unused)
#define MAYBE_UNUSED [[gnu::unused]]

#endif
#else
#define NODISCARD
#define FALLTHROUGH
#define MAYBE_UNUSED
#endif

#define IS_SAME_TYPE(T1, T2) \
static_assert(std::is_same< T1, T2 >::value, \
"\n'Reason: " #T1 " and " #T2 " are not the same type.");

#define DEFAULT_COPY_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = default;   \
  TypeName& operator=(const TypeName&) = default; \
  TypeName(TypeName&&) = default;   \
  TypeName& operator=(TypeName&&) = default;


#define DISALLOW_COPY_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;   \
  TypeName& operator=(const TypeName&) = delete; \
  TypeName(TypeName&&) = delete;   \
  TypeName& operator=(TypeName&&) = delete;

// Does what the macro says; prohibits coping of a object
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;   \
  TypeName& operator=(const TypeName&) = delete;

#define ALLOW_DEFAULT_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = default;   \
  TypeName& operator=(const TypeName&) = default;

#define DISALLOW_MOVE_AND_ASSIGN(TypeName) \
  TypeName(TypeName&&) = delete;   \
  TypeName& operator=(TypeName&&) = delete; \
  static_assert(false, "Don't delete move members!");

#define ALLOW_DEFAULT_MOVE_AND_ASSIGN(TypeName) \
  TypeName(TypeName&&) = default;   \
  TypeName& operator=(TypeName&&) = default;

//Interface definition of ctor and dtor
//#undef MY_INTERFACE
#define MY_CONSTEXPR_INTERFACE(TypeName) \
protected: \
	constexpr TypeName() noexcept {}; \
	~TypeName() = default; \

#define MY_INTERFACE(TypeName) \
protected: \
	TypeName() = default ; \
	~TypeName() = default; \

#define MY_VIRTUAL_INTERFACE(TypeName) \
protected: \
	TypeName() noexcept {}; \
public: \
	virtual ~TypeName() = default; \

// Silly hack to force static functions into an interface so that it throws an error at compile time
// Use it like this STATICINTERFACE(T,T,createObjectFromConfigFile,(const ConfigFile &file, std::string &section),(file,section))
// or like this STATICINTERFACE(std::string,T,getSectionName,(),())
//
#define CONCAT_HIDDEN(first,second) first ## second
#define CONCAT(first,second) CONCAT_HIDDEN(first,second)
#define CONCATTHREE_RTL(first,second,third) CONCAT(CONCAT(first,second),third)
#define CONCATTHREE_LTR(first,second,third) CONCAT(first,CONCAT(second,third))

#define CLASS_STATIC_AND_OBJ_FUNC(ReturnType,Type,StaticFunc,ForwardArgsWithType,ForwardArgs) \
	ReturnType CONCAT(StaticFunc,Obj) ForwardArgsWithType const noexcept\
		{ return Type :: StaticFunc ForwardArgs ; };



// Gives the name of the variable
#define RAWNAME(x) x
#define NAME(x)	#x
#define VARNAME(x) #x
#define SVARNAME(x) std::string{VARNAME(x)}
#define SMEMBERNAME(x) (std::string{VARNAME(x)}).replace(0,2,std::string{std::toupper(VARNAME(x)[1],std::locale{})})

// Call Member function via pointer to member function
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#endif

