#include <stdio.h>
#include <unistd.h>

int main(){
    int i = 0;
    char* args[] = {"firefox", NULL};
    //Now we call a fork() function 
    if (fork()==0){
        execvp("firefox", args);
        i++;
        printf("Value of i : %d\n", i);
    }else {
        printf("Parent process's ID : %d\n", getpid());
    }
    return 0;
}