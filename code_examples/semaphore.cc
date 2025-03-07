#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

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

Semaphore sem(4);  // Allows up to 4 threads at a time
std::mutex log_mtx; // To prevent mixed output

void log(const std::string& message, int id) {
    std::lock_guard<std::mutex> guard(log_mtx);
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cout << "[" << ms << " ms] Thread " << id << ": " << message << std::endl;
}

void task(int id) {
    log("Waiting for semaphore...", id);
    sem.wait();

    log("Entered critical section", id);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    log("Leaving critical section", id);
    sem.signal();
}

int main() {
    const int num_threads = 16;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(task, i + 1);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
