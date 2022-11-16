#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

struct pValue
{
	int tid;
	int tnum;
	int maxSum;
};
struct spilt
{
	int left;
	int right;
};

struct timeval start, end;

void *fun(void *param)
{
	gettimeofday(&start, 0);
	struct pValue *tn = (struct pValue *)param;
	struct spilt spilt;
	spilt.left = (tn->maxSum / tn->tnum) * tn->tid + 1;
	spilt.right = (tn->maxSum / tn->tnum) * (tn->tid + 1);
	long sum = 0;
	for (int i = 1; i <= tn->maxSum; i++)
	{
		sum += i;
	}
	printf("tid: %d\nsum: %ld\n", tn->tid, sum);
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
	gettimeofday(&end, 0);

	printf("time: %d\n", end.tv_usec - start.tv_usec);
	return 0;
}
