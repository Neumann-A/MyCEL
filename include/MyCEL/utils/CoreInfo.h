///---------------------------------------------------------------------------------------------------
// file:		CoreInfo.h
//
// summary: 	Declares classes to handle core information
//
// Copyright (c) 2018 Alexander Neumann.
//
// author: Neumann
// date: 20.07.2018

#ifndef INC_ProcessorInfo_H
#define INC_ProcessorInfo_H
///---------------------------------------------------------------------------------------------------
#pragma once
#include <cassert>
#include <cstdint>
#include <utility>
#include <bitset>
#include <vector>
#include <optional>

#include "ProcessorInformation.h"

#ifdef WIN32
namespace utils {
    // A single logical Core
    struct LogicalCoreInfo
    {
        std::uint8_t	Group;
        std::bitset<64>	GroupMask;
        std::size_t		CoreNumber;

        inline explicit LogicalCoreInfo(std::uint8_t grp, std::uint64_t msk, std::size_t no) noexcept
            : Group(std::move(grp)), GroupMask(std::move(msk)), CoreNumber(std::move(no))
        {
            assert(GroupMask.count() == 1);
        };

        inline explicit LogicalCoreInfo(const LogicalCoreInfo& info) noexcept
            : Group(info.Group), GroupMask(info.GroupMask), CoreNumber(info.CoreNumber)
        {
            assert(GroupMask.count() == 1);
        };

        inline explicit LogicalCoreInfo(LogicalCoreInfo&& info) noexcept
            : Group(std::move(info.Group)), GroupMask(std::move(info.GroupMask)), CoreNumber(std::move(info.CoreNumber))
        {
            assert(GroupMask.count() == 1);
        };

        inline bool operator==(const LogicalCoreInfo& core2) const noexcept
        {
            return (this->CoreNumber == core2.CoreNumber);
        }
    };

    // A physical core consist of one or more logical cores
    class PhysicalCoreInfo
    {
    public:
        std::vector<LogicalCoreInfo> Cores;

        explicit PhysicalCoreInfo(std::uint8_t grp, const std::uint64_t msk, const std::size_t CoreOffset);
        std::optional<LogicalCoreInfo> getCore(const std::uint64_t& CoreNumber) const noexcept;
        auto getGroupMask() const noexcept;
        auto getCoreList() const;
        bool operator==(const PhysicalCoreInfo& core2) const noexcept;
    };

    class AllCoreInfo
    {
    public:
        std::vector<PhysicalCoreInfo> PhysicalCores;
        std::vector<std::size_t>	  GroupSize;
        //std::vector<PhysicalCoreInfo> ActiveCores; <- Cannot be extracted since we cannot find out the Group where active cores are. 

        AllCoreInfo();

        std::optional<LogicalCoreInfo> getLogicalCore(const std::uint64_t& CoreNumber) const noexcept;

        std::optional<PhysicalCoreInfo> getPhysicalCore(const std::uint64_t& CoreNumber) const noexcept;

        bool isSameCore(const std::uint64_t& CoreNumber1, const std::uint64_t& CoreNumber2);
    };
}

#endif

#endif	// INC_ProcessorInfo_H
// end of ProcessorInfo.h
///---------------------------------------------------------------------------------------------------
