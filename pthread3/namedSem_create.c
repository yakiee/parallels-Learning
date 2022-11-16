#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

void main() {
    sem_open("/sem1", O_CREAT, 0666, 1);
    sem_open("/sem2", O_CREAT, 0666, 0);
}