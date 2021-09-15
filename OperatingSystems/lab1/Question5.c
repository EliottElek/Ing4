#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Current process's ID : %d\n", getpid());
    char* args[] = {"firefox", "NULL"};
     a = execvp("/usr/bin/firefox", parmList);
    fprintf(stdout, "execvp() returned %d\n", a);
    fprintf(stdout, "errno: %s (%d).\n", strerror(errno), errno);
    return 0;
}