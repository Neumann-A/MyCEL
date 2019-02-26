///-------------------------------------------------------------------------------------------------
// file:	C:\Sources\Repos\Everything\Basic_Library\utils\CoreInfo.cpp
//
// summary:	Implements the core information class
///-------------------------------------------------------------------------------------------------

#include "CoreInfo.h"

#include <numeric>
#include <limits>

namespace utils
{
    PhysicalCoreInfo::PhysicalCoreInfo(std::uint8_t grp, const std::uint64_t msk, const std::size_t CoreOffset)
    {
        std::bitset<64> mask{ msk };
        assert(mask.any());
        for (std::size_t i = 0; i < mask.size(); i++)
        {
            if (mask[i])
            {
                std::bitset<64> newmask{ 0 };
                newmask[i] = 1;
                const auto CoreNumber{ CoreOffset + i };
                Cores.emplace_back(grp, newmask.to_ullong(), CoreNumber);
            }
        }
    }

    std::optional<LogicalCoreInfo> PhysicalCoreInfo::getCore(const std::uint64_t& CoreNumber) const noexcept
    {
        for (const auto& core : Cores) {
            if (core.CoreNumber == CoreNumber)
            {
                return std::optional<LogicalCoreInfo>{ core };
            }
        }
        return {};
    }

    auto PhysicalCoreInfo::getGroupMask() const noexcept
    {
        std::bitset<64> res{ 0 };
        for (const auto& elem : Cores)
        {
            res |= elem.GroupMask;
        }
        return res;
    }

    auto PhysicalCoreInfo::getCoreList() const
    {
        std::vector<std::size_t> res;
        for (const auto& elem : Cores)
        {
            res.emplace_back(elem.CoreNumber);
        }

        return res;
    }

    bool PhysicalCoreInfo::operator==(const PhysicalCoreInfo& core2) const noexcept
    {
        return this->Cores[1] == core2.Cores[1];
    }

    AllCoreInfo::AllCoreInfo()
    {
        //First get Group info;
        auto noGroups = GetActiveProcessorGroupCount();

        GroupSize = std::vector<std::size_t>(noGroups);
        assert(std::numeric_limits<WORD>::max() >= GroupSize.size()); // If not we have a more serious problem -> Windows API change?
        for (WORD idx = 0; idx < GroupSize.size(); idx++)
        {
            GroupSize[idx] = GetActiveProcessorCount(idx);
        }

        std::vector<std::size_t> CoreOffset(noGroups, 0);
        std::partial_sum(GroupSize.begin(), GroupSize.end() - 1, CoreOffset.begin() + 1);

        // This lists all PhysicalCores in the system;
        for (EnumLogicalProcessorInformation enumInfo(RelationProcessorCore);
            auto pelem = enumInfo.Current(); enumInfo.MoveNext())
        {
            //const SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX& elem = *pelem;
            const auto CurrGroupNo{ (std::size_t)pelem->Processor.GroupMask->Group };

            const auto CurrGroupMask{ pelem->Processor.GroupMask->Mask };

            PhysicalCores.emplace_back(CurrGroupNo, CurrGroupMask, CoreOffset[CurrGroupNo]);
        }
    }

    std::optional<LogicalCoreInfo> AllCoreInfo::getLogicalCore(const std::uint64_t& CoreNumber) const noexcept
    {
        for (const auto& pcore : PhysicalCores)
        {
            const auto& lcore{ pcore.getCore(CoreNumber) };
            if (lcore) {
                return std::optional<LogicalCoreInfo>{ lcore };
            }
        }
        return {};
    }

    std::optional<PhysicalCoreInfo> AllCoreInfo::getPhysicalCore(const std::uint64_t& CoreNumber) const noexcept
    {
        for (const auto& pcore : PhysicalCores)
        {
            const auto& lcore{ pcore.getCore(CoreNumber) };
            if (lcore) {
                return PhysicalCoreInfo{ pcore };
            }
        }

        return {};
    }

    bool AllCoreInfo::isSameCore(const std::uint64_t& CoreNumber1, const std::uint64_t& CoreNumber2)
    {
        return (getPhysicalCore(CoreNumber1) == getPhysicalCore(CoreNumber2));
    }

}
