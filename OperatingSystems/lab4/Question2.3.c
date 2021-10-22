#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t lock1, lock2;

void *thrd1(void *arg)
{
    system("firefox");
    printf("launched Firefox : 1st");
    sem_post(&lock1);
}
void *thrd2(void *arg)
{
    sem_wait(&lock1);
    system("vi");
    printf("launched Vi : 2nd");
    sem_post(&lock2);
}
void *thrd3(void *arg)
{
    sem_wait(&lock2);
    system("gnumeric");
    printf("launched Gnumeric : 3rd");
}

int main()
{
    pthread_t tr1, tr2, tr3;
    sem_init(&lock1, 0, 0);
    sem_init(&lock2, 0, 0);
    pthread_create(&tr1, NULL, thrd1, NULL);
    pthread_create(&tr2, NULL, thrd2, NULL);
    pthread_create(&tr3, NULL, thrd3, NULL);
    pthread_join(tr1, NULL);
    pthread_join(tr2, NULL);
    pthread_join(tr3, NULL);
    sem_destroy(&lock1);
    sem_destroy(&lock2);
}