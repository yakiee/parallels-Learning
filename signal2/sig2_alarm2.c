#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int t;
void sig_fun(int sig) {
    printf("Pass %ds.\n", t);
}
int main(int argc, char* argv[]) {
    t = atoi(argv[1]);
    alarm(t);
    signal(SIGALRM, sig_fun);

    pause();
}