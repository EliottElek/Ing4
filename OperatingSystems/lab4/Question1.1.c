#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

#define KEY 1234
#define PERMS 0660

int main(int argc, char **argv)
{
	int id;
    int i;
	id = shmget(KEY,sizeof(int),IPC_CREAT | PERMS);

	i = (int) shmat(id,NULL,0);
	i = 65;

	if(fork()==0)
	{
		sleep(2);
		i--;
		printf("-: %d\n",i);
	}
	else
	{
		sleep(2);
		i++;
		printf("+: %d\n",i);
		sleep(2);
		printf("=: %d\n",i);
	}


	
	return 0;
}