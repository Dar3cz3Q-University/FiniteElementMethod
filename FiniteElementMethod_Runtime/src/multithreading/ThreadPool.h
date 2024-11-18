#pragma once

#include "StringUtils.h"

class ThreadPool
{
    // Singleton Pattern
private:
    ThreadPool();
    ~ThreadPool();

private:
    static ThreadPool* m_Instance;

public:
    ThreadPool(ThreadPool&) = delete;
    void operator=(const ThreadPool&) = delete;
    static ThreadPool* GetInstance();

    // Logic of the class
public:
	void Start(uint32_t numberOfThreads = std::thread::hardware_concurrency());
	void QueueJob(const std::function<void()>& job);
    void WaitAllJobs();

private:
    void ThreadLoop();
	void Stop();
	bool IsBusy();

    bool m_ShouldTerminate = false;
    std::mutex m_QueueMutex;
    std::condition_variable m_MutexCondition; 
    std::vector<std::thread> m_Threads;
    std::queue<std::function<void()>> m_Jobs;
    std::vector<std::shared_ptr<std::future<void>>> m_Futures;
};

