#pragma once

#ifndef INC_MYCEL_CONCEPTS_H
#define INC_MYCEL_CONCEPTS_H

#include <type_traits>
#include <array>


namespace MyCEL
{
    template <typename T>
    struct is_std_array : std::false_type {};

    template <typename T, std::size_t N>
    struct is_std_array<std::array<T, N>> : std::true_type {};

    template <typename T>
    concept std_array = is_std_array<std::decay_t<T>>::value;

    template <typename T>
    struct is_fundamental_type : std::false_type {};
    template <typename T>
    concept fundamental_type = is_fundamental_type<T>::value;

    template <>
    struct is_fundamental_type<bool> : std::true_type {};

    template <>
    struct is_fundamental_type<signed char> : std::true_type {};
    template <>
    struct is_fundamental_type<unsigned char> : std::true_type {};

    template <>
    struct is_fundamental_type<short int> : std::true_type {};
    template <>
    struct is_fundamental_type<unsigned short int> : std::true_type {};

    template <>
    struct is_fundamental_type<int> : std::true_type {};
    template <>
    struct is_fundamental_type<unsigned int> : std::true_type {};

    template <>
    struct is_fundamental_type<long int> : std::true_type {};
    template <>
    struct is_fundamental_type<unsigned long int> : std::true_type {};

    template <>
    struct is_fundamental_type<long long int> : std::true_type {};
    template <>
    struct is_fundamental_type<unsigned long long int> : std::true_type {};

    template <>
    struct is_fundamental_type<float> : std::true_type {};
    template <>
    struct is_fundamental_type<double> : std::true_type {};
    template <>
    struct is_fundamental_type<long double> : std::true_type {};

} // namespace MyCEL

#endif //INC_MYCEL_CONCEPTS_H
