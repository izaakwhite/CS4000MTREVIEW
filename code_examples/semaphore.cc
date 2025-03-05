#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    explicit Semaphore(int init_count) : count(init_count) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

Semaphore sem(2);  // Allows up to 2 threads at a time

void task(int id) {
    sem.wait();
    std::cout << "Thread " << id << " is inside the critical section\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is leaving the critical section\n";
    sem.signal();
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
