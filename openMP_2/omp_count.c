#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int sum = 0;
void count(int max) {
	
int main(int argc, char* argv[]) {
	int tnum = atoi(argv[1]);
	int max = atoi(argv[2]);
	#pragma omp parallel num_threads(tnum)
	count(max);
int tid, all_tid;
	tid = omp_get_thread_num();
	all_tid = omp_get_num_threads();
	// #pragma omp critical
	for (int i = 0; i <= max; i++) {
		sleep(1);
		if (tid== i % all_tid + 1) {
			sum += i;
			printf("tid %d i %d\n", tid, i);
		}	
	}
	
	printf("thread%d\tsum: %d\n", tid, sum);
}
}
