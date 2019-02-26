///---------------------------------------------------------------------------------------------------
// file:		random_helpers.h
//
// summary: 	Helper header to deal with random number generators (seeding etc. )
//
// Copyright (c) 2019 Alexander Neumann.
//
// author: Alexander Neumann
// date: 26.02.2019
///---------------------------------------------------------------------------------------------------
#pragma once

#include <array>
#include <random>

#ifdef USE_PCG_RANDOM
#include <pcg_extras.hpp> // For pcg_extras::seed_seq_from
#else
namespace pcg_extras
{
    template<typename T>
    using seed_seq_from = std::seed_seq;
}
#endif

namespace math::random_helpers
{
    namespace pcg_helper
    {
        template<typename Gen, typename void_t = std::void_t<> >
        struct is_pcg_random : std::false_type {};

        //TODO: Implement a better check for pcg random and move the check somewhere else!
        template<typename Gen>
        struct is_pcg_random<Gen, std::void_t<decltype(std::declval<Gen&>().period_pow2)>> : std::true_type { };

        template<typename Gen>
        constexpr bool is_pcg_random_v = is_pcg_random<Gen>::value;
    }
    
    template<typename Generator, typename EntropySource>
    Generator create_seeded_PRNG(EntropySource&& src)
    {
        if constexpr (pcg_helper::is_pcg_random_v<Generator>)
        {
            pcg_extras::seed_seq_from<std::random_device> seq;
            return Generator{ seq };
        }
        else
        {
            std::array<EntropySource::result_type, Generator::state_size> seed_data;
            std::generate(seed_data.begin(), seed_data.end(), [&]() {return src(); });
            std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
            return Generator{ seq };
        }
    };
}
///---------------------------------------------------------------------------------------------------