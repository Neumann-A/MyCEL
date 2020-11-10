#pragma once

#ifndef INC_MYCEL_CONCEPTS_H
#define INC_MYCEL_CONCEPTS_H

#include <type_traits>
#include <array>


namespace MyCEL
{
    template <typename T>
    struct is_std_array : std::false_type
    {
    };

    template <typename T, std::size_t N>
    struct is_std_array<std::array<T, N>> : std::true_type
    {
    };

    template <typename T>
    concept std_array = is_std_array<std::decay_t<T>>::value;
} // namespace MyCEL

#endif //INC_MYCEL_CONCEPTS_H
