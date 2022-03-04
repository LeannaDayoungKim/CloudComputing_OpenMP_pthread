//1515009 Dayoung Kim hw2 pthread code
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
double rod[402];
pthread_mutex_t lock[3];
int i, j;
void *Hello(void* rank);

int main(int argc, char* argv[]) {
	long thread;
	pthread_t* thread_handles;
	int i;
	rod[0] = 1000;   // ∂ﬂ∞≈øÓ ∫Œ∫–¿« ø¬µµ 
	for (i = 0; i < thread_count - 1; i++) {
		pthread_mutex_init(&lock[i], NULL);
	}//π¬≈ÿΩ∫ lock √ ±‚»≠

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count* sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Hello, (void*)thread);

	
	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	pthread_barrier_destroy(lock);
	free(thread_handles);

	printf("Result\n");
	for (i = 0; i < 402; i++)
		printf("rod[%d] = %lf\n", i, rod[i]);

	return 0;
}
void *Hello(void* rank) { 
	int i, j;
	long myrank = (long)rank;
	int first = 100 * myrank;
	int last = 100 * (myrank + 1) - 1;
	for (i = 0; i < 10000; i++) {   // 10000π¯ ∞ËªÍ   
		if (myrank != 0) {
			pthread_mutex_lock(&lock[myrank - 1]);
			rod[first] =
				(rod[first - 1] + rod[first + 1]) / 2;
			pthread_mutex_unlock(&lock[myrank - 1]);
		}//lock
		for (j = first+1; j < last; j++) {    // rod ¿« ∞¢ ¿ßƒ° ∞ËªÍ   
			rod[j] = (rod[j - 1] + rod[j] + rod[j + 1]) / 3.0;
		}
		if (myrank != 3) {
			pthread_mutex_lock(&lock[myrank]);
			rod[last] =
				(rod[last - 1] + rod[last + 1]) / 2;
			pthread_mutex_unlock(&lock[myrank]);
		}


	}
	return NULL;
}
