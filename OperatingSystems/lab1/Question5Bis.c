#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(){
    printf("\nThis is the ID : %d\n",getpid());
    char cmd[30];
    strcpy(cmd,"Firefox");
    execl("/bin/sh","sh","-c",cmd, (char) NULL);
    return 0;
}