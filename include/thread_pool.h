#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

#include "thread_worker.h"

class ThreadPool
{
private:
    std::vector<std::thread> m_thread_list;
    std::queue<std::function<void()>> m_function_queue;
    std::mutex m_queue_mutex;

public:
    bool m_is_shut_down = false;
    std::mutex m_mutex;
    std::condition_variable m_condition_variable;

    ThreadPool(int n_theards);
    ~ThreadPool();

    std::function<void()> get_function();
    bool is_function_queue_empty();

    void execute_function(std::function<void()> request_handler);
    void shut_down();
};

#endif // THREAD_POOL_H
