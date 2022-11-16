#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int main() {
    int i = 1;
    while (1) {
        printf("%dHello world.\n", i++);
        sleep(1);
    }
    return 0;
}