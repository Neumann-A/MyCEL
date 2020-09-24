///---------------------------------------------------------------------------------------------------
// file:		strongtype.hpp
//
// summary: 	Declares the strongtype class
//
// Copyright (c) 2019 Alexander Neumann.
//
// author: Neumann
// date: 04.10.2019
#ifndef INC_strongtype_H
#define INC_strongtype_H

#pragma once
///---------------------------------------------------------------------------------------------------

#include <type_traits>
#include <utility>

namespace {
    template<typename T, typename _ = void>
    struct is_not_a_reference_t : std::false_type {};

    template<typename T>
    struct is_not_a_reference_t<T, typename std::enable_if_t<!std::is_reference_v<T>> > : std::true_type{};

    template< typename T >
    inline constexpr bool is_not_a_reference_v = is_not_a_reference_t<T>::value;
}

// StrongType makes universal types like int, double, Vec3D .. distinct from each other using the Tag type.
// This allows for strong interfaces/function calls using the StrongType and avoids mixing up the 
// parameters to a function call.
// StrongType is implicitly convertable to its underlying type (int, double, Vec3D, ...) to allow
// all operations on the underlying type but loses it StrongType type this way. (Since the meaning might have changed)
// The implicit conversion is allowed to allow easy working with C libraries.
// If you want a StrongType which itselft returns the same StrongType on some operations you want to use SkilledStrongType
// and define the allowed arithmetic Opertation which return the same SkilledStrongType
// Due to the above limitation StrongType might also be called StrongParameterType since it mainly applies to being Strong
// on C++ function calls if the function is defined using the StrongType. 
// The Tag might be used to encode additional meaning to the strong type (e.g. a name for serialization)
// How to use: using MyStrongMeaningfullType = StrongType<UniversalType, MyTag>;
template<typename Type, typename Tag, typename _ = void>
struct StrongType { static_assert(!std::is_same_v<T, T>, "Strong Type used wrongly!"); };


template<typename Type, typename Tag>
struct StrongType<Type, Tag, std::enable_if_t<std::is_fundamental_v<Type> > > {
    //Only applies to buildin types like int, char, etc
    //Types which are classes are coverd by the partial template specialization and not this class!
private:
    using this_type = StrongType<Type, Tag, std::enable_if_t<std::is_fundamental_v<Type> > >;
    template<typename other_tag, typename other_>
    using other_strongtype = StrongType<Type, other_tag, other_>;
    using _type = std::enable_if_t < std::is_fundamental_v<Type>>;
public:
    using underlying_type = Type;
    using tag_type = Tag;					//StrongTypes with the same underlying_type are grouped by the tag_type

    underlying_type value;

    // constructor
    inline explicit constexpr StrongType(underlying_type const& val) noexcept(noexcept(underlying_type(val))) : value(val) {}
    template<typename T_ = underlying_type, typename _ = is_not_a_reference_t<T_>> 
    inline explicit constexpr StrongType(underlying_type&& val) noexcept(noexcept(underlying_type(std::move(val)))) : value(std::move(val)) {}

    inline constexpr operator underlying_type& () noexcept { return value; }
    inline constexpr operator underlying_type () const noexcept { return value; }

    // get
    inline constexpr underlying_type& get() noexcept{ return value; }
    inline constexpr std::remove_reference_t<underlying_type> const& get() const noexcept { return value; }
};

template<typename wrapped_type, typename tag>
struct StrongType<wrapped_type, tag, std::enable_if_t<std::is_class_v<wrapped_type>> > : public wrapped_type {
    // This definition applies to all classes. 
    // The inheritance makes sure that all functions of the underlying type are available. 
    // Should be used for classes like Vec3D which represents a 3D vector but might have different meanings depending on what it represents

    using underlying_type = wrapped_type;
    using tag_type = tag;						//StrongTypes with the same underlying_type are grouped by the tag_type
    
    // constructor
    inline explicit constexpr StrongType(underlying_type const& val) noexcept(noexcept(underlying_type(val))) : underlying_type( val ) {}
    template<typename T_ = underlying_type, typename _ = is_not_a_reference_t<T_>>
    inline explicit constexpr StrongType(underlying_type&& val) noexcept(noexcept(underlying_type(std::move(val)))) : underlying_type( std::move(val)) {}
    
    constexpr inline operator underlying_type& () noexcept { return *this; }
    constexpr inline operator underlying_type () const noexcept { return *this; }

    // get
    inline constexpr underlying_type& get() noexcept { return *this; }
    inline constexpr std::remove_reference_t<underlying_type> const& get() const noexcept { return *this; }
};

template<typename T, typename _ = void >
struct is_strong_type : std::false_type {};

template<typename T>
struct is_strong_type<T, typename std::enable_if_t<std::is_base_of_v<T, StrongType<typename T::underlying_type, typename T::tag_type>>>> : std::true_type {};

template< typename T >
inline constexpr bool is_strong_type_v = is_strong_type<T>::value;

namespace
{
    using MyStrongTypeTest = StrongType<int, struct Int_Tag>;
    struct MyClassTest { double x[4]; };
    using MyStrongTypeTest2 = StrongType<MyClassTest, struct Class_Tag>;

    static_assert(is_strong_type_v<MyStrongTypeTest>);
    static_assert(sizeof(MyStrongTypeTest) == sizeof(int));
    static_assert(!is_strong_type_v<int>);
    static_assert(is_strong_type_v<MyStrongTypeTest2>);
    static_assert(sizeof(MyStrongTypeTest2) == sizeof(MyClassTest));
    static_assert(!is_strong_type_v<MyClassTest>);
}



// a SkilledStrongType has the same properties as a StrongType with the addition that it can define additional operations(skills)
// which return the same type as the SkilledStrongType and does not convert to the underlying type. The underlying type must support the requested
// operation defined by the skill.
// as an example: If you define a StrongType named Length and add it with another Length you properly have a Length in these cases you would define
// a SkilledStrongType with the skills Add AddAssign Substract SubstractAssign
template<typename wrapped_type, typename tag_type, template<typename> class ... Skills>
struct SkilledStrongType : public StrongType<wrapped_type, tag_type>, public Skills<SkilledStrongType<wrapped_type, tag_type, Skills...>>...
{
    //Skills are basically Operations returning the same Type. 
    using underlying_type = wrapped_type;
    using ThisClass = SkilledStrongType<wrapped_type, tag_type, Skills...>;
    template<typename other_wrapped_type, typename other_tag_type, template<typename> class ... Other_Skills>
    using OtherClass = SkilledStrongType<other_wrapped_type, other_tag_type, Other_Skills...>;

    // constructor
    inline explicit constexpr SkilledStrongType(underlying_type const& val) 
        noexcept(noexcept(StrongType<wrapped_type, tag_type>(val))) 
        : StrongType<wrapped_type, tag_type>(val) {};
    template<typename T_ = underlying_type, typename _ = is_not_a_reference_t<T_>>
    inline explicit constexpr SkilledStrongType(underlying_type&& val) 
        noexcept(noexcept(StrongType<wrapped_type, tag_type>(std::move(val)))) 
        : StrongType<wrapped_type, tag_type>(std::move(val)) {}
};



#endif	// INC_strongtype_H
// end of Sources\Libs\LibUtil\types\strongtype.hpp
///---------------------------------------------------------------------------------------------------
