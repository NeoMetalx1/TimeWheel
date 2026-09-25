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

    wheel.start();

    wheel.addTask(3, test1);
    wheel.addTask(12,deleteExpired);
    wheel.addTask(4, test2);
    wheel.addTask(3, test3);

}
