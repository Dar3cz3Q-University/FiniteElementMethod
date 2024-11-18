#include "pch.h"
#include "ThreadPool.h"

ThreadPool* ThreadPool::m_Instance = nullptr;

ThreadPool::ThreadPool() {}

ThreadPool::~ThreadPool()
{
    LOG_TRACE("Stopping additional threads");

    Stop();

    if (!m_Instance)
        delete m_Instance;
}

ThreadPool* ThreadPool::GetInstance()
{
    if (!m_Instance)
        m_Instance = new ThreadPool();

    return m_Instance;
}

void ThreadPool::Start(uint32_t numberOfThreads)
{
    LOG_TRACE("Initializing thread pool");
    for (uint32_t i = 0; i < numberOfThreads; i++)
    {
        m_Threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        LOG_TRACE("Thread {} started", thread_id_to_string(m_Threads.at(i).get_id()));
    }
}

void ThreadPool::QueueJob(const std::function<void()>& job)
{
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future();

    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_Jobs.push([promise, job]()
            {
                job();
                promise->set_value();
            });
    }
    m_MutexCondition.notify_one();
    m_Futures.push_back(std::make_shared<std::future<void>>(std::move(future)));
}

void ThreadPool::WaitAllJobs()
{
    for (auto& future : m_Futures)
    {
        future->wait();
    }
    m_Futures.clear();
}

bool ThreadPool::IsBusy()
{
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        poolbusy = !m_Jobs.empty();
    }
    return poolbusy;
}

void ThreadPool::Stop()
{
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_ShouldTerminate = true;
    }
    m_MutexCondition.notify_all();
    for (std::thread& active_thread : m_Threads)
    {
        active_thread.join();
    }
    m_Threads.clear();
}

void ThreadPool::ThreadLoop()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_MutexCondition.wait(lock, [this]
                {
                    return !m_Jobs.empty() || m_ShouldTerminate;
                });
            if (m_ShouldTerminate && m_Jobs.empty())
            {
                return;
            }
            job = m_Jobs.front();
            m_Jobs.pop();
        }
        job();
    }
}
