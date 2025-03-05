#include <iostream>
#include <omp.h>

omp_lock_t lock1, lock2;

void task1() {
    omp_set_lock(&lock1);
    std::cout << "Task 1 acquired lock1\n";
    omp_set_lock(&lock2);  // Waiting for lock2
    std::cout << "Task 1 acquired lock2\n";

    omp_unset_lock(&lock2);
    omp_unset_lock(&lock1);
}

void task2() {
    omp_set_lock(&lock2);
    std::cout << "Task 2 acquired lock2\n";
    omp_set_lock(&lock1);  // Waiting for lock1 (Deadlock risk)
    std::cout << "Task 2 acquired lock1\n";

    omp_unset_lock(&lock1);
    omp_unset_lock(&lock2);
}

int main() {
    omp_lock_t lock1, lock2;
    omp_init_lock(&lock1);
    omp_init_lock(&lock2);

    #pragma omp parallel sections
    {
        #pragma omp section
        task1();

        #pragma omp section
        task2();
    }

    omp_destroy_lock(&lock1);
    omp_destroy_lock(&lock2);
    return 0;
}
