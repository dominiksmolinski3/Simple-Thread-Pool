#include "SimpleThreadPool.h"
#include <iostream>
SimpleThreadPool::SimpleThreadPool(std::size_t threadCount)
    : m_threadCount(threadCount), stop(false) {
    for (size_t i = 0; i < m_threadCount; ++i) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mut);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }

    std::cout << "SimpleThreadPool initialized with " << m_threadCount << " threads." << std::endl;
}

SimpleThreadPool::~SimpleThreadPool() {
    Destroy();
}

void SimpleThreadPool::WorkOn() {
    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void SimpleThreadPool::Destroy() {
    {
        std::unique_lock<std::mutex> lock(mut);
        stop = true;
    }
    condition.notify_all();
    WorkOn();
}
