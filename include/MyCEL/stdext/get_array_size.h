#pragma once

#include <array>

namespace stdext
{
    template<typename T>
    struct get_array_size
    {
        static constexpr std::size_t size{ 0 };
    };

    template<typename value_type, std::size_t elems>
    struct get_array_size<std::array<value_type, elems>>
    {
        static constexpr std::size_t size{ elems };
    };

    template<typename T>
    static constexpr std::size_t array_size = get_array_size<T>::size;
}
