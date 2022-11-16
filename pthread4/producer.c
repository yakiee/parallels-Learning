#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

sem_t *empty, *full, *mutex;
int shm_fd;
int *ptr; 
int *ptr2;
int count = 0;

void *produce(void *param)
{
    long pNum = (long)param;
    int randomNum;
    if (count > 4 && count % 5 == 0)
    {
        sem_wait(full);
        ptr = ptr2;
        sem_post(empty);
    }
    else if (count > 5)
    {
        sem_wait(full);
        sem_post(empty);
    }
    sem_wait(empty);
    sem_wait(mutex);
    sleep(2);
    randomNum = rand() % 1000;
    // randomNum = 1;
    *ptr = randomNum;
    printf("count: %d\trandom: %d\n", count, randomNum);
    ptr++;
    count++;
    sem_post(mutex);
    sem_post(full);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t *tid;
    int tCount = atoi(argv[1]);
    int sleepTime = atoi(argv[2]);

    shm_fd = shm_open("buffer", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ptr2 = ptr;
    tid = malloc(sizeof(pthread_t) * tCount);

    full = sem_open("/full", 0);
    empty = sem_open("/empty", 5);
    mutex = sem_open("/mutex", 1);

    for (long i = 0; i < tCount; i++)
    {
        pthread_create(&tid[i], 0, produce, (void *)i);
        sleep(sleepTime);
    }

    for (int i = 0; i < tCount; i++)
    {
        pthread_join(tid[i], 0);
    }

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);
    return 0;
}