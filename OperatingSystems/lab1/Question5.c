#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Current process's ID : %d\n", getpid());
    char* args[] = {"firefox", NULL};
     int a = execvp("firefox", args);
    fprintf(stdout, "execvp() returned %d\n", a);
    return 0;
}