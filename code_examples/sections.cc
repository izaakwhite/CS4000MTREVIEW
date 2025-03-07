#include <stdio.h>
#include <omp.h> 

using namespace std;

int t1(int x) {
	printf("Task 1 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum += i;
    }
    printf("Task 1 local sum: %d \n", local_sum);
    return local_sum;
}
int t2(int x) {
	printf("Task 2 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum += i * i;
    }
    printf("Task 2 local sum: %d \n", local_sum);
    return local_sum;
}
int t3(int x) {
    printf("Task 3 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum -= i;
    }
    printf("Task 3 local sum: %d \n", local_sum);
    return local_sum;
}

int main()
{
    int t1_sum, t2_sum, t3_sum;
#pragma omp parallel sections
    {
#pragma omp section
        {
            t1_sum = t1(100000000);
        }
#pragma omp section
        {
            t2_sum = t2(400000);
        }
#pragma omp section
        {
            t3_sum = t3(900000);
        }
    }
    int big_sum = t1_sum + t2_sum + t3_sum;
    printf("big_sum = %d \n", big_sum);
    return 0;
}