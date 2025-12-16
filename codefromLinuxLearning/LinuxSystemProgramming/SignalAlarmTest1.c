#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void my_sig_handler(int signumber)
{
    printf("Alarm delivered signumber is %d\n", signumber);
    //system("/bin/ls");
    /* exit the process from here*/
    exit(0);	
}



int main()
{
    
    //signal(SIGALRM, my_sig_handler);
    alarm(5);


    //start executing from this line only if not exited in signal handler.
    while(1)
   {
    printf("Waiting for Signal handler\n");  
    sleep(1);
   }
	
    return 0;
}

