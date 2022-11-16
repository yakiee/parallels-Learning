#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>

int main() {
    sem_t *sem1, *sem2;
    int shm_fd;
    void *ptr;
    shm_fd = shm_open("OS", O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    fprintf(ptr, "%s\n", "Hello");
    return 0;
}