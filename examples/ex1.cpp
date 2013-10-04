#include <iostream>
#include "synchronized/synchronized.hpp"
#include <thread>
#include <ctime>
#include <chrono>

int i = 1;

void f(int thread_no) {
    std::chrono::seconds t(2);
    std::cout << "thread " << thread_no << "before synchronized" << std::endl;
    synchronized (&i) {
        std::cout << "thread " << thread_no << " before sleep" << std::endl;
        std::this_thread::sleep_for(t);
        std::cout << "thread " << thread_no << " after sleep" << std::endl;
    }
    std::cout << "thread " << thread_no << " after synchronized" << std::endl;
}

int main() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::cout << "current time: " << ctime(&time);
    
    std::thread t1(f, 1);
    std::thread t2(f, 2);

    t1.join();
    t2.join();

    auto then = std::chrono::system_clock::now();
    time = std::chrono::system_clock::to_time_t(then);
    std::cout << "current time: " << ctime(&time);

    return 0;
}
