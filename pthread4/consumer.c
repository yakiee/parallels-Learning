#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <pthread.h>

int shm_fd;
int *ptr;
int *ptr2;
int count = 0;
sem_t *empty, *full, *mutex;

void *consume(void *param)
{
    long cNum = (long)param;

    if (count > 4 && count % 5 == 0)
    {
        sem_wait(empty);
        ptr = ptr2;
        sem_post(full);
    }
    else if (count > 5)
    {
        sem_wait(empty);
        sem_post(full);
    }

    sem_wait(full);
    sem_wait(mutex);
    sleep(2);
    if (ptr == NULL)
    {
        printf("Consumer %ld: ptr is NULL\n", cNum);
    }
    else
    {
        printf("Consumer %ld: %d\n", cNum, *ptr);
        *ptr = -1;
        ptr++;
        count++;
    }
    sem_post(mutex);
    sem_post(empty);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t *tid;
    int tCount = atoi(argv[1]);
    int sleepTime = atoi(argv[2]);

    shm_fd = shm_open("buffer", O_RDONLY | O_RDWR, 0666);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ptr2 = ptr;
    tid = malloc(sizeof(pthread_t) * tCount);

    full = sem_open("/full", 5);
    empty = sem_open("/empty", 0);
    mutex = sem_open("/mutex", 1);

    for (long i = 0; i < tCount; i++)
    {
        pthread_create(&tid[i], 0, consume, (void *)i);
        sleep(sleepTime);
    }

    for (int i = 0; i < tCount; i++)
    {
        pthread_join(tid[i], 0);
    }

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    shm_unlink("buffer");
    return 0;
}