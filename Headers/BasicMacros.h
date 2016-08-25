#pragma once

#ifndef _BASICMACROS_H_
#define _BASICMACROS_H_

#include <locale>
#include <type_traits>

//class str_const { // constexpr string
//private:
//	const char* const p_;
//	const std::size_t sz_;
//public:
//	template<std::size_t N>
//	constexpr str_const(const char(&a)[N]) : // ctor
//		p_(a), sz_(N - 1) {}
//	constexpr char operator[](std::size_t n) { // []
//		return n < sz_ ? p_[n] :
//			throw std::out_of_range("");
//	}
//	constexpr std::size_t size() { return sz_; } // size()
//};

#define IS_SAME_TYPE(T1, T2) \
static_assert(std::is_same< T1, T2 >::value, \
"\n'Cuz " #T1 " and " #T2 " are not the same type.");

#define DEFAULT_COPY_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = default;   \
  const TypeName& operator=(const TypeName&) = default; \
  TypeName(TypeName&&) = default;   \
  const TypeName& operator=(TypeName&&) = default;


#define DISALLOW_COPY_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;   \
  void operator=(const TypeName&) = delete; \
  TypeName(TypeName&&) = delete;   \
  void operator=(TypeName&&) = delete;

// Does what the macro says; prohibits coping of a object
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;   \
  void operator=(const TypeName&) = delete;

#define ALLOW_DEFAULT_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = default;   \
  const TypeName& operator=(const TypeName&) = default;

#define DISALLOW_MOVE_AND_ASSIGN(TypeName) \
  TypeName(TypeName&&) = delete;   \
  void operator=(TypeName&&) = delete;

#define ALLOW_DEFAULT_MOVE_AND_ASSIGN(TypeName) \
  TypeName(TypeName&&) = default;   \
  TypeName& operator=(TypeName&&) = default;

//Interface definition of ctor and dtor
//#undef MY_INTERFACE
#define MY_INTERFACE(TypeName) \
protected: \
	constexpr TypeName() noexcept {}; \
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
#define VARNAME(x) #x
#define SVARNAME(x) std::string{VARNAME(x)}
#define SMEMBERNAME(x) (std::string{VARNAME(x)}).replace(0,2,std::string{std::toupper(VARNAME(x)[1],std::locale{})})

// Call Member function via pointer to member function
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#endif

