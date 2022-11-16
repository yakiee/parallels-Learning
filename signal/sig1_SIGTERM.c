#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fun(int sig) {
    printf("signal: %d\n", sig);
    signal(SIGTERM, SIG_DFL);    //ignore | default
}

int main() {
    int i = 1;
    signal(SIGINT, fun);
    while (1) {
        printf("%dHello world.\n", i++);
        sleep(1);
    }
    return 0;
}