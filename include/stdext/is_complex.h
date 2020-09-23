#pragma once
#include <type_traits>
#include <complex>

namespace stdext
{
    template<typename T, typename _ = std::void_t<> >
    struct is_complex : std::false_type {};

    template <typename T>
    struct is_complex<T,
        std::void_t< typename std::decay_t<T>::value_type >> : std::conjunction<std::is_same<T, std::complex<typename T::value_type> >, std::is_arithmetic<std::decay_t<typename T::value_type>>> {};

    template<typename T>
    static constexpr bool is_complex_v = is_complex<T>::value;
}
