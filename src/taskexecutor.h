#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <chrono>
#include <functional>
#include <list>
#include <condition_variable>

using fn = std::function<void()>;

class TaskExecutor {
private:
    std::vector<std::thread> _threads;
    std::queue<fn> _taskQueue;

    std::mutex _mutex;
    std::condition_variable _cv;
    std::atomic<bool> _running{false};
    
    void loop();
public:
    TaskExecutor(size_t threadCount);
    ~TaskExecutor();

    void putTask(const fn& task);
};