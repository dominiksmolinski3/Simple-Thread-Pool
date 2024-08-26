#ifndef SIMPLE_THREAD_POOL_H
#define SIMPLE_THREAD_POOL_H

#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>

class SimpleThreadPool {
public:
    explicit SimpleThreadPool(std::size_t threadCount);
    ~SimpleThreadPool();

    SimpleThreadPool(const SimpleThreadPool&) = delete;
    SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;

    template<typename Fnc_T>
    auto Post(Fnc_T task) -> std::future<decltype(task())>;

    void WorkOn();
    void Destroy();

private:
    size_t m_threadCount;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    std::condition_variable condition;
    std::mutex mut;
    bool stop;
};

template<typename Fnc_T>
auto SimpleThreadPool::Post(Fnc_T task) -> std::future<decltype(task())> {
    using return_type = decltype(task());
    auto packaged_task = std::make_shared<std::packaged_task<return_type()>>(task);
    std::future<return_type> result = packaged_task->get_future();

    {
        std::unique_lock<std::mutex> lock(mut);
        if (stop) {
            throw std::runtime_error("Thread pool has been stopped, cannot post new tasks.");
        }
        tasks.emplace([packaged_task]() { (*packaged_task)(); });
    }

    condition.notify_one();
    return result;
}

#endif // SIMPLE_THREAD_POOL_H
