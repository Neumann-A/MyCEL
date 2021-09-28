#pragma once

#ifndef INC_MYCEL_TEMPLATEHELPERS_H
#define INC_MYCEL_TEMPLATEHELPERS_H

#include <type_traits>
#include <utility>
#include <tuple>

namespace MyCEL {
    template <const auto &Input, template <std::remove_cvref_t<decltype(::std::get<0>(Input))>...> typename Output, std::size_t... Is>
    constexpr auto apply_nttp_impl(std::index_sequence<Is...>) -> Output<::std::get<Is>(Input)...>;

    template <const auto &Input, template <std::remove_cvref_t<decltype(::std::get<0>(Input))>...> typename Output>
    constexpr auto apply_nttp() -> decltype(apply_nttp_impl<Input,Output>(std::make_index_sequence<size(Input)>()));

    template <const auto &Input, template <std::remove_cvref_t<decltype(::std::get<0>(Input))>...> typename Output>
    using apply_nttp_t = decltype(apply_nttp_impl<Input, Output>(std::make_index_sequence<size(Input)>()));
}

#endif //INC_MYCEL_TEMPLATEHELPERS_H
