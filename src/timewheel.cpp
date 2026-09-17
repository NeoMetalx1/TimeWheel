#include "timewheel.h"

bool Task::isAvailable() const {
    return rotations == 0;
}

TimeWheel::TimeWheel(uint32_t wheel_size) : _wheelSize(wheel_size), _currentCell(0), wheel(wheel_size) {}

void TimeWheel::tick() {
    _currentCell = (_currentCell + 1) % _wheelSize;

    auto& cell = wheel[_currentCell];

    for (auto taskIt = cell.begin(); taskIt != cell.end();) {
        Task& task = *taskIt; // just for better readability

        if (!task.isAvailable()) {
            --task.rotations;
            ++taskIt;
        } else {
            task.function();
            taskIt = cell.erase(taskIt);
        }
    }
}

uint32_t TimeWheel::calcRotations(uint32_t delay) const {
    uint32_t rotations = delay / _wheelSize;
    std::cout << "[DEBUG] (calcRotations) | return value: " << rotations << '\n';
    return rotations;
}

uint32_t TimeWheel::get_wheel_size() const {
    return _wheelSize;
}

void TimeWheel::addTask(const fn& function, uint32_t delay) {
    Task newTask;

    newTask.rotations = calcRotations(delay);
    newTask.function = std::move(function);
    uint32_t targetCell = (_currentCell + delay) % _wheelSize;
    
    wheel[targetCell].push_back(std::move(newTask));
    std::cout << "[DEBUG] (addTask) | put task into cell: " << targetCell << '\n';
}
