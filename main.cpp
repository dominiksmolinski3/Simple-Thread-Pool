#include "SimpleThreadPool.h"
#include <iostream>
#include <chrono>

int main() {
    SimpleThreadPool pool(std::thread::hardware_concurrency());

    auto task1 = pool.Post([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Task 1 done" << std::endl;
        return 1;
    });

    auto task2 = pool.Post([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Task 2 done" << std::endl;
        return 2;
    });

    auto task3 = pool.Post([]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Task 3 done" << std::endl;
        return 3;
    });

    std::cout << "Result of Task 1: " << task1.get() << std::endl;
    std::cout << "Result of Task 2: " << task2.get() << std::endl;
    std::cout << "Result of Task 3: " << task3.get() << std::endl;

    return 0;
}
