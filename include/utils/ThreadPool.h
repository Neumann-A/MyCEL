///---------------------------------------------------------------------------------------------------
// file:		C:\Sources\Repos\Everything\Basic_Library\utils\ThreadPool.h
//
// summary: 	Declares the thread pool class. A simple threadpool which stores created threads. 
//              Threads are requested by executors to perform tasks
//
// Copyright (c) 2018 Alexander Neumann.
//
// author: Neumann
// date: 27.11.2018

#ifndef INC_ThreadPool_H
#define INC_ThreadPool_H
///---------------------------------------------------------------------------------------------------

#endif	// INC_ThreadPool_H
// end of C:\Sources\Repos\Everything\Basic_Library\utils\ThreadPool.h
///---------------------------------------------------------------------------------------------------

#include <cstddef>
#include <functional>
#include <optional>
#include <vector>

//Threading related
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
#include <condition_variable>

//Own includes
#include "ThreadDispatcher.h"


template <typename Task>
class GeneralTask
{
    std::packaged_task<Task> _task;
public:
    operator std::packaged_task<void()>() { return static_cast<std::packaged_task<void()>>(_task); };
};

/// <summary>   A worker thread.  </summary>
template<typename PoolType, typename TaskType>
class WorkerThread
{
    friend PoolType;
public:
    std::optional<TaskType> task;
    std::condition_variable& cv;
    std::atomic<bool>        running{false};
    PoolType&                owningPool;

    const std::thread::id   id;
    
    WorkerThread(PoolType& pool) ;
    ~WorkerThread();

    WorkerThread(const WorkerThread&) = delete;
    WorkerThread& operator=(const WorkerThread&) = delete;

    bool performingTask() noexcept const { return running.load(std::memory_order_relaxed); }
private:
};

class ThreadPool
{
private:
    struct ThreadHandle
    {
        std::condition_variable cv;
        std::optional<std::packaged_task<void()>> task;
    };

    std::mutex               _poolmutex;
    std::vector<std::thread> _pool;
    std::thread::id          _owner;

    template<typename AffinityStrategy>
    void setAffinities();

public:
    ThreadPool(std::size_t to_spawn) 
    {
        //We have to create at least 1 Thread
        assert(to_spawn > 0);
        //Reserve memory for all threads at the beginning
        _pool.reserve(to_spawn);

        do
        {

        } while (--to_spawn);
    };
    ~ThreadPool() 
    {
        assert()
        for (auto thread& : _pool)
        {
            if (thread.joinable())
                thead.join();
        }
    };

    template<typename TaskType>
    WorkerThread<ThreadPool, TaskType> getWorker() noexcept
    {

    };
    template<typename TaskType>
    void returnWorker(WorkerThread<ThreadPool, TaskType>& worker) const noexcept;
}