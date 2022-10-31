#pragma once

#ifndef MYCEL_STATIC_MAP_HPP
#define MYCEL_STATIC_MAP_HPP

#include <array>
#include <string>
#include <cstdint>
#include <utility>
#include <stdexcept>
#include <optional>
#include <algorithm>
#include <fmt/format.h>

namespace MyCEL
{
    template <typename Key, typename Value, std::size_t Size>
    struct static_map : std::array<std::pair<Key, Value>, Size>
    {
        using type       = static_map<Key, Value, Size>;
        using array_type = std::array<std::pair<Key, Value>, Size>;
        [[nodiscard]] constexpr std::optional<Value> at(const Key &key) const noexcept
        {
            const auto it =
                std::find_if(std::begin(*this), std::end(*this), [&key](const auto &val) { return val.first == key; });
            if (it != std::end(*this))
                return it->second;
            return std::nullopt;
        };
        [[nodiscard]] constexpr Value operator[](const Key &key) const
        {
            const auto it =
                std::find_if(std::begin(*this), std::end(*this), [&key](const auto &val) { return val.first == key; });
            if (it != std::end(*this))
                return it->second;
            else {
                throw std::range_error("Key not found!");
            }
        };
        [[nodiscard]] constexpr Key operator[](const Value &val) const
        {
            const auto it =
                std::find_if(std::begin(*this), std::end(*this), [&val](const auto &key) { return key.second == val; });
            if (it != std::end(*this))
                return it->first;
            else {
                using std::to_string;
                constexpr bool has_to_string = requires(const Value& t) {
                    to_string(t);
                };
                if constexpr (!has_to_string) {
                    const auto msg = fmt::format("Value '{}' not found!" , val);
                    throw std::range_error(msg);
                }
                else {
                    
                    const auto msg = fmt::format("Value '{}' not found!" , to_string(val));
                    throw std::range_error(msg);
                }
            }
        };
        [[nodiscard]] constexpr static_map<Value, Key, Size> switch_key_value() const noexcept
        {
            std::array<std::pair<Value, Key>, Size> val;
            for (std::size_t i = 0; i < this->size(); ++i) {
                val[i] = std::make_pair(Value{static_cast<array_type>(*this)[i].second},
                                        Key{static_cast<array_type>(*this)[i].first});
            }
            return static_map<Value, Key, Size>{ {val} };
        }

        [[nodiscard]] constexpr auto get_key_array() const noexcept
        {
            std::array<Key, Size> ret;
            std::transform(std::begin(*this),std::end(*this), std::begin(ret),[](const auto& in) {return in.first;});
            return ret;
        }

        [[nodiscard]] constexpr auto get_value_array() const noexcept
        {
            std::array<Value, Size> ret;
            std::transform(std::begin(*this),std::end(*this),std::begin(ret),[](const auto& in) {return in.second;});
            return ret;
        }
    };
    template <std::size_t Element, typename Key, typename Value, std::size_t Size>
    constexpr auto get(static_map<Key,Value,Size>& map) noexcept
    {
        return std::get<Element>(static_cast<std::array<std::pair<Key, Value>, Size>>(map));
    }
} // namespace MyCEL
#endif
