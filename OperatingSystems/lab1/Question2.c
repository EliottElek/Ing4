#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

// https://stackoverflow.com/questions/46368813/fork-returns-0-but-the-child-process-getpid-0-why

int main(int argc, char *argv[])
{

    printf("I am: %d\n", (int)getpid());
    printf("Parent is: %d\n", (int)getppid());


    pid_t pid = fork();

    printf("fork returned: %d\n", (int)pid);

    if (pid < 0)
    {
        perror("fork failed");  
    }

    if (pid==0)
    {
        printf("I am the child with pid %d\n", (int)getpid());
        sleep(5);
        printf("Child exiting...\n");
        exit(0);
    }

    printf("I am the parent with pid %d, waiting for the child\n", (int)getpid());
    wait(NULL);
    printf("Parent ending. \n");

    return 0;
}