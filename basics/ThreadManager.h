#pragma once

//http://progsch.net/wordpress/?p=81
//https://github.com/progschj/ThreadManager

#ifndef INC_THREADMANAGER_H_
#define INC_THREADMANAGER_H_

//rename to thread manager

#include "BasicMacros.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdint>

#include <memory>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include <functional>
#include <stdexcept>

#ifdef _WIN32
#include "../../Playground/ThreadAffinity/ThreadDispatcher.h"
#include "../../Playground/ThreadAffinity/HPCEnvReader.h"
#endif

// ThreadManager Class
// A Class for holding a number of threads.
class ThreadManager
{
private:
	DISALLOW_COPY_AND_ASSIGN(ThreadManager)

	std::atomic<bool>			_stopped{ false };	// ThreadManager was stopped
	uint64_t					_NumberOfThreads;   // NumberOfCreated Threads 
	std::atomic<uint64_t>		_WorkingThreads{ 0 };// Number of Working Threads
	const std::thread::id		_tid;				// Thread ID of the owner of the ThreadManager
	std::vector<std::thread>	_Threads;			// Threads

	std::deque<std::function<void()>> _Tasks;		// List with Task 

	//For synchronization
	std::mutex _TaskDequeMutex;						// Mutex for the Task list
	std::condition_variable _TaskCondVar;			// Condition variable to wake sleeping threads waiting for the task list to update

	uint64_t createThreads(const uint64_t &NumberOfThreadsToCreate)
	{

#ifdef _WIN32
		const HPCEnvReader HPCEnv{};
#endif

		uint64_t counter = 0;
		const uint64_t create = NumberOfThreadsToCreate;
		const auto implementation = std::thread::hardware_concurrency();
		if (NumberOfThreadsToCreate*1.1 >= implementation)
		{
			Log("Much more threads requested than supported by implementation!");
			Log(std::string{ "Requested: " } +std::to_string(create) + "\t Available: " + std::to_string(implementation));
		}
		
		for (uint64_t i = 0; i < create; ++i, ++counter)
		{

			try
			{
				_Threads.emplace_back([this] {this->createThread(); });
				
				//_Threads.emplace_back(std::bind(&ThreadManager::createThread,this));
			}
			catch(std::exception &e) // May run into out of memory exception if too many threads are created
			{
				Log(std::string{ "Couldn't create another thread. Reason: " } + e.what());
				break;
			}
		}

#ifdef _WIN32
		using Dispatcher = ThreadDispatcher;
		using Strategy = ThreadStrategy_OneThreadOneLogicalCore<void, void>;
		Dispatcher::assignThreads<Strategy>(_Threads, HPCEnv.AssignedCores);
#endif
		
#ifdef _DEBUG
		Log(std::string{ "Created " }  +std::to_string(counter) + std::string{" threads."});
#endif
			
		return counter;
	};

	void createThread()
	{
		for (;;) //Forever
		{
#ifdef _DEBUG
			Log("Looping");
#endif
			
			std::function<void()> task;

			{
				std::unique_lock<std::mutex> lock(_TaskDequeMutex);
#ifdef _DEBUG
				_TaskCondVar.wait(lock, [this] 	{ 
					Log("Waiting...");
					return (this->_stopped || !this->_Tasks.empty()); 				
				});   // Wait until dequeue is not empty or ThreadManager is stopped
#else
				_TaskCondVar.wait(lock, [this] {
					return (this->_stopped || !this->_Tasks.empty());
				});   // Wait until dequeue is not empty or ThreadManager is stopped
#endif

				if (_stopped && _Tasks.empty())			//ThreadManager is stopped and there are no tasks left
				{
#ifdef _DEBUG
					Log("Stopped!");
#endif					
					return;
				}

				++_WorkingThreads;
				task = std::move(this->_Tasks.front());	// Get Task
				this->_Tasks.pop_front();				// Remove Task from queue
				
			}
#ifdef _DEBUG
			Log("Performs task");
#endif
			task(); // Perform task;
			--_WorkingThreads;
		}

	};

	void stopThreads()
	{
		
	};

	void Log(std::string msg)
	{
		std::stringstream smsg;
		const std::thread::id tid{ std::this_thread::get_id() };

		if( _tid != tid )
			smsg << "ThreadManager: Thread " << (tid) << ": " << msg;
		else
			smsg << "ThreadManager: " << msg;
		
		Logger::Log(smsg.str());
	}
protected:
public:
	ThreadManager(const uint64_t NumberOfThreadsToCreate) : _tid(std::this_thread::get_id())
	{
		_NumberOfThreads = createThreads(NumberOfThreadsToCreate);
	}

	~ThreadManager()
	{
#ifdef _DEBUG
		Log("Terminating Pool");
#endif
		{
			std::unique_lock<std::mutex> lock(_TaskDequeMutex); //Make sure no other thread of the pool is running
			_stopped = true;
		}
		_TaskCondVar.notify_all();

		for (std::thread &Thread : _Threads)
		{	
			if (Thread.joinable())
				Thread.join();
		}
#ifdef _DEBUG
		Log("Threads joined");
#endif
	};

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

	uint64_t getNumberOfWorkingThreads() const BASIC_NOEXCEPT { return _WorkingThreads.load(); };
};

#endif //_THREADMANAGER_H_
