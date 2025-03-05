#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void thread1() {
    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(m2);  // Waiting for m2
    std::cout << "Thread 1 acquired both locks\n";
}

void thread2() {
    std::lock_guard<std::mutex> lock2(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock1(m1);  // Waiting for m1 (Deadlock risk)
    std::cout << "Thread 2 acquired both locks\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
