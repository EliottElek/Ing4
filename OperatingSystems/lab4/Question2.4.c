#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


int tab[3];
sem_t lock1, lock2, muti;
int a = 1;
int b = 2;
int c = 3;
int d = 2;
int e = 3;
int f = 2;
int i =-1;


void *thrd1(void *arg)
{
	sem_wait(&muti);
	i++;
	tab[i]=a+b;
	printf("result : %d, i: %d\n",tab[i],i);
	sem_post(&muti);
	if(i==1)
	{
		sem_post(&lock1);
		printf("1st lock : free\n");
	}
	else if(i==2)
	{
		sem_post(&lock2);
		printf("2nd lock : free\n");
	}
}

void *thrd2(void *arg)
{
	sem_wait(&muti);
	i++;
	tab[i]=c-d;
	printf("result : %d, i: %d\n",tab[i],i);
	if(i==1)
	{
		sem_post(&lock1);
		printf("1st lock : free\n");
	}
	else if(i==2)
	{
		sem_post(&lock2);
		printf("2nd lock : free\n");
	}
	sem_post(&muti);
}

void *thrd3(void *arg)
{
	sem_wait(&muti);
	i++;
	tab[i]=e+f;
	printf("result : %d, i: %d\n",tab[i],i);
	if(i==1)
	{
		sem_post(&lock1);
		printf("1st lock : free\n");
	}
	else if(i==2)
	{
		sem_post(&lock2);
		printf("2nd lock : free\n");
	}
	sem_post(&muti);
}

void *thrd4(void *arg)
{
	sem_wait(&lock1);
	printf("1st lock : on\n");

	tab[0]=tab[0]*tab[1];

	sem_wait(&lock2);
	printf("1st lock : on\n");

	tab[0]=tab[0]*tab[2];
	printf("result: %d\n",tab[0]);
}

int main()
{
	sem_init(&lock1,0,0);
	sem_init(&lock2,0,0);
	sem_init(&muti,0,1);
	pthread_t t1, t2, t3, t4;

	pthread_create(&t1, NULL, thrd1, NULL);
	pthread_create(&t2, NULL, thrd2, NULL);
	pthread_create(&t3, NULL, thrd3, NULL);
	pthread_create(&t4, NULL, thrd4, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
}