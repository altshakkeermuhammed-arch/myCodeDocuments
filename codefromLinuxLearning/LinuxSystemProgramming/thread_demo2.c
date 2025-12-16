#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *ThreadFunc(void *args)
{
	int i;
        int test;
        if ( (*(char*)args) == 1 )
        {
          test = 100;
        }
        else
        {
          test = 200;
        }
	for(i=0;i<25;++i)
	{
		printf("This is from child thread i=%d\n",i);
                printf("This is from child thread value the came via argument =%d , %d --\n",(*((char*)args)),test++);
                printf("---------------------------------------------------\n");
		sleep(1);
	}	
}

int main()
{
	pthread_t mythread1;
        pthread_t mythread2;
	void *thread_result;
	int j=0;
        char array[3] = {1,2,3};
	pthread_create(&mythread1, NULL, ThreadFunc, &array[0]);
        pthread_create(&mythread2, NULL, ThreadFunc, &array[1]);	
        //pthread_create(&mythread, NULL, ThreadFunc,NULL);	

	for(j=0;j<25;j++)
	{
		sleep(1);
		printf("-----------this is from main or parent thread----------- j=%d\n", j);
	}

	pthread_join(mythread1, &thread_result);
        pthread_join(mythread2, &thread_result);
	return 0;
}


