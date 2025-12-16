#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("system call usage starts here\n");
	printf("-------------------------------------------\n");
	
	int ret = 0;
	
	ret = write(1 ,"Hello World priting from write API\n",35);
	printf("ret: %d\n" ,ret);
	if ( ret<0)
	  perror("Write failed");
	else
	  printf("Write successful\n");
	return 0;

}

