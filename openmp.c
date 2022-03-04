//1515009 Dayoung Kim hw2 openmp code
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
double rod[402];
omp_lock_t lock;//for lock for critical section
void Hello(void);
int main(int argc, char* argv[]) {
	rod[0] = 1000;
	int thread_count = strtol(argv[1], NULL, 10);
	int i;
#pragma omp parallel num_threads(thread_count)
	Hello();
	printf("Result\n");
	for (i = 0; i < 402; i++)
		printf("rod[%d] = %lf\n", i, rod[i]);
	return 0;
}
void Hello(void) {
	int myrank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	int i, j;
	int first = 100 * myrank;
	int last = 100 * (myrank + 1) - 1;
	for (i = 0; i < 10000; i++) {   // 10000π¯ ∞ËªÍ
		omp_set_lock(&lock);//lock
		rod[first] = (rod[first - 1] + rod[first] + rod[first + 1]) / 3.0;
		rod[0] = 1000;//Ω√¿€ ∞™ ∞Ì¡§
		omp_unset_lock(&lock);
		for (j = first + 1; j < last; j++) {    // rod ¿« ∞¢ ¿ßƒ° ∞ËªÍ   
			rod[j] = (rod[j - 1] + rod[j] + rod[j + 1]) / 3.0;
		}
		omp_set_lock(&lock);//lock
		rod[last] = (rod[last - 1] + rod[last] + rod[last + 1]) / 3.0;
		rod[401] = 0;//∏∂¡ˆ∏∑ ∞™ ∞Ì¡§
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
}
