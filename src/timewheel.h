#include "taskexecutor.h"

struct Task {
    uint32_t rotations;
    fn function;
    
    bool isAvailable() const;
};

class TimeWheel {
private:
    TaskExecutor _executor;

    uint32_t _wheelSize = 0;
    uint32_t _currentCell = 0;

    std::vector<std::list<Task>> wheel;

    uint32_t calcRotations(uint32_t delay) const;
    
    void tick();

    bool _running = false;

    std::thread _worker;
    std::mutex _mutex;
public:
    explicit TimeWheel(uint32_t wheel_size);
    ~TimeWheel();

    void start();
    void stop();

    uint32_t get_wheel_size() const;

    void addTask(uint32_t delay, const fn& function);
};
