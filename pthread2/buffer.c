#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t full, empty, mutex;
int buffer[5];

struct tType
{
    int tid;
    char type;
};

void *fun(void *param)
{
    struct tType *receive = (struct tType *)param;
    
    if (receive->type == 'p')
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        for (int i = 0; i < receive->tid; i++)
        {
            sleep(rand() % 5);
            buffer[i] = rand();
            printf("%d\n", buffer[i]);
        }
        sem_post(&full);
        sem_post(&mutex);
    }

    if (receive->type == 'c')
    {
        sem_wait(&full);
        sem_wait(&mutex);
        for (int j = 0; j < receive->tid; j++)
        {
            sleep(rand() % 5);
            printf("read: %d\n", buffer[j]);
            buffer[j] = -1;
        }
        sem_post(&empty);
        sem_post(&mutex);
    }
}

void main(int argc, char **argv)
{
    pthread_t *tid_p, *tid_c;
    int sleepTime = atoi(argv[1]), producer = atoi(argv[2]), consumer = atoi(argv[3]);
    tid_p = malloc(sizeof(pthread_t) * producer);
    tid_c = malloc(sizeof(pthread_t) * consumer);
    struct tType tProducer[producer];
    struct tType tConsumer[consumer];
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    sem_init(&mutex, 0, 1);
    //生产者线程
    for (long i = 0; i < producer; i++)
    {
        tProducer[i].tid = i;
        tProducer[i].type = 'p';
        pthread_create(&tid_p[i], 0, fun, &tProducer[i]);
    }
    //消费者线程
    for (long i = producer; i < consumer + producer; i++)
    {
        tConsumer[i - producer].tid = i;
        tConsumer[i - producer].type = 'c';
        pthread_create(&tid_c[i - producer], 0, fun, &tConsumer[i]);
    }
    sleep(sleepTime);

    //生产者线程
    for (long i = 0; i < producer; i++)
    {
        pthread_join(tid_p[i], 0);
    }
    //消费者线程
    for (long i = producer; i < consumer + producer; i++)
    {
        pthread_join(tid_c[i - producer], 0);
    }
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);
}