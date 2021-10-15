#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/resource.h>
clock_t times(struct tms *buf); 

int main()
{
  // P1 : a+b, save in shared space then exit
  // P2 : c+d, wait for P1, do the multiply operation, save result in shared space then exit
  // P3 : e+f, wait for P2, do ther final operation
  
  // wait version : P3 should be parent of P2, and P2 parent of P1
  
  int a = 5, b = 7, c = 8, d = 9, e = 4, f = 3;
  
  // create shared space
  int id = shmget(45678, 2*sizeof(int), IPC_CREAT | 0600);
  int *tab = shmat(id, NULL, 0);
  
  
  
  // this is P3
  if (fork() == 0) {
  // this is P2
  
    if (fork() == 0) {
      // this is P1
      tab[0] = a + b;
      exit(0);
    }



    int tmp = c + d;
    wait(NULL); // wait for P1 to end
    tab[1] = tab[0] * tmp;
    exit(0);
  
  }
  // this is P3
  int tmp = e + f;
  wait(NULL); // wait for P2 to friend
  printf("result = %d\n", tmp * tab[1]);
 times(&end);
  getrusage(RUSAGE_SELF, &rend);

  printf("\nTime: %lf usec\n", (end.tms_utime+end.tms_stime-start.tms_utime-start.tms_stime)*1000000.0/sysconf(_SC_CLK_TCK));
  printf("%ld usec\n", (rend.ru_utime.tv_sec-rstart.ru_utime.tv_sec)*1000000 +(rend.ru_utime.tv_usec-rstart.ru_utime.tv_usec)+(rend.ru_stime.tv_sec-rstart.ru_stime.tv_sec)*1000000 +(rend.ru_stime.tv_usec-rstart.ru_stime.tv_usec));
  printf("I/O : %ld\n", (rend.ru_inblock + rend.ru_oublock));
  printf("Context switches : %ld\n", (rend.ru_nvcsw + rend.ru_nivcsw));
}