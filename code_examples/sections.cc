#include <stdio.h>
#include <omp.h> 

using namespace std;

int t1(int x) {
	printf("Task 1 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum += i;
    }
    return local_sum;
}
int t2(int x) {
	printf("Task 2 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum += i;
    }
    return local_sum;
}
int t3(int x) {
    printf("Task 3 is on thread %d \n", omp_get_thread_num());
    int local_sum = 0;
	for(int i = 0; i < x; i++){
        local_sum += i;
    }
    return local_sum;
}

int main()
{
    int t1_sum, t2_sum, t3_sum;
#pragma omp parallel sections
    {
#pragma omp section
        {
            t1_sum = t1(100000);
        }
#pragma omp section
        {
            t2_sum = t2(100000);
        }
#pragma omp section
        {
            t3_sum = t3(100000);
        }
    }
    int big_sum = t1_sum + t2_sum + t3_sum;
    printf("100000*3 = %d \n", big_sum);
    return 0;
}