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
#include "../basics/BasicMacros.h"

#include <algorithm>
#include <type_traits>
#include <vector>
#include <utility>
#include <map>
#include <random>
#include <string>

#include "../basics/Logger.h"
#include "random_helpers.h"



namespace Distribution
{
	enum class IDistribution { Distribution_unknown, Distribution_delta, Distribution_normal, Distribution_lognormal, Distribution_gamma };
	extern const std::map<IDistribution, std::string> IDistributionMap;

	std::string to_string(const IDistribution& field);


	template<typename T>
	T from_string(const std::string &String);
	template<>
	IDistribution from_string<IDistribution>(const std::string &String);

	template<typename ReturnValue>
	class IDistributionHelper
	{
		using ThisClass = IDistributionHelper<ReturnValue>;
		MY_VIRTUAL_INTERFACE(IDistributionHelper)
	protected:
		IDistributionHelper(const ThisClass&) = default;
		ThisClass& operator=(const ThisClass&) = default;
		IDistributionHelper(ThisClass&&) = default;
		ThisClass& operator=(ThisClass&&) = default;
	public:
		virtual ReturnValue getValueFromDistribution() = 0;
	};

	template<typename prec>
	class DeltaDistribution : public IDistributionHelper<prec>
	{
	private:
		prec deltavalue;
	public:
		explicit DeltaDistribution(const prec& value) : deltavalue(value) {};
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
		//TODO: use better init for PNG see noisefield!
		template <typename T = distribution>
		explicit DistributionHelper(const prec &value, typename std::enable_if_t<std::is_same<T, std::discrete_distribution<prec>>::value, prec>* = nullptr)
            :_distribution(distribution{ value }), _prng(math::random_helpers::create_seeded_PRNG<std::mt19937_64>(std::random_device{}))
		{
			_prng.discard(10'000'000);
		}
		explicit DistributionHelper(const DistributionParams &values)
			: _distribution(distribution{ values.first, values.second }),
			_prng(math::random_helpers::create_seeded_PRNG<std::mt19937_64>(std::random_device{}))
		{
			_prng.discard(10'000'000);
		};

		prec getValueFromDistribution() override final
		{
			return _distribution(_prng);
		}
	};

	template <typename inttype>
	class DistributionHelperDiscrete : public IDistributionHelper<inttype>
	{
		static_assert(std::is_integral<inttype>::value, "This class is only for integral types!");
	private:
		std::discrete_distribution<inttype> _distribution;
		std::mt19937_64 _prng;

	protected:

	public:
		//TODO: use better init for PNG see noisefield!
		//TODO: Silence stupid compiler warning due to implicit conversion from inttype to double!
		explicit DistributionHelperDiscrete(const std::vector<inttype>& values)
			:_distribution(values.begin(), values.end()), _prng(math::random_helpers::create_seeded_PRNG<std::mt19937_64>(std::random_device{}))
		{
			_prng.discard(10'000'000);
		}
		inttype getValueFromDistribution() override final
		{
			return _distribution(_prng);
		}

	};

};
#endif	// INC_DistributionHelper_H
// end of DistributionHelper.h
///---------------------------------------------------------------------------------------------------
