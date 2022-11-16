#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *fun(void *param)
{
    long num = (long)param;
    sleep(num);
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
    
    for (long i = 0; i < 3; i++)
    {
        sleepTime[i + 1] = sleepTime[i] + 2;
        pthread_create(&tid[i], 0, fun, (void *)sleepTime[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], 0);
    }

    return 0;
}