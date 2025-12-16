#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void *thread_function1(void *arg);
void *thread_function2(void *arg);
void UserSigHandler(int sig);

char message1[] = "Hello Thread1";
char message2[] = "Hello Thread2";

pthread_t  a_thread, b_thread;

int main() {
    int res;

    void *thread_result1, *thread_result2;
	
    res = pthread_create(&a_thread, NULL, thread_function1, (void *)message1);
    if (res != 0) {
        perror("Thread creation1 failed");
        exit(EXIT_FAILURE);
    }

     printf("In main function threadid  a_thread = %d  \n",  a_thread); 
	
	res = pthread_create(&b_thread, NULL, thread_function2, (void *)message2);
    if (res != 0) {
        perror("Thread creation2 failed");
        exit(EXIT_FAILURE);
    }

	
	 printf("Waiting for thread2 to finish.. which will send USER SIG 1.\n");
         printf(".................................................................................\n");
	res = pthread_join(b_thread, &thread_result2);
    if (res != 0) {
        perror("Thread2join failed");
        exit(EXIT_FAILURE);
    }
	printf("Thread2 joined, it returned %s\n", (char *)thread_result2);
         printf(".................................................................................\n");

	
	
		
    printf("Waiting for thread1 to finish.. which will wait for USER SIG 1..\n");
    printf(".................................................................................\n");
    res = pthread_join(a_thread, &thread_result1);
    if (res != 0) {
        perror("Thread1 join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread1 joined, it returned %s\n", (char *)thread_result1);
    printf(".................................................................................\n");

    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg) {
    int ret_pause ;

    printf("thread_function1 waiting for the USER SIG 1 to receive\n");
    printf(".................................................................................\n");
    (void) signal(SIGUSR1, UserSigHandler);
      ret_pause =  pause();


   // printf( " ret_pause  value is %d \n" ,ret_pause );
   
    printf("thread_function1 resumed since  USER SIG 1 is rceived. Thread Argument was %s\n", (char *)arg);
   printf(".................................................................................\n");

  printf("In function \nthread id\n threadid  = %d , %d \n", pthread_self() ,  a_thread); 
   
    pthread_exit("Thank you for the CPU time");
}

void *thread_function2(void *arg) {
    
   printf("thread_function2 will send USER SIG 1 now. Press Enter to send singnal\n");
   printf(".................................................................................\n");
   getchar();

    pthread_kill( a_thread,SIGUSR1);

   printf("thread_function2 posted the  USER SIG 1 signal. Thread Argument was %s\n", (char *)arg);
   printf(".................................................................................\n");
   
    pthread_exit("Thank you for the CPU time");
}

void UserSigHandler(int sig)
{
    pthread_t thread_id;
   printf("Printing From UserSigHandler - ! - I got signal - Hope Thread1 can resume now. Signal number is  %d\n", sig);
    printf(".................................................................................\n");
    thread_id = pthread_self() ;

 //   printf("Printing From UserSigHandler - ! -current executing thread id  is %d \n",(int) id);
    //printf( " %d " , thread_id);
   
    printf("In function \nt process id = %d\n", getpid()); 
    printf(".................................................................................\n");

   //(void) signal(SIGINT, SIG_DFL);
}