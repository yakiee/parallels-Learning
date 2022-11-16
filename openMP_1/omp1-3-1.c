#include <stdio.h>
#include <omp.h>
#include <unistd.h>
void count() {
	#pragma omp critical
	for(int i = 1; i <= 10; i++) {
		sleep(1);
		printf("num: %d\n", i);
	}
}
int main() {
	#pragma omp parallel num_threads(3)
	count();
}
