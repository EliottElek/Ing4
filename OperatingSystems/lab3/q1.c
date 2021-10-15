#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/resource.h>

clock_t times(struct tms *buf); 


void * f1(void *arg) {
  int *a = malloc(sizeof(int));
  int *b = malloc(sizeof(int));
  int *result1 = malloc(sizeof(int));
  *a = 1;
  *b = 2;
  *result1 = *a + *b;
  pthread_exit(result1);
}

void * f2(void *arg) {
  int *c = malloc(sizeof(int));
  int *d = malloc(sizeof(int));
  int *result2 = malloc(sizeof(int));
  *c = 3;
  *d = 4;
  *result2 = *c - *d;
  pthread_exit(result2);
}

void * f3(void *arg) {
  int *e = malloc(sizeof(int));
  int *f = malloc(sizeof(int));
  int *result3 = malloc(sizeof(int));
  *e = 5;
  *f = 6;
  *result3 = *e + *f;
  pthread_exit(result3);
}

int main() {
  struct tms start, end;
  struct rusage rstart, rend;

  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  int *result1;
  int *result2;
  int *result3;
  int res = 0;

  int  verif1, verif2, verif3;

  const char *text1 = "Thread 1";
  const char *text2 = "Thread 2";
  const char *text3 = "Thread 3";




  times(&start);
  getrusage(RUSAGE_SELF, &rstart);
  for(int i = 0; i<500; i++)
  {
        /////THREAD 1//////  
  verif1 = pthread_create(&thread1, NULL, f1, (void*) text1); 
  if(verif1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",verif1);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread1, (void **) &result1);
  
  
  
  

        /////THREAD 2//////
  verif2 = pthread_create(&thread2, NULL, f2, (void*) text2); 
  if(verif2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",verif2);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread2, (void **) &result2);
  

        /////THREAD 3//////
  verif3 = pthread_create(&thread3, NULL, f3, (void*) text3); 
  if(verif3)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",verif3);
         exit(EXIT_FAILURE);
     }
  pthread_join(thread3, (void **) &result3);

  
  res = *result1 * *result2 + *result3;
  }

  printf("\n calculus of : (a + b) * (c -d) + (e +f) = %d\n", res);

  times(&end);
  getrusage(RUSAGE_SELF, &rend);

  printf("\nTime: %lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
  printf("%ld usec\n", (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec));
  printf("I/O : %ld\n", (rend.ru_inblock + rend.ru_oublock));
  printf("Context switches : %ld\n", (rend.ru_nvcsw + rend.ru_nivcsw));
}