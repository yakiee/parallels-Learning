#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter;
int thread_count;
sem_t count_sem;    // 1
sem_t barrier_sem;  // 0

void *fun(void *param)
{
    long num = (long)param;
    thread_count = num;
    sleep(num);

    sem_wait(&count_sem);
    if (counter == thread_count - 1) {
        counter = 0;
        sem_post(&count_sem);
        for (int j = 0; j < thread_count - 1; j++) {
            sem_post(&barrier_sem);
        }
    } else {
        counter++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
    printf("tid%ld: exit.\n", num / 2);
    pthread_exit(0);
}

int main()
{
    pthread_t *tid;
    long *sleepTime;
    tid = malloc(sizeof(pthread_t) * 3);
    sleepTime = malloc(sizeof(long) * 4);
    sleepTime[0] = 2;

    sem_init(&count_sem, 0, 1);
    sem_init(&barrier_sem, 0, 0);

    for (long i = 0; i < 3; i++)
    {
        sleepTime[i + 1] = sleepTime[i] + 2;
        pthread_create(&tid[i], 0, fun, (void *)sleepTime[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], 0);
    }

    sem_destroy(&count_sem);
    sem_destroy(&barrier_sem);
    return 0;
}