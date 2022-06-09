#include <utility>
#include <iostream>

#include "../include/thread_pool.h"

ThreadPool::ThreadPool(int n_threads) : m_thread_list(n_threads)
{
    for (int i = 0; i < n_threads; i++)
    {
        m_thread_list[i] = std::thread(ThreadWorker(this));
    }
}

ThreadPool::~ThreadPool()
{
}

std::function<void()> ThreadPool::get_function()
{
    std::function<void()> func = nullptr;

    if (m_function_queue.empty() == false)
    {
        std::unique_lock lock(m_queue_mutex);
        func = m_function_queue.front();
        m_function_queue.pop();
    }

    return func;
}

bool ThreadPool::is_function_queue_empty()
{
    return m_function_queue.empty();
}

void ThreadPool::execute_function(std::function<void()> request_handler)
{
    std::unique_lock lock(m_queue_mutex);
    m_function_queue.push(request_handler);
    lock.unlock();
    m_condition_variable.notify_one();
}

void ThreadPool::shut_down()
{
    std::unique_lock lock(m_mutex);
    m_is_shut_down = true;
    lock.unlock();
    m_condition_variable.notify_all();


    std::cout << "Queue's size = " << m_function_queue.size() << std::endl;

    for (int i = 0; i < m_thread_list.size(); i++)
    {
        std::thread& thread = m_thread_list[i];
        if (thread.joinable())
        {
            thread.join();
            std::cout << "joined, i = " << i + 1 << std::endl;
        }
    }
}

