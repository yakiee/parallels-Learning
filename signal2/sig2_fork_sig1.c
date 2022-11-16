#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void sig_fun(int sig)
{
    exit(0);
}

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        signal(SIGALRM, sig_fun);
        alarm(3);
    }
    printf("Father porccess is waiting....\n");
    pause();
    printf("Father process is terminal....\n");
    exit(0);
}
