#include "DistributionHelper.h"
#include <exception>


namespace Distribution
{
    const std::map<IDistribution, std::string> IDistributionMap = { { { IDistribution::Distribution_unknown,"unknown" },
		                                                              { IDistribution::Distribution_delta,"delta" },
                                                                      { IDistribution::Distribution_normal,"normal" },
                                                                      { IDistribution::Distribution_lognormal,"lognormal" },
                                                                      { IDistribution::Distribution_gamma,"gamma" } } };
    template<>
    IDistribution from_string<IDistribution>(const std::string &String) //TODO: Remoe inline move to cpp; currently gives linker errors!
	{
		for (auto it : IDistributionMap)
			if (it.second == String)
				return it.first;

		throw std::runtime_error{ std::string{ "Type of Distribution unknown! " } +String };
	};

    std::string to_string(const IDistribution& field)
	{
		return IDistributionMap.at(field);
	};
}
