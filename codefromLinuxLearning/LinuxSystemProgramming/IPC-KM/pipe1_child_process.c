#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h>

int main(int argc, char *argv[])
{
   int arr[] = {1,2,3,4,5,6,7,8,9};
   int arrSize = sizeof(arr)/sizeof(int);
   int start, end, result=0;
   int fd[2];

   if(pipe(fd)==-1){
      perror("PIPE ERRPR: ");
      return -1;
   }

   int id1 = fork();
   
   if(id1 == -1){
      perror("FORK 1 ERROR: ");
      return -1;
   }
   int id2 = -1;
   if(id1!=0){
      id2 = fork();
      if(id2 == -1){
       perror("FORK 2 ERROR: ");
       return -1;
      }
   }
   
   if(id1 == 0){
      start = 0;
      end = 3;
   }else if(id2 == 0){
      start = 3;
      end   = 6;
   }else{
      start = 6;
      end = arrSize;
   }
   
   for(int i = start; i<end; i++)
      result+=arr[i];

   printf("Partial Calculation: %d, of PID: %d, PPID: %d\n",result,getpid(),getppid());
   
   
   if(id1 == 0){
      close(fd[0]);
      if(write(fd[1], &result, sizeof(result)) < 0){
      	perror("Child 1 Write: ");
      	return -1;
      }
	   close(fd[1]);
   }else if(id2 == 0){
      close(fd[0]);
      if(write(fd[1], &result, sizeof(result)) < 0){
      	perror("Child 2 Write: ");
      	return -1;
      }
      close(fd[1]);
   }else{
      //sleep(1);
      waitpid(id2, NULL, 0);
      waitpid(id1, NULL, 0);
      int sumFromChild;
      close(fd[1]);
      if(read(fd[0], &sumFromChild, sizeof(sumFromChild)) < 0){
      	perror("READ ERROR: ");
      	return -1;
      }
      
      printf("first element read from Pipe my parent is  %d\n",sumFromChild); 
      int total = result + sumFromChild;

      if(read(fd[0], &sumFromChild, sizeof(sumFromChild)) < 0){
    	perror("READ ERROR: ");
      	return -1;
      }

      printf("second element read from Pipe my parent is  %d\n",sumFromChild); 
      total = total + sumFromChild;

   
     close(fd[0]);
      printf("Total sum is %d\n", total);
   //   waitpid(id1, NULL, 0);
   //   waitpid(id2, NULL, 0);
   }
   //waitpid(id2, NULL, 0);
   //waitpid(id2, NULL, 0);
  
   return 0;
}
