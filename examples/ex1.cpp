#include <iostream>
#include "synchronized/synchronized.hpp"
#include <thread>
#include <ctime>
#include <chrono>

int i = 1;

void f() {
    std::chrono::seconds t(2);
    std::cout << "a" << std::endl;
    synchronized(&i) {
        std::cout << "b" << std::endl;
        std::this_thread::sleep_for(t);
        std::cout << "c" << std::endl;
    }
    std::cout << "d" << std::endl;
}

int main() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::cout << ctime(&time) << std::endl;
    
    std::thread t1(f);
    std::thread t2(f);

    t1.join();
    t2.join();

    auto then = std::chrono::system_clock::now();
    time = std::chrono::system_clock::to_time_t(then);
    std::cout << ctime(&time) << std::endl;

    return 0;
}
