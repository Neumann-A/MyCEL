#include "BasicIncludes.h"

namespace BasicTools
{
    template<>
    float stringToNumber<float>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stof(stringtoconvert, &pos);
    }

    template<>
    double stringToNumber<double>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stod(stringtoconvert, &pos);
    }

    template<>
    long double stringToNumber<long double>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stold(stringtoconvert, &pos);
    }

    template<>
    short stringToNumber<short>(const std::string& stringtoconvert, size_t& pos)
    {
        return (short)(std::stoi(stringtoconvert, &pos));
    }

    template<>
    unsigned short stringToNumber<unsigned short>(const std::string& stringtoconvert, size_t& pos)
    {
        return (unsigned short)(std::stoul(stringtoconvert, &pos));
    }

    template<>
    int stringToNumber<int>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stoi(stringtoconvert, &pos);
    }

    template<>
    unsigned int stringToNumber<unsigned int>(const std::string& stringtoconvert, size_t& pos)
    {
        return (unsigned int)(std::stoul(stringtoconvert, &pos));
    }

    template<>
    long stringToNumber<long>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stol(stringtoconvert, &pos);
    }

    template<>
    unsigned long stringToNumber<unsigned long>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stoul(stringtoconvert, &pos);
    }

    template<>
    long long stringToNumber<long long>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stoll(stringtoconvert, &pos);
    }

    template<>
    unsigned long long stringToNumber<unsigned long long>(const std::string& stringtoconvert, size_t& pos)
    {
        return std::stoull(stringtoconvert, &pos);
    }
    //std::string toStringScientific(float num)
    //{
    //	std::stringstream str;
    //	str << std::scientific << num;
    //	return str.str();
    //}
    //std::string toStringScientific(double num)
    //{
    //	std::stringstream str;
    //	str << std::scientific << num;
    //	return str.str();
    //}
    //std::string toStringScientific(long double num)
    //{
    //	std::stringstream str;
    //	str << std::scientific << num;
    //	return str.str();
    //}
    //std::string toStringScientific(int num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
    //std::string toStringScientific(unsigned int num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
    //std::string toStringScientific(long num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
    //std::string toStringScientific(unsigned long num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
    //std::string toStringScientific(long long num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
    //std::string toStringScientific(unsigned long long num)
    //{
    //	std::stringstream str;
    //	str << std::setprecision(0) << num;
    //	return str.str();
    //}
}
