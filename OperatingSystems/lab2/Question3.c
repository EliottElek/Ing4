#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
//define the shared memory keys
#define KEY 4567
#define KEY2 4568

//define the key for permission access
#define PERMS 0660
int main(int argc, char **argv)
{
    //declaration of our variables
    int *tab;
    int *tabBooleans;
    int id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
    int flag = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
    system("ipcs -m");
    //Here, we attach the previously created memory to the pointer ptr.
    //-id is the id of the previously created space
    //-NULL indicates that the systems can any free adress to attach to
    tab = (int *)shmat(id, NULL, 0);
    tabBooleans = (int *)shmat(flag, NULL, 0);

    //we assign the values of each variable of the tab.
    for (int k = 0; k < 6; k++)
    {
        tab[k] = k + 3; //assing random values
    }
    //that gives us :
    //tab[0] = 3 = a
    //tab[1] = 4 = b
    //tab[2] = 5 = c
    //tab[3] = 6 = d
    //tab[4] = 7 = e
    //tab[5] = 8 = f
    //initializing of our boolean tab :
    tabBooleans[0] = 0;
    tabBooleans[1] = 0;
    if (fork() == 0)
    {
        if (fork() == 0)
        {
            //third part of the calculating
            printf("e = %d, f = %d\n", tab[4], tab[5]);
            // e = e + f
            tab[4] = tab[4] - tab[5];
            printf("e + f = %d\n", tab[4]);
            tabBooleans[0] = 1;
        }
        else
        {
            //second part of the calculating
            printf("c = %d, d = %d\n", tab[2], tab[3]);
            // c = c - d
            tab[2] = tab[2] - tab[3];
            printf("c - d = %d\n", tab[2]);
            while (tabBooleans[0] == 0)
            {
            }
            //fourth part of the calculating
            tab[0] = tab[0] * tab[2];
            printf("(a + b)(c - d) = %d\n", tab[0]);
            wait(NULL);
            tabBooleans[1] = 1;
        }
    }
    else
    {
        //first part of the calculating
        printf("a = %d, b = %d\n", tab[0], tab[1]);
        // a = a + b
        tab[0] = tab[0] + tab[1];
        printf("a + b = %d\n", tab[0]);
        while (tabBooleans[1] == 0)
        {
        } //last part of the calculating
        tab[0] = tab[0] + tab[4];
        printf("(a + b) * (c - d) + (e + f) = %d", tab[0]);
    }
}
