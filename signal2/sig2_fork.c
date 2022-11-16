#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        sleep(2);
        printf("??\: %d\n", getppid());
        exit(0);
    }

    printf("??: %d\n", getppid());
    printf("Father porccess is waiting....\n");
    printf("???: %d\n", getppid());
    wait(NULL);
    printf("Father process is terminal....\n");
    exit(0);
}
