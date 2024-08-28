#include "SimpleThreadPool.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <sstream>

std::mutex output_mutex; // Mutex to synchronize console output

std::string thread_id_to_string(std::thread::id id) {
    std::ostringstream ss;
    ss << id;
    return ss.str();
}

void log(const std::string& message) {
    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << message << std::endl;
}

int main() {
    SimpleThreadPool pool(std::thread::hardware_concurrency());

    auto task1 = pool.Post([]() {
        log("Task 1 started on thread " + thread_id_to_string(std::this_thread::get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(6));
        log("Task 1 done on thread " + thread_id_to_string(std::this_thread::get_id()));
        return 1;
    });

    auto task2 = pool.Post([]() {
        log("Task 2 started on thread " + thread_id_to_string(std::this_thread::get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(4));
        log("Task 2 done on thread " + thread_id_to_string(std::this_thread::get_id()));
        return 2;
    });

    auto task3 = pool.Post([]() {
        log("Task 3 started on thread " + thread_id_to_string(std::this_thread::get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(2));
        log("Task 3 done on thread " + thread_id_to_string(std::this_thread::get_id()));
        return 3;
    });

    log("Result of Task 1: " + std::to_string(task1.get()));

    log("Result of Task 2: " + std::to_string(task2.get()));

    log("Result of Task 3: " + std::to_string(task3.get()));

    return 0;
}
