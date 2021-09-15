#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Current process's ID : %d\n", getpid());
    char* args[] = {"firefox", "NULL"};
    execvp(args[0], args);
    return 0;
}