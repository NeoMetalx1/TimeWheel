#include "taskexecutor.h"

TaskExecutor::TaskExecutor(size_t threadCount) {
    _running = true;
    for(size_t i = 0; i < threadCount; i++) {
        _threads.emplace_back([this] { loop(); });
    }
}

TaskExecutor::~TaskExecutor() {
    _running = false;
    _cv.notify_all();
    for (auto& thread : _threads) {
        if (thread.joinable())
            thread.join(); 
    }
}

void TaskExecutor::loop() {
    while (_running) {
        std::unique_lock lock(_mutex);

        _cv.wait(lock, [this] {
            return !_taskQueue.empty() || !_running;
        });

        if (!_running && _taskQueue.empty())
            return;

        auto task = std::move(_taskQueue.front());
        _taskQueue.pop();

        lock.unlock();

        task();
    }
}

void TaskExecutor::putTask(const fn& task) {
    {
        std::lock_guard lock(_mutex);
        _taskQueue.push(std::move(task));
    }
    _cv.notify_one();
}