

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

int arr[] = {1,2,3,4,5,6,7,8,9};

   int arrSize = sizeof(arr)/sizeof(int);
   int start, end, result=0;
   int fd[2];
   int sumFromChild;


void *ThreadFuncA(void *args)
{
	int i,j;

        for(i=0;i<4;++i)
	{
		printf("This is from thread A\n");
		sleep(1);
        }
	for(i=0;i<1000;++i)
	{
		printf("This is from thread A\n");
		sleep(1);
                if(read(fd[0], &sumFromChild, sizeof(sumFromChild)) < 0){
	    		perror("READ ERROR: ");
	      		return -1;
      		}
	}	
}

void *ThreadFuncB(void *args)
{
	int i;
	for(i=0;i<1000;++i)
	{
		printf("This is from thread B\n");
		sleep(3);
                if ( i == 25)
                {
                   if(write(fd[1], &result, sizeof(result)) < 0){
		      	perror("Child 2 Write: ");
		      	return -1;
		   }

                }
	}	
}

int main()
{
	pthread_t mythreadA,mythreadB;
	void *thread_result;
	int j=0;

        
	if(pipe(fd)==-1){
	   perror("PIPE ERRPR: ");
	   return -1;
	}

	pthread_create(&mythreadA, NULL, ThreadFuncA, NULL);

        pthread_create(&mythreadB, NULL, ThreadFuncB, NULL);	


	pthread_join(mythreadA, &thread_result);
        pthread_join(mythreadB, &thread_result); 
	return 0;
}

