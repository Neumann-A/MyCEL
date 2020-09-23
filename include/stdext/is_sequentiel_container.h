#pragma once

#include "is_container.h"
#include "is_associative_container.h"

namespace stdext
{
    template<typename T>
    struct is_sequentiel_container : std::conjunction<is_container<T>, std::negation<is_associative_container<T>>> {};

    template<typename T>
    static constexpr bool is_sequentiel_container_v = is_sequentiel_container<T>::value;
}