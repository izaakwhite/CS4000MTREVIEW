#include <iostream>
#include <omp.h>

void task(int id) {
    std::cout << "Thread " << id << " before barrier\n";
    
    // Synchronization barrier: All threads must reach this point before proceeding
    #pragma omp barrier

    std::cout << "Thread " << id << " after barrier\n";
}

int main() {
    const int num_threads = 3;

    #pragma omp parallel num_threads(num_threads)
    {
        int id = omp_get_thread_num() + 1;
        task(id);
    }

    return 0;
}
