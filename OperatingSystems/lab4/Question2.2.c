#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t lock1, lock2, lock3;

void * thrd1(void *arg)
{
	sem_wait(&lock1);
	printf("lock 1: on\n");
	sleep(2);
	sem_wait(&lock2);
	printf("lock 2 : on\n");
	sleep(2);
	sem_post(&lock2);
	printf("lock 2 : off\n");
	sem_post(&lock1);
	printf("lock 1 : off\n");
}

void * thrd2(void *arg)
{
	sem_wait(&lock2);
	printf("lock 2 : on\n");
	sleep(2);
	sem_wait(&lock3);
	printf("lock 3 : on\n");
	sleep(2);
	sem_post(&lock3);
	printf("lock 3 : off\n");
	sem_post(&lock2);
	printf("lock 2 : off\n");
}

void * thrd3(void *arg)
{
	sem_wait(&lock3);
	printf("lock 3 : on\n");
	sleep(2);
	sem_wait(&lock1);
	printf("lock 1 : on\n");
	sleep(2);
	sem_post(&lock1);
	printf("lock 1 : off\n");
	sem_post(&lock3);
	printf("lock 3 : off\n");
}

int main(int argc, char **argv)
{
	sem_init(&lock1,0,1);
	sem_init(&lock2,0,1);
	sem_init(&lock3,0,1);

	pthread_t tr1, tr2, tr3;

    pthread_create(&tr1, NULL, thrd1, NULL);
    pthread_create(&tr2, NULL, thrd2, NULL);
    pthread_create(&tr3, NULL, thrd3, NULL);

	pthread_join(tr1,NULL);
	pthread_join(tr2,NULL);
	pthread_join(tr3,NULL);

	sem_destroy(&lock1);
	sem_destroy(&lock2);
	sem_destroy(&lock3);
}