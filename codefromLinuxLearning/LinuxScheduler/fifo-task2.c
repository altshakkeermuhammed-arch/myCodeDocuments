#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
  printf("Setting SCHED_FIFO and priority to 2");
  struct sched_param param;
  int ret;
  param.sched_priority = 2;
  ret = sched_setscheduler(0, SCHED_FIFO, &param);
  if ( ret == -1)
  {
    printf(" Errror in scheduler set  \n"); 
    return (1);
  }   
  int n = 0;
  while(1) {
    n++;
    if (!(n % 10000000)) {
      //printf("%s FIFO Prio %d running (n=%d)\n",argv[2], param.sched_priority,n);
	printf("FIFO Prio %d running (n=%d)\n",param.sched_priority,n);
    }

  }
}
