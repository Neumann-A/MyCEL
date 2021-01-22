#pragma once

//http://progsch.net/wordpress/?p=81
//https://github.com/progschj/ThreadManager

#ifndef INC_THREADMANAGER_H_
#define INC_THREADMANAGER_H_

//rename to thread manager

#include "BasicMacros.h"
#include "Logger.h"

#include <cstdint>
#include <string>
#include <vector>
#include <queue>

#include <memory>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include <functional>
#include <stdexcept>

// ThreadManager Class
// A Class for holding a number of threads.
class ThreadManager
{
private:
    DISALLOW_COPY_AND_ASSIGN(ThreadManager)

    //For synchronization
    std::mutex _TaskDequeMutex;                        // Mutex for the Task list
    std::condition_variable _TaskCondVar;            // Condition variable to wake sleeping threads waiting for the task list to update
    std::vector<std::thread>     _Threads;            // Threads

    std::atomic<bool>            _stopped{ false };    // ThreadManager was stopped
    const std::thread::id        _tid;                // Thread ID of the owner of the ThreadManager
    std::uint64_t                _NumberOfThreads;   // NumberOfCreated Threads 
    std::atomic<std::uint64_t>   _WorkingThreads{ 0 };// Number of Working Threads



    std::deque<std::function<void()>> _Tasks;        // List with Task 

    std::uint64_t createThreads(const std::uint64_t &NumberOfThreadsToCreate);

    void ThreadLoop();

    void Log(const std::string& msg);

protected:
public:
    ThreadManager(const std::uint64_t NumberOfThreadsToCreate);
    ~ThreadManager();

    // Add Task to Task Deque
    template<class Func, class... Args>
    auto AddTask(Func&& func, Args&&... args) noexcept(false)
        -> std::future<typename std::invoke_result_t<Func,Args...>>
    {
        using return_type = typename std::invoke_result_t<Func,Args...>;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(_TaskDequeMutex);

            // don't allow enqueueing after stopping the pool
            if (_stopped)
                throw std::runtime_error("Tried to enque Task in stopped ThreadManager");

            _Tasks.emplace_back([task]() { (*task)(); });
        }
        _TaskCondVar.notify_one();
#ifdef _DEBUG
        Log("Task added");
#endif
        return res;
    }

    inline std::uint64_t getNumberOfWorkingThreads() const BASIC_NOEXCEPT { return _WorkingThreads.load(); };
};

#endif //_THREADMANAGER_H_
