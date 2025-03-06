#include <stdio.h>
#include <omp.h> 

using namespace std;

void t1() {
	printf("Task 1 is on thread %d \n", omp_get_thread_num());
}
void t2() {
	printf("Task 2 is on thread %d \n", omp_get_thread_num());
}
void t3() {
	printf("Task 3 is on thread %d \n", omp_get_thread_num());
}

int main()
{
#pragma omp parallel sections 
{
#pragma omp section 
{
			t1();
		}
#pragma omp section 
{
			t2();
		}
#pragma omp section 
{
			t3();
		}
	}
	return 0;
}