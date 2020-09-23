#pragma once

#include <type_traits>
#include <utility>

#include "is_container.h"

namespace stdext
{
    template<typename T, typename _ = void>
    struct is_resizeable_container : std::false_type {};

    template<typename T>
    struct is_resizeable_container<T,
        std::void_t<decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))> > : is_container<T>{};
    
    template<typename T>
    static constexpr bool is_resizeable_container_v = is_resizeable_container<T>::value;
}
