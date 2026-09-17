#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <list>

using fn = std::function<void()>;

struct Task {
    uint32_t rotations;
    fn function;
    
    bool isAvailable() const;
};

class TimeWheel {
private:
    uint32_t _wheelSize = 0;
    uint32_t _currentCell = 0;

    std::vector<std::list<Task>> wheel;
    

    uint32_t calcRotations(uint32_t delay) const;
public:
    explicit TimeWheel(uint32_t wheel_size);

    void tick(); // temporary public for debugging

    uint32_t get_wheel_size() const;

    void addTask(const fn& function, uint32_t delay);
};
