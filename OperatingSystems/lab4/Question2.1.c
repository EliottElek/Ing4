#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;
//creating i
int i;

void *thrd1(void *arg)
{
	i--;
	printf("decrement: %d\n", i);
	sem_post(&sem);
}

void *thrd2(void *arg)
{
	sem_wait(&sem);
	i++;
	printf("increment: %d\n", i);
}

int main()
{
	sem_init(&sem,0,0);
    //giving i a value of 65
	i=65;
	pthread_t tr1, tr2;
	pthread_create(&tr1, NULL, thrd1, NULL);
	pthread_create(&tr2, NULL, thrd2, NULL);
	pthread_join(tr1, NULL);
	pthread_join(tr2, NULL);

	printf("final: %d\n",a);
}
