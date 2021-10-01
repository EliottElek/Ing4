#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
//define the shared memory key
#define KEY 4567
//define the key for permission access
#define PERMS 0660
int main(int argc, char **argv)
{
    //declaration of our variables
    int id;
    int i;
    int *ptr;
    //we display the segments of the shared memory
    system("ipcs -m");
    // the following function gets in parameters : 
    //  -the shared memory key
    //  -the size of int (size of allocated space in memory)
    //  -IPC_CREAT indicates that the function is in "create" mode
    // This function returns the id of the memory allocated.
    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
    // Here, we display the segment of the created shared memory :
    system("ipcs -m");
    //Here, we attach the previously created memory to the pointer ptr.
     //-id is the id of the previously created space
     //-NULL indicates that the systems can any free adress to attach to
     ptr = (int *)shmat(id, NULL, 0);
    //we assign the same value to both the pointer and i.
    *ptr = 54;
    i = 54;
    if (fork() == 0)
    {
        //creates a child process,
        //incrementes the value of both i and ptr
        //displays the values of i and ptr
        (*ptr)++;
        i++;
        printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
        exit(0);
    }
    else
    {
        //Parent process
        wait(NULL);
        //waits for the child process, displays values of i and ptr
        printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
        //finally, we use this function to remove allocated memory space.
        //it receives the id of the created space.
        shmctl(id, IPC_RMID, NULL);
    }
}