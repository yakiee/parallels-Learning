#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem0, sem1;

void *fun(void *param)
{
    long num = (long)param;

    for (int i = 0; i < 10; i++)
    {
        if (num == 0)
            sem_wait(&sem0);
        else
            sem_wait(&sem1);
        printf("pthread %ld: %d\n", num, i);
        // sleep(1);
        if (num == 0)
            sem_post(&sem1);
        else
            sem_post(&sem0);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t tid0, tid1;
    long num0 = 0, num1 = 1;
    sem_init(&sem0, 0, 1);
    sem_init(&sem1, 0, 0);
    pthread_create(&tid0, 0, fun, (void *)num0);
    pthread_create(&tid1, 0, fun, (void *)num1);
    pthread_join(tid0, 0);
    pthread_join(tid1, 0);
    sem_destroy(&sem0);
    sem_destroy(&sem1);
    return 0;
}
