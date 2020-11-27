///---------------------------------------------------------------------------------------------------
// file:		ThreadDispatcher.h
//
// summary: 	Declares the thread dispatcher class
//
// Copyright (c) 2018 Alexander Neumann.
//
// author: Neumann
// date: 20.07.2018

#ifndef INC_ThreadDispatcher_H
#define INC_ThreadDispatcher_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <thread>
#include <vector>

#include "CoreInfo.h"

#if defined(WIN32)
namespace utils
{
    struct ThreadDispatcher
    {
        template<typename Strategy>
        static void assignThreads(std::vector<std::thread>& threads, const std::vector<std::size_t>& assignedCores)
        {
            AllCoreInfo allcores{};
            Strategy::dispatchThreads(threads, assignedCores, allcores);
        }
    };

    struct ThreadStrategy_DummyCreator
    {
        static void dispatchThreads(std::vector<std::thread>& threads, const std::vector<std::size_t>& assignedCores, MAYBE_UNUSED const AllCoreInfo& allcores)
        {
			MAYBE_UNUSED const bool undersubscribed = threads.size() < assignedCores.size();
            MAYBE_UNUSED const bool oversubscribed = threads.size() > assignedCores.size();
			//TODO:
        }
    };

    template<typename UndersubscriptionStrategy, typename OversubscriptionStrategy>
    struct ThreadStrategy_OneThreadOnePhysicalCore
    {
        static void dispatchThreads(std::vector<std::thread>& threads, const std::vector<std::size_t>& assignedCores, const AllCoreInfo& allcores)
        {
            const bool undersubscribed = threads.size() < assignedCores.size();
            const bool oversubscribed = threads.size() > assignedCores.size();
        }
    };

    template<typename UndersubscriptionStrategy, typename OversubscriptionStrategy>
    struct ThreadStrategy_OneThreadOneLogicalCore
    {
        static void dispatchThreads(std::vector<std::thread>& threads, const std::vector<std::size_t>& assignedCores, AllCoreInfo& allcores)
        {
            const auto noThreads = threads.size();
            const auto noCores = assignedCores.size();
            const bool undersubscribed = noThreads < noCores;
            const bool oversubscribed = noThreads > noCores;


            if (undersubscribed)
            {

            }
            else
            {
                const auto limit = oversubscribed ? noCores : noThreads;
                for (std::size_t i = 0; i < limit; ++i)
                {
                    const auto coreid = assignedCores[i];
                    auto coreinfo = allcores.getLogicalCore(coreid);
                    const auto& handle = threads[i].native_handle();
                    if (coreinfo)
                    {
                        const GROUP_AFFINITY toSet{ coreinfo->GroupMask.to_ullong(),coreinfo->Group,{0,0,0} };
                        //toSet.Group = coreinfo->Group;
                        //toSet.Mask = coreinfo->GroupMask.to_ullong();		

                        const auto success = SetThreadGroupAffinity(handle, &toSet, nullptr);
                        if (!success)
                        {
                            std::cout << "ThreadDispatcher: Unable to change Thread affinity! Error: " << GetLastError() << '\n';
                            SetLastError(0);
                        }

                    }
                    else
                    {
                        throw std::runtime_error{ "ThreadDispatcher: Assigned logical core does not exist or is not active!\n" };
                    }
                }

                if (oversubscribed)
                {

                }
            }


        }
    };

    struct ThreadStrategy_OneThreadOneLogicalCore_PhysicalFirst
    {
    };

    struct ThreadStrategy_OversubscribedStrategy_AllCoresEqual
    {

    };

    struct ThreadStrategy_OversubscribedStrategy_SingleCoreRandom
    {

    };

    struct ThreadStrategy_UndersubscribedStrategy_Nothing
    {

    };

}

#endif

#endif	// INC_ThreadDispatcher_H
// end of ThreadDispatcher.h
///---------------------------------------------------------------------------------------------------
