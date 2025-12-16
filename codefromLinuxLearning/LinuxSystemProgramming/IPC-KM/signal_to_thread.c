#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include<signal.h>
#include<sys/types.h>

void *producer(void *arg);
void *consumer(void *arg);
//int counter = 0;
char buffer[5];
void con(int);
void pro(int);
pthread_t a_thread,b_thread;


int main() 
{
    int res;
    void *thread_result;
    
    res = pthread_create(&a_thread, NULL, producer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&b_thread, NULL, consumer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Wait for pthread_join\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}


/***   Producer Thread *****/
void *producer(void *arg) 
{
    (void) signal(SIGUSR1,pro);

    while(1)
	{
	 pause();
	}
	
   pthread_exit("exit");	
}


/***   Consumer Thread *****/
void *consumer(void *arg) 
{
	(void) signal(SIGUSR2, con);
	pthread_kill(a_thread,SIGUSR1);
    	
	while(1)
	{
		pause();
	}
	
     	pthread_exit("exit");	
}


/***   Producer Signal Handler  *****/
void pro(int sig)
{
        char ch='A';
        int x=0,in=0;

        while(x<5)
        {
                buffer[in]=ch;
                in = (in+1)% 5;
                ch++;
                if (in == 0 )
                {
                        ch='A';
                        printf("p:%s\n",buffer);
                }
                x++;
        }
        pthread_kill(b_thread,SIGUSR2);
}


/***   Consumer Signal Handler  *****/
void con(int sig)
{
        int out = 0;
        char data[5];
        int y=5;
        while(y>0)
        {
                data[out] = buffer[out];
                out = (out+1)% 5;
                if (out == 0)
                        printf ("\t:c:%s\n",data);
                y--;
        }
        pthread_kill(a_thread,SIGUSR1);
}