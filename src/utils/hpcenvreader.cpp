///-------------------------------------------------------------------------------------------------
// summary:	Implements the hpc environment reader class
///-------------------------------------------------------------------------------------------------

#include "HPCEnvReader.h"
#include <charconv>
#include <cassert>

#ifdef WIN32
namespace utils
{
    HPCEnvReader::HPCEnvReader() :
        AssignedCores(createCoreList(readEnviormentVariable("CCP_COREIDS").get()))
    { };
       
    std::vector<std::size_t> HPCEnvReader::createCoreList(char* envvar)
    {
        if (envvar != nullptr)
        {
            constexpr char delimiter[] = " ";
            char* next_token = nullptr;
            auto token = strtok_s(envvar, delimiter, &next_token);
            std::vector<std::size_t> vec;
            while (token != nullptr)
            {
                std::size_t number;
                [[maybe_unused]] const auto res = std::from_chars(token, token + strlen(token), number);
                assert(res.ec == std::errc());
                vec.emplace_back(std::move(number));
                token = strtok_s(nullptr, delimiter, &next_token);
            }
            return vec;
        }
        return {};
    }
}
#endif
