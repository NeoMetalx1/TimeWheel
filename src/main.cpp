#include "timewheel.h"

void deleteExpired() {
    std::cout << "Deleted expired\n";
}

void test1() {
    std::cout << "Call test 1\n";
}

void test2() {
    std::cout << "Call test 2\n";
}

void test3() {
    std::cout << "Call test 3\n";
}

int main() {
    TimeWheel wheel(8);

    wheel.addTask(test1, 3);
    wheel.addTask(deleteExpired, 12);
    wheel.addTask(test2, 13);
    wheel.addTask(test3, 18);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        wheel.tick();
    }
}
