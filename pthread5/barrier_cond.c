#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int counter;
int thread_count;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

void *fun(void *param)
{
    long num = (long)param;
    thread_count = num;
    sleep(num);

    pthread_mutex_lock(&mutex);
    counter++;
    if (counter == thread_count) {
        counter = 0;
        pthread_cond_broadcast(&cond_var);
    } else {
        while(pthread_cond_wait(&cond_var, &mutex) != 0);
    }
    pthread_mutex_unlock(&mutex);

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
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond_var, 0);

    for (long i = 0; i < 3; i++)
    {
        sleepTime[i + 1] = sleepTime[i] + 2;
        pthread_create(&tid[i], 0, fun, (void *)sleepTime[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], 0);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
    return 0;
}