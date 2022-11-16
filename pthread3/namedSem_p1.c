#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/shm.h>

int main() {
    sem_t *sem1, *sem2;
    sem_open("/sem1", 0);
    sem_open("/sem2", 0);

    for (int i = 0; i <= 10; i++) {
        sem_wait(sem1);
        printf("process1: %d\n", i);
        sleep(1);
        sem_post(sem2);
    }

    sem_close(sem1);
    sem_close(sem2);

    return 0;
}