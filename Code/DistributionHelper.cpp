#include "..\Headers\DistributionHelper.h"

std::string to_string(const IDistribution& field)
{
	return IDistributionMap.at(field);
};

template<>
IDistribution from_string<IDistribution>(const std::string &String)
{
	for (auto it : IDistributionMap)
		if (it.second == String)
			return it.first;

	throw std::runtime_error{ std::string{ "Type of Distribution unknown! " } +String };
};