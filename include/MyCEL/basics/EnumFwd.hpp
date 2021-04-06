#pragma once

#include <string>
#include <type_traits>

template<typename T> requires std::is_enum_v<T>
static constexpr auto get_enum_string_mapping(T&&);

template<typename T> requires std::is_enum_v<T>
std::string to_string(const T& enum_value);

template<typename T> requires std::is_enum_v<T>
static constexpr std::string_view to_string_view(const T& enum_value);

template<typename T> requires std::is_enum_v<T>
T from_string(const std::string&);

template<typename T> requires std::is_enum_v<T>
static constexpr T from_string_view(const std::string_view&);