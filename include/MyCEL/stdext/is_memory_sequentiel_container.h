#pragma once

#include <type_traits>
#include <utility>

#include "is_container.h"
#include "is_string.h"

namespace stdext
{
    template<typename T, typename _ = void>
    struct is_memory_sequentiel_container : std::false_type {};

    template<typename T>
    struct is_memory_sequentiel_container<T, std::void_t<decltype(std::declval<T>().data()), typename T::value_type> > : std::conjunction< is_container<T> , std::disjunction<std::negation<is_container<typename T::value_type>>, stdext::is_string<typename T::value_type>> > {};
    //Nested Containers will most likly not be memory sequentiel. Else use a partial specialization for the type

    template<typename T>
    static constexpr bool is_memory_sequentiel_container_v = is_memory_sequentiel_container<T>::value;


}
