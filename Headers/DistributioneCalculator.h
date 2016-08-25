#pragma once

#ifndef _DISTRIBUTIONCALCULATOR_H_
#define _DISTRIBUTIONCALCULATOR_H_

#include <type_traits>
#include <vector>
#include <utility>
#include <random>

#include "Logger.h"

template <typename prec, typename = typename std::enable_if<std::is_floating_point<prec>::value, prec>::type >
class DistributionCalculator
{
	typedef typename std::vector<std::pair<prec, prec>> DistributionParams;
	typedef typename std::vector<unsigned long long> Weights;
private:
	Parameters::IDistribution _type = Parameters::Distribution_unknown;
	DistributionParams _values; // first in the pair is the mean wheras he second is the std deviation
	Weights _weights;
	unsigned long long _SumOfWeights = 0;

	std::random_device _randomsrc;
	//std::vector<std::random_device> _randomsrc;
	
	std::discrete_distribution<unsigned long long> _discretedist;

	std::vector<std::normal_distribution<prec>> _normaldists;
	std::vector<std::lognormal_distribution<prec>> _lognormaldists;

	//Function Pointer
	prec (DistributionCalculator<prec>::*toDistribution)(void) = nullptr;

	prec useDeltaDistribution()
	{
		size_t index = _discretedist(_randomsrc);
		return (_values.at(index)).first;
	};
	prec useNormalDistribution()
	{
		size_t index = _discretedist(_randomsrc);
		return (_normaldists.at(index))(_randomsrc);
	};
	prec useLognormalDistribution()
	{
		size_t index = _discretedist(_randomsrc);
		return (_lognormaldists.at(index))(_randomsrc);
	};
protected:
	
public:
	//DistributionCalculator() {};
	DistributionCalculator(const Parameters::IDistribution &type, const DistributionParams &values, const Weights &weights) 
		: _type(type), _values(values), _weights(weights), _randomsrc(), _discretedist(weights.begin(), weights.end())
	{
		_discretedist = std::discrete_distribution<unsigned long long>{ _weights.begin(), _weights.end() };
		switch (type)
		{
		case Parameters::IDistribution::Distribution_delta:
			this->toDistribution = &DistributionCalculator<prec>::useDeltaDistribution;
			break;
		case Parameters::IDistribution::Distribution_normal:
			for (auto &it : values)
			{
				//std::normal_distribution<prec> tmp{ values.first,values.second };
				_normaldists.emplace_back( it.first, it.second );
			}
			
			this->toDistribution = &DistributionCalculator<prec>::useNormalDistribution;
			break;
		case Parameters::IDistribution::Distribution_lognormal:
			for (auto &it : values)
			{
				//std::normal_distribution<prec> tmp{ values.first,values.second };
				double meansquare = std::pow(it.first,2);
				double var = std::pow(it.second, 2);
				double meanlog = std::log(meansquare/std::sqrt(var+meansquare));
				double stdlog = std::log(1+var/meansquare);
				_lognormaldists.emplace_back(meanlog,stdlog );
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
#endif