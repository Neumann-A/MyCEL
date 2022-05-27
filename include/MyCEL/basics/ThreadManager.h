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
    std::atomic<bool>                   m_stopped{ false };  // ThreadManager was stopped
    std::mutex                          m_TaskDequeMutex;    // Mutex for the Task list
    std::condition_variable             m_TaskCondVar;       // Condition variable to wake sleeping threads waiting for the task list to update
    std::deque<std::function<void()>>   m_Tasks;             // List with Task 
    std::vector<std::thread>            m_Threads;           // Threads

    const std::thread::id        m_tid;                // Thread ID of the owner of the ThreadManager
    std::uint64_t                m_NumberOfThreads;   // NumberOfCreated Threads 
    std::atomic<std::uint64_t>   m_WorkingThreads{ 0 };// Number of Working Threads

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
            std::unique_lock<std::mutex> lock(m_TaskDequeMutex);

            // don't allow enqueueing after stopping the pool
            if (m_stopped)
                throw std::runtime_error("Tried to enque Task in stopped ThreadManager");

            m_Tasks.emplace_back([task]() { (*task)(); });
        }
        m_TaskCondVar.notify_one();
#ifdef _DEBUG
        Log("Task added");
#endif
        return res;
    }

    inline std::uint64_t getNumberOfWorkingThreads() const BASIC_NOEXCEPT { return m_WorkingThreads.load(); };
};

#endif //_THREADMANAGER_H_
