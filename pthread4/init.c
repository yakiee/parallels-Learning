#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

int main() {
    sem_open("/mutex", O_CREAT, 0666, 1);
    sem_open("/full", O_CREAT, 0666, 0);
    sem_open("/empty", O_CREAT, 0666, 5);
    return 0;
}