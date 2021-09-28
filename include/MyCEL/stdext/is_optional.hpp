#pragma once

#include <optional>
#include <type_traits>

namespace stdext {
    template<typename T>
    struct is_optional : std::false_type {};
    template<typename T>
    struct is_optional<std::optional<T>> : std::true_type {};
    template<typename T>
    constexpr auto is_optional_v = is_optional<T>::value;

    template<typename T>
    concept IsOptional = is_optional_v<T>;
    template<typename T>
    concept IsNotOptional = !is_optional_v<T>;

    static_assert(IsOptional<std::optional<int>>);
    static_assert(IsNotOptional<double>);
}