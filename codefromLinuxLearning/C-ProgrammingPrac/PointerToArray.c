
#include <stdio.h>
#include <stdlib.h>

  
int main() 
{ 
 // Pointer to an array of five numbers 
 // Here Array is pointer, hence 'a' pointer to pointer ?
    int(*a)[5]; 
  
    int b[5] = { 1, 2, 3, 4, 5 }; 
  
    int i = 0; 
  
    // Points to the whole array b 
  
    a = &b; 
  
    for (i = 0; i < 5; i++)   
    //printf("%d\n", *((*a) + i))) ); 

     printf("%d\n", *((*a)+i)  ); 

     printf(" Printing address to compare\n");
  
     printf("%d\n %d\n %d\n", (*a), b, a  ); // array address, array address, pointer to array address
 
     for (i = 0; i < 5; i++)   
     printf("%d\n", *((a)+i)  );  // address of each array element will be printed
    return 0;	

} 
