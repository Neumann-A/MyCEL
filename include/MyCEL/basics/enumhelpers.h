#pragma once

#ifndef INC_MYCEL_ENUMHELPERS_H
#define INC_MYCEL_ENUMHELPERS_H

#include <type_traits>
#include <variant>
#include <format>

#include <magic_enum.hpp>
#include "templatehelpers.h"

namespace MyCEL
{
    template<typename EnumType, EnumType val>
    struct enum_value_type {
        constexpr static const EnumType enum_value = val;
        using enum_type = EnumType;
    };

    template <typename EnumType, EnumType... EnumVals>
    struct enum_tuple
    {
        using enum_type = EnumType;
        static_assert(std::is_enum_v<EnumType>);
        static constexpr auto count = sizeof...(EnumVals);

        template <EnumType NewValue>
        using append_enum_value = enum_tuple<EnumType, EnumVals..., NewValue>;

        template <EnumType NewValue>
        using prepend_enum_value = enum_tuple<EnumType, NewValue, EnumVals...>;

        template <EnumType... NewValues>
        using append_enum_values = enum_tuple<EnumType, EnumVals..., NewValues...>;

        template <EnumType... NewValues>
        using prepend_enum_values = enum_tuple<EnumType, NewValues..., EnumVals...>;
    };

    template <std::size_t Index, typename EnumTuple>
    struct enum_tuple_element
    {
        using type                        = EnumTuple;
        static constexpr const auto index = Index;
    };

    template <std::size_t Index, typename EnumType, EnumType Head, EnumType... Tail>
    struct enum_tuple_element<Index, enum_tuple<EnumType, Head, Tail...>>
        : enum_tuple_element<Index - 1, enum_tuple<EnumType, Tail...>>
    {
        static_assert(std::is_enum_v<EnumType>);
    };

    template <typename EnumType, EnumType Head, EnumType... Tail>
    struct enum_tuple_element<0, enum_tuple<EnumType, Head, Tail...>>
    {
        using enum_type                            = EnumType;
        static constexpr const EnumType enum_value = Head;
    };

    template <std::size_t Index = 0, typename EnumTuple, typename EnumTuple::enum_type Value>
    constexpr decltype(auto) enum_tuple_index_impl()
    {
        if constexpr (enum_tuple_element<Index, EnumTuple>::enum_value == Value)
            return Index;
        else
            return enum_tuple_index_impl<Index + 1, EnumTuple, Value>();
    }

    template <typename EnumTuple, typename EnumTuple::enum_type Value>
    constexpr auto enum_tuple_index()
    {
        return enum_tuple_index_impl<0, EnumTuple, Value>();
    }

    template <typename EnumType, std::size_t EnumCount, std::size_t index, typename EnumTuple>
    constexpr decltype(auto) make_enum_tuple_impl()
    {
        if constexpr (index < EnumCount) {
            using NewTuple = typename EnumTuple::template append_enum_value<magic_enum::enum_value<EnumType>(index)>;
            return make_enum_tuple_impl<EnumType, EnumCount, index + 1, NewTuple>();
        }
        else {
            return EnumTuple{};
        }
    }

    template <typename EnumType>
    constexpr decltype(auto) make_enum_tuple()
    {
        return make_enum_tuple_impl<EnumType, magic_enum::enum_count<EnumType>(), 1,
                                    enum_tuple<EnumType, magic_enum::enum_value<EnumType>(0)>>();
    }

    template <typename EnumType, size_t... I>
    constexpr enum_tuple<EnumType, magic_enum::enum_value<EnumType>(I)...> make_enum_tuple_type_impl(std::index_sequence<I...>);

    template <typename EnumType>
    using make_enum_tuple_type = decltype( make_enum_tuple_type_impl<EnumType>( std::make_index_sequence< magic_enum::enum_count<EnumType>() >() ));

    struct enum_switch
    {
        template <std::size_t switch_size, typename EnumTuple, typename DefaultCaseFunctor,
                  template <typename EnumTuple::enum_type> typename EnumFunctor, typename... Args>
        static constexpr decltype(auto) switch_impl(typename EnumTuple::enum_type value, Args... args)
        {
            constexpr const auto enum_startindex = EnumTuple::count - switch_size;
            if constexpr (switch_size >= 4) {
                switch (value) {
                case enum_tuple_element<enum_startindex, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                case enum_tuple_element<enum_startindex + 1, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex + 1, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                case enum_tuple_element<enum_startindex + 2, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex + 2, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                case enum_tuple_element<enum_startindex + 3, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex + 3, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                default:
                    return switch_impl<switch_size - 4, EnumTuple, DefaultCaseFunctor, EnumFunctor, Args...>(
                        value, std::forward<Args>(args)...);
                }
            }
            else if constexpr (switch_size >= 2) {
                switch (value) {
                case enum_tuple_element<enum_startindex, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                case enum_tuple_element<enum_startindex + 1, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex + 1, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                default:
                    return switch_impl<switch_size - 2, EnumTuple, DefaultCaseFunctor, EnumFunctor, Args...>(
                        value, std::forward<Args>(args)...);
                }
            }
            else if constexpr (switch_size == 1) {
                switch (value) {
                case enum_tuple_element<enum_startindex, EnumTuple>::enum_value:
                    return EnumFunctor<enum_tuple_element<enum_startindex, EnumTuple>::enum_value>{}(
                        std::forward<Args>(args)...);
                default:
                    return switch_impl<switch_size - 1, EnumTuple, DefaultCaseFunctor, EnumFunctor, Args...>(
                        value, std::forward<Args>(args)...);
                }
            }
            else {
                static_assert(switch_size == 0);
                return DefaultCaseFunctor{}(std::forward<Args>(args)...);
            }
        }

        struct enum_default_switch_case
        {
            template<typename... Args>
            void operator()(Args && ... args)
            {
                throw std::out_of_range{std::format("No switch case available for the given enum value!").c_str()};
            }
        };

        template <typename EnumType, template <EnumType> typename EnumFunctor, typename DefaultCaseFunctor = enum_default_switch_case,
                  typename... Args>
        static constexpr decltype(auto) run(EnumType Value, Args &&...args)
        {
            static_assert(std::is_enum_v<EnumType>);
            using EnumTuple = decltype(make_enum_tuple<EnumType>());
            return switch_impl<EnumTuple::count, EnumTuple, DefaultCaseFunctor, EnumFunctor, Args...>(
                Value, std::forward<Args>(args)...);
        }
    };

    
    template <typename EnumType, template <EnumType> typename MappingType, EnumType... Values>
    struct enum_variant_creator
    {
        using type = std::variant<typename MappingType<Values>::type...>;
    };
    template <typename EnumType, template <EnumType> typename MappingType, EnumType... Values>
    using enum_variant_creator_t = typename enum_variant_creator<EnumType, MappingType, Values...>::type;

    template< typename EnumType >
    struct enum_type_info
    {
    };

    template< typename EnumType, template <std::remove_cvref_t<EnumType>> typename EnumVariantMapping, const auto& AllowedValues>
    struct enum_variant {
        static_assert(std::is_enum_v<std::remove_cvref_t<EnumType>>);
        template<std::remove_cvref_t<EnumType> Value>
        using enum_variant_mapping_t = EnumVariantMapping<Value>;
        template<std::remove_cvref_t<EnumType>... Values>
        using enum_variant_mapper_t = typename MyCEL::enum_variant_creator_t<std::remove_cvref_t<EnumType>, EnumVariantMapping, Values...>;
        using enum_variant_type = MyCEL::apply_nttp_t<AllowedValues,enum_variant_mapper_t>;
        using enum_type = EnumType;

        enum_type value;
        enum_variant_type variant;

        template<EnumType value>
        const auto& getEmumVariantType() const noexcept {
            using return_type = typename EnumVariantMapping<value>::type;
            return std::get<return_type>(variant);
        };
        template<EnumType value>
        auto& getEmumVariantType() noexcept {
            using return_type = typename EnumVariantMapping<value>::type;
            return std::get<return_type>(variant);
        };
    };

} // namespace MyCEL

#endif
