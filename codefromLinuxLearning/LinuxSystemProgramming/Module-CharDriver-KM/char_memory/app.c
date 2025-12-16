#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{

int fd,ret;
char buff[10];

	fd = open("/dev/memory",O_RDWR);
	if (fd < 0)
	perror("open FAILS\n");
	
	ret = write(fd,"SHAK",4);
	printf("write return value:%d\n",ret);
	
	ret = read(fd,buff,100);
	printf("read return value:%d buff[0]:%s \n",ret,buff);

	close(fd);
}
