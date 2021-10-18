#pragma once

#ifndef _DISTRIBUTIONCALCULATOR_H_
#define _DISTRIBUTIONCALCULATOR_H_

#include <cassert>

#include <type_traits>
#include <vector>
#include <utility>

#include <random>
#include "..\math\random_helpers.h"

#include "DistributionHelper.h"

namespace Distribution {

    template <typename prec, typename = typename std::enable_if<std::is_floating_point<prec>::value, prec>::type >
    class DistributionCalculator
    {
        typedef typename std::vector<std::pair<prec, prec>> DistributionParams;
        typedef typename std::vector<std::size_t> Weights;
    private:
        IDistribution mType = IDistribution::Distribution_unknown;
        DistributionParams mValues; // first in the pair is the mean wheras he second is the std deviation
        Weights mWeights;
        std::size_t mSumOfWeights = 0;

        std::random_device mRnd;
        std::discrete_distribution<std::size_t> mDiscreteDist;

        struct UsedDist
        {
            std::vector<std::normal_distribution<prec>> normal;
            std::vector<std::lognormal_distribution<prec>> lognormal;
            std::vector<std::gamma_distribution<prec>> gamma;
        };

        UsedDist mDistribution;

        //Function Pointer
        prec(DistributionCalculator<prec>::*toDistribution)(void) = nullptr;

        prec useDeltaDistribution()
        {
            const size_t index = mDiscreteDist(mRnd);
            return (mValues.at(index)).first;
        };
        prec useNormalDistribution()
        {
            const size_t index = mDiscreteDist(mRnd);
            return (mDistribution.normal.at(index))(mRnd);
        };
        prec useLognormalDistribution()
        {
            const size_t index = mDiscreteDist(mRnd);
            return (mDistribution.lognormal.at(index))(mRnd);
        };
        prec useGammeDistribution() 
        {
            const size_t index = mDiscreteDist(mRnd);
            return (mDistribution.gamma.at(index))(mRnd);
        }
    protected:

    public:
        //DistributionCalculator() {};
        DistributionCalculator(const Parameters::IDistribution &type, const DistributionParams &values, const Weights &weights)
            : mType(type), mValues(values), mWeights(weights), mRnd(), mDiscreteDist(weights.begin(), weights.end())
        {
            assert(mWeights.size() >= 1);
            mDiscreteDist = std::discrete_distribution<std::size_t>{ mWeights.begin(), mWeights.end() };

            switch (type)
            {
            case IDistribution::Distribution_delta:
                this->toDistribution = &DistributionCalculator<prec>::useDeltaDistribution;
                break;
            case IDistribution::Distribution_normal:
                for (auto &it : values)
                {
                    //std::normal_distribution<prec> tmp{ values.first,values.second };
                    mDistribution.normal.emplace_back(it.first, it.second);
                }
                this->toDistribution = &DistributionCalculator<prec>::useNormalDistribution;
                break;
            case IDistribution::Distribution_lognormal:
                for (auto &it : values)
                {
                    //std::normal_distribution<prec> tmp{ values.first,values.second };
                    double meansquare = std::pow(it.first, 2);
                    double var = std::pow(it.second, 2);
                    double meanlog = std::log(meansquare / std::sqrt(var + meansquare));
                    double stdlog = std::log1p(var / meansquare);
                    mDistribution.lognormal.emplace_back(meanlog, stdlog);
                }
                this->toDistribution = &DistributionCalculator<prec>::useLognormalDistribution;
                break;
            }
        };
        virtual ~DistributionCalculator() {};

        prec getValue()
        {
            return (this->*toDistribution)();
        }

    };
}
#endif