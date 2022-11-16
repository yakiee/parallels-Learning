#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_fun(int sig) {
    printf("Pass 5s.\n");
}
int main() {
    alarm(5);
    signal(SIGALRM, sig_fun);
    pause();
}