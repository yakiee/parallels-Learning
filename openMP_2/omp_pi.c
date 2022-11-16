#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

double sum = 0.0;

void calculate(int max) {
	double sumt = 0.0;
	int tid = omp_get_thread_num();
	int a_num = omp_get_num_threads();

	#pragma omp critical	
	for(int i = tid; i <= max; i++, i += a_num - 1) {
		if (i & 1)
			sumt += 0 - 1.0 / (2 * i + 1);
		else
			sumt += 1.0 / (2 * i + 1);		
	}

	sum += sumt;

	// #pragma omp critical	
	// for(int i = 0; i <= max; i++) {
	//	printf("judge %d\n", i % a_num);
	//	if (tid == i % a_num) {
	//		sum += i;
	//		printf("i %d\n", i);
	//	}
	//}
	printf("thread %d\n", tid);
}

int main(int argc, char* argv[]) {
	int tnum = atoi(argv[1]);
	int max = atoi(argv[2]);
	#pragma omp parallel num_threads(tnum)
	calculate(max);
	printf("pi: %f\n", sum);
	return 0;
}
