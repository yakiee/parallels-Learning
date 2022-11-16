#include <semaphore.h>

int main() {
    sem_unlink("/mutex");
    sem_unlink("/full");
    sem_unlink("/empty");
    return 0;
}