#include "ThreadManager.h"

#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include "../utils/ThreadDispatcher.h"
#include "../utils/HPCEnvReader.h"
#endif


std::uint64_t ThreadManager::createThreads(const std::uint64_t &NumberOfThreadsToCreate) 
{
#if defined(_WIN32)
        const utils::HPCEnvReader HPCEnv{};
#endif
        std::uint64_t counter = 0;
        const std::uint64_t create = NumberOfThreadsToCreate;
        const auto implementation = std::thread::hardware_concurrency();
        if ((NumberOfThreadsToCreate+NumberOfThreadsToCreate/10) >= implementation)
        {
            Log("Much more threads requested than supported by implementation!");
            Log(std::string{ "Requested: " } +std::to_string(create) + "\t Available: " + std::to_string(implementation));
        }
        
        for (std::uint64_t i = 0; i < create; ++i, ++counter)
        {

            try
            {
                std::thread new_thread(&ThreadManager::ThreadLoop, this);
                m_Threads.push_back(std::move(new_thread));
                //_Threads.emplace_back( &ThreadManager::ThreadLoop, this );
                //_Threads.emplace_back([this] {this->createThread(); });
                
                //_Threads.emplace_back(std::bind(&ThreadManager::createThread,this));
            }
            catch(std::exception &e) // May run into out of memory exception if too many threads are created
            {
                Log(std::string{ "Couldn't create another thread. Reason: " } + e.what());
                break;
            }
        }

#if defined(_WIN32)
        using Dispatcher = utils::ThreadDispatcher;
        using Strategy = utils::ThreadStrategy_OneThreadOneLogicalCore<void, void>;
        Dispatcher::assignThreads<Strategy>(m_Threads, HPCEnv.AssignedCores);
#endif
        
#ifdef _DEBUG
        Log(std::string{ "Created " }  +std::to_string(counter) + std::string{" threads."});
#endif
            
        return counter;
}

void ThreadManager::ThreadLoop() 
{
    for (;;) //Forever
    {
#ifdef _DEBUG
        Log("Looping");
#endif
        
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(m_TaskDequeMutex);
#ifdef _DEBUG
            m_TaskCondVar.wait(lock, [this] { 
                Log("Waiting...");
                return (this->m_stopped || !this->m_Tasks.empty());                 
            });   // Wait until dequeue is not empty or ThreadManager is stopped
#else
            m_TaskCondVar.wait(lock, [this] {
                return (this->m_stopped || !this->m_Tasks.empty());
            });   // Wait until dequeue is not empty or ThreadManager is stopped
#endif

            if (m_stopped && m_Tasks.empty())            //ThreadManager is stopped and there are no tasks left
            {
#ifdef _DEBUG
                Log("Stopped!");
#endif                    
                return;
            }

            ++m_WorkingThreads;
            task = std::move(this->m_Tasks.front());    // Get Task
            this->m_Tasks.pop_front();                // Remove Task from queue
            
        }
#ifdef _DEBUG
        Log("Performs task");
#endif
        try
        {
            task(); // Perform task;
        }
        catch (std::runtime_error &err)
        {
            Log(std::string{ "Runtime exception in task: " } +err.what());
        }
        catch(...)
        {
            Log("Unknown excpetion thrown by task!");
            //throw;
        }
        --m_WorkingThreads;
    }
}

void ThreadManager::Log(const std::string& msg)
{
    std::stringstream smsg;
    const std::thread::id tid{ std::this_thread::get_id() };

    if( m_tid != tid )
        smsg << "ThreadManager: Thread " << (tid) << ": " << msg << '\n';
    else
        smsg << "ThreadManager: " << msg << '\n';
    
    Logger::Log(smsg.str());
}

ThreadManager::ThreadManager(const std::uint64_t NumberOfThreadsToCreate) 
    : m_TaskDequeMutex(), m_TaskCondVar(), m_Tasks(), m_Threads(), m_tid(std::this_thread::get_id()), m_NumberOfThreads(createThreads(NumberOfThreadsToCreate)) {}
ThreadManager::~ThreadManager()
{
#ifdef _DEBUG
    Log("Terminating Pool");
#endif
    {
        std::unique_lock<std::mutex> lock(m_TaskDequeMutex); //Make sure no other thread of the pool is running
        m_stopped = true;
    }
    m_TaskCondVar.notify_all();

    for (std::thread &Thread : m_Threads)
    {    
        if (Thread.joinable())
            Thread.join();
    }
#ifdef _DEBUG
    Log("Threads joined");
#endif
}
