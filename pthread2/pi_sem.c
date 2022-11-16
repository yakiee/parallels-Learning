#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <semaphore.h>

struct pValue
{
	int tid;
	int tnum;
	int maxSum;
};

struct timeval start, end;
double sum = 0.0, pi = 0.0;
int flag[2] = {false}, turn;
sem_t sem;

void *fun(void *param)
{
	struct pValue *tn = (struct pValue *)param;
	double factor = 1.0;
	int tid = tn->tid;
	int tnum = tn->tnum;
	int max = tn->maxSum;
	double sumt = 0.0;
	int left = max / tnum * tid;
	int right = max / tnum * (tid + 1) - 1;

	for (int i = tid; i <= max; i++, i += tnum - 1)
	{
		if (i & 1)
			sumt += 0 - 1.0 / (2 * i + 1);
		else
			sumt += 1.0 / (2 * i + 1);
	}

	sem_wait(&sem);
	sum += sumt;
	sem_post(&sem);
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t *tid;
	int tnum = atoi(argv[1]);
	struct pValue pV[tnum];
	for (int i = 0; i < tnum; i++)
	{
		pV[i].tnum = atoi(argv[1]);
		pV[i].maxSum = atoi(argv[2]);
	}
	tid = malloc(pV[0].tnum * sizeof(pthread_t));

	sem_init(&sem, 0, 1);
	gettimeofday(&start, 0);
	for (long i = 0; i < pV[0].tnum; i++)
	{
		pV[i].tid = i;
		pthread_create(&tid[i], 0, fun, &pV[i]);
	}

	for (long i = 0; i < pV[0].tnum; i++)
	{
		pthread_join(tid[i], 0);
	}

	printf("pi: %f\n", sum * 4.0);

	gettimeofday(&end, 0);
	sem_destroy(&sem);
	printf("time: %d\n", end.tv_usec - start.tv_usec);
	return 0;
}
