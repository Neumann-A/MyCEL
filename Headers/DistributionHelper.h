///---------------------------------------------------------------------------------------------------
// file:		DistributionHelper.h
//
// summary: 	Declares the distribution helper class
//
// Copyright (c) 2016 Alexander Neumann.
//
// author: Alexander Neumann
// date: 06.06.2016

#ifndef INC_DistributionHelper_H
#define INC_DistributionHelper_H
///---------------------------------------------------------------------------------------------------
#pragma once
#include "BasicMacros.h"

#include <type_traits>
#include <vector>
#include <utility>
#include <random>
#include <map>

#include "Logger.h"

enum class IDistribution { Distribution_unknown, Distribution_delta, Distribution_normal, Distribution_lognormal };
const std::map<IDistribution, std::string> IDistributionMap{ { { IDistribution::Distribution_unknown,"unknown" },{ IDistribution::Distribution_delta,"delta" } ,{ IDistribution::Distribution_normal,"normal" },{ IDistribution::Distribution_lognormal,"lognormal" } } };

// Interface functions which converts a string to an enum
IDistribution getIDistribution(const std::string &string) noexcept
{
	for (const auto& it : IDistributionMap)
		if (it.second == string)
			return it.first;

	Logger::Log(std::string{ "Type of Distribution unknown! Requested Type: " } +string);
	return IDistribution::Distribution_unknown;
};

template<typename ReturnValue>
class IDistributionHelper
{
	MY_VIRTUAL_INTERFACE(IDistributionHelper)
public:
	virtual ReturnValue getValueFromDistribution() = 0;
};

template<typename prec>
class DeltaDistribution : public IDistributionHelper<prec>
{
private:
	prec deltavalue;
public:
	DeltaDistribution(const prec& value) : deltavalue(value) {};
	prec getValueFromDistribution() override final { return deltavalue; };

};

template <typename prec, typename distribution >
class DistributionHelper : public IDistributionHelper<prec>
{
private:
	typedef typename std::pair<prec, prec> DistributionParams;

	distribution _distribution;
	std::mt19937_64 _prng;
public:
	template <typename T = distribution>
	DistributionHelper(const prec &value, typename std::enable_if_t<std::is_same<T, std::discrete_distribution<prec>>::value, prec>* = nullptr)
		:_distribution(distribution{ value }),	_prng((std::random_device{})())
	{
		for (int i = 0; i <= 1000000; ++i)
			_prng();
	}
	DistributionHelper(const DistributionParams &values)
		: _distribution(distribution{ values.first, values.second }),
		_prng(std::random_device{}())
	{
		for (int i = 0; i <= 1000000; i += 1)
			_prng();
	};

	prec getValueFromDistribution() override final
	{
		return _distribution(_prng);
	}

};

template <typename inttype>
class DistributionHelperDiscrete : public IDistributionHelper<inttype>
{
private:
	std::discrete_distribution<inttype> _distribution;
	std::mt19937_64 _prng;

protected:

public:
	DistributionHelperDiscrete(const std::vector<inttype>& values)
		:_distribution( values.begin(),values.end() ), _prng((std::random_device{})())
	{
		for (int i = 0; i <= 1000000; ++i)
			_prng();
	}
	inttype getValueFromDistribution() override final
	{
		return _distribution(_prng);
	}

};

#endif	// INC_DistributionHelper_H
// end of DistributionHelper.h
///---------------------------------------------------------------------------------------------------
