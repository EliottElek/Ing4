#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Current process's ID : %d\n", getpid());
    char* args[] = {"firefox", "NULL"};
    execvp("firefox", args);
    sleep(3);
    return 0;
}