
#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"
//extern void add(int,int);
  
int main(int argc, char *argv[])
{ 

   
    printf("I am in main function\n"); 	
    //printf("number of args and what you pased is %d ,%s\n", argc, *argv[0] );

  //  printf("number of args and what you pased is %s, %s %s %s\n", argc, argv[0],argv[1],argv[2]);
    
    add (100,200);

    return 0;
   
} 
