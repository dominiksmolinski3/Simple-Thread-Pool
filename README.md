# Simple C++ Thread Pool

This repository contains a straightforward implementation of a thread pool in C++. This thread pool is designed to help manage a group of worker threads that execute tasks asynchronously. It is lightweight, easy to use, and ideal for parallelizing workloads in your C++ applications.

## Features

- **Lightweight Design**: The code is simple and easy to understand, making it a good starting point for learning about thread pools.
- **Task Posting with Return Values**: Allows tasks to return values using `std::future`.
- **Thread Safety**: The thread pool handles task synchronization using mutexes and condition variables.
- **Automatic Cleanup**: The pool handles graceful shutdown and thread joining.

## Requirements

- C++11 or higher (for threading support, lambda functions, and modern C++ features).

## Getting Started

### Clone the Repository:

```bash
git clone https://github.com/dominiksmolinski3/simple-thread-pool.git
cd simple-thread-pool
