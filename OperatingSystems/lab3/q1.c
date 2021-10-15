#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/resource.h>

clock_t times(struct tms *buf); 


void * Thr1(void *arg) {
  int *a = malloc(sizeof(int));
  int *b = malloc(sizeof(int));
  int *res1 = malloc(sizeof(int));
  *a = 1;
  *b = 2;
  *res1 = *a + *b;
  pthread_exit(res1);
}

void * thr2(void *arg) {
  int *c = malloc(sizeof(int));
  int *d = malloc(sizeof(int));
  int *res2 = malloc(sizeof(int));
  *c = 3;
  *d = 4;
  *res2 = *c - *d;
  pthread_exit(res2);
}

void * thr3(void *arg) {
  int *e = malloc(sizeof(int));
  int *f = malloc(sizeof(int));
  int *res3 = malloc(sizeof(int));
  *e = 5;
  *f = 6;
  *res3 = *e + *f;
  pthread_exit(res3);
}

int main() {
  struct tms start, end;
  struct rusage rstart, rend;

  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  int *res1;
  int *res2;
  int *res3;
  int res = 0;

  int  check1, check2, check3;

  const char *text1 = "Thread 1";
  const char *text2 = "Thread 2";
  const char *text3 = "Thread 3";




  times(&start);
  getrusage(RUSAGE_SELF, &rstart);
  for(int i = 0; i<500; i++)
  {
        /////THREAD 1//////  
  check1 = pthread_create(&thread1, NULL, thr1, (void*) text1); 
  if(check1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",check1);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread1, (void **) &res1);
  
  
  
  

        /////THREAD 2//////
  check2 = pthread_create(&thread2, NULL, thr2, (void*) text2); 
  if(check2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",check2);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread2, (void **) &res2);
  

        /////THREAD 3//////
  check3 = pthread_create(&thread3, NULL, thr3, (void*) text3); 
  if(check3)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",check3);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread3, (void **) &res3);

  
  res = *res1 * *res2 + *res3;
  }

  printf("\n calculus of : (a + b) * (c -d) + (e +f) = %d\n", res);

  times(&end);
  getrusage(RUSAGE_SELF, &rend);

  printf("\nTime: %lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
  printf("%ld usec\n", (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec));
  printf("I/O : %ld\n", (rend.ru_inblock + rend.ru_oublock));
  printf("Context switches : %ld\n", (rend.ru_nvcsw + rend.ru_nivcsw));
}