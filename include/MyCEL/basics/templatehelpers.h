#pragma once

#ifndef INC_MYCEL_TEMPLATEHELPERS_H
#define INC_MYCEL_TEMPLATEHELPERS_H

#include <type_traits>

namespace MyCEL {
    template <const auto &Input, template <std::remove_cvref_t<decltype(get<0>(Input))>...> typename Output, std::size_t... Is>
    constexpr auto apply_nttp_impl(std::index_sequence<Is...>) -> Output<get<Is>(Input)...>;

    template <const auto &Input, template <std::remove_cvref_t<decltype(get<0>(Input))>...> typename Output>
    constexpr auto apply_nttp() -> decltype(apply_nttp_impl<Input,Output>(std::make_index_sequence<Input.size()>()));

    template <const auto &Input, template <std::remove_cvref_t<decltype(get<0>(Input))>...> typename Output>
    using apply_nttp_t = decltype(apply_nttp_impl<Input, Output>(std::make_index_sequence<Input.size()>()));
}

#endif //INC_MYCEL_TEMPLATEHELPERS_H
