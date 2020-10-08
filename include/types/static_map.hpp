#include <array>
#include <cstdint>
#include <utility>


#pragma once

namespace MyCEL {
template <typename Key, typename Value, std::size_t Size>
struct static_map : std::array<std::pair<Key, Value>, Size> {
  using type = static_map<Key, Value, Size>;
  using array_type = std::array<std::pair<Key, Value>, Size>;
  [[nodiscard]] constexpr std::optional<Value>
  at(const Key &key) const noexcept {
    const auto it =
        std::find_if(std::begin(*this), std::end(*this),
                     [&key](const auto &val) { return val.first == key; });
    if (it != std::end(*this))
      return it->second;
    return std::nullopt;
  };
  [[nodiscard]] constexpr Value operator[](const Key &key) const {
    const auto it =
        std::find_if(std::begin(*this), std::end(*this),
                     [&key](const auto &val) { return val.first == key; });
    if (it != std::end(*this))
      return it->second;
    else
      throw std::range_error("Key not found");
  };
  [[nodiscard]] constexpr Value operator[](const Value &val) const {
    const auto it =
        std::find_if(std::begin(*this), std::end(*this),
                     [&val](const auto &key) { return key.second == val; });
    if (it != std::end(*this))
      return it->first;
    else
      throw std::range_error("Value not found");
  };
  [[nodiscard]] constexpr static_map<Value, Key, Size>
  switch_key_value() const noexcept {
    std::array<std::pair<Value, Key>, Size> ret;
    for (std::size_t i = 0; i < this->size(); ++i) {
      ret[i] = std::make_pair(Value{static_cast<array_type>(*this)[i].second},
                              Key{static_cast<array_type>(*this)[i].first});
    }
    return static_map<Value, Key, Size>{ret};
  }
};
} // namespace MyCEL