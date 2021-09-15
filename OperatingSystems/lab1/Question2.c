#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

int main(int argc, char *argv[])
{
   if (fork() == 0){
       printf("I'm the child process ! \n");
   }else {
       printf("I'm the parent process ! \n");
   }
   printf("My ID : %d\n", getpid());
   printf("My parent ID : %d\n", getppid()); 
   return 0; 
}