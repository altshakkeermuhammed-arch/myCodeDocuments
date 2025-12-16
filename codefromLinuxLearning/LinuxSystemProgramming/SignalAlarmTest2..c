/*  In alarm.c, the first function, ding, simulates an alarm clock.  */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
    alarm_fired = 1;
}

/*  In main, we tell the child process to wait for five seconds
    before sending a SIGALRM signal to its parent.  */

int main()
{
    pid_t pid;

    printf("alarm application starting\n");
    pid = fork();
    switch(pid) {
    case -1:
      /* Failure */
      perror("fork failed");
      exit(1);
    case 0:
      /* child */
        sleep(5);
       /* kill send specified signal to ( SIGALRM) the mentioned pid. Here sending to parent process */  
        kill(getppid(), SIGALRM);
        /* Exit the child process */
        exit(0);
    }

/*  The parent process arranges to catch SIGALRM with a call to signal
    and then waits for the inevitable.  */

    printf("waiting for alarm to go off\n");
    /* Register for singnal handler */
    (void) signal(SIGALRM, ding);
   
    /* Wait ( blocking call) for the signal to receive. That is singnal handler is invoked*/
    pause();
    if (alarm_fired)
        printf("Ding!\n");

    printf("done\n");
    exit(0);
}
