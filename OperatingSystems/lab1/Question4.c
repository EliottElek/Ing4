#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

int main(int argc, char *argv[])
{
 if (fork() == 0) {
       printf("I'm a child (Generation 1) ! \n");
  if (fork() == 0) {
       printf("I'm a child (Generation 2) ! \n");
  }
 } else {
       printf("I'm a parent (Generation 1) ! \n");
 if (fork() == 0) {
       printf("I'm a child (Generation 1) ! \n");
 }
 }
 sleep(3);
  return 0; 
}