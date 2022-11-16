#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fun(int sig) {
    printf("signal: %d\n", sig);
    signal(SIGINT, SIG_DFL);    //ignore | default
}

int main() {
    int i = 1;
    signal(SIGINT, fun);
    while (1) {
        printf("%dHello world.\n", i++);
        sleep(2);
    }
    return 0;
}
