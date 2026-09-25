#include "timewheel.h"

bool Task::isAvailable() const {
    return rotations == 0;
}
                                          //temporary
TimeWheel::TimeWheel(uint32_t wheel_size) : _executor(4), _wheelSize(wheel_size), _currentCell(0), wheel(wheel_size) {}

TimeWheel::~TimeWheel() {
    if (_worker.joinable() && _running) {
        stop();
    }
}

void TimeWheel::tick() {
    std::lock_guard<std::mutex> lock(_mutex);

    _currentCell = (_currentCell + 1) % _wheelSize;

    auto& cell = wheel[_currentCell];

    for (auto taskIt = cell.begin(); taskIt != cell.end();) {
        Task& task = *taskIt; // just for better readability

        if (!task.isAvailable()) {
            --task.rotations;
            ++taskIt;
        } else {
            _executor.putTask(std::move(task.function));
            taskIt = cell.erase(taskIt);
        }
    }
}

void TimeWheel::start() {
    _running = true;

    _worker = std::thread([this] {
        while(_running) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // temporary
            tick();
        }
    });
}

void TimeWheel::stop() {
    if (!_running)
        return;
    
    if (_running && _worker.joinable()) {
        _worker.join();
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

void TimeWheel::addTask(uint32_t delay, const fn& function) {
    std::lock_guard<std::mutex> lock(_mutex);

    Task newTask;

    newTask.rotations = calcRotations(delay);
    newTask.function = std::move(function);
    uint32_t targetCell = (_currentCell + delay) % _wheelSize;
    
    wheel[targetCell].push_back(std::move(newTask));
    std::cout << "[DEBUG] (addTask) | put task into cell: " << targetCell << '\n';
}
