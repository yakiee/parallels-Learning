#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* fun (void* param) {
    long num = (long)param;

    for (int i = 0; i < 10; i++) {
        printf("pthread %ld: %d\n", num, i);
        sleep(1);
    }

    pthread_exit(0);
}

int main() {
    pthread_t tid0, tid1;
    long num0 = 0, num1 = 1;
    
    pthread_create(&tid0, 0, fun, (void*)num0);
    pthread_create(&tid1, 0, fun, (void*)num1);
    pthread_join(tid0, 0);
    pthread_join(tid1, 0);

    return 0;
}
