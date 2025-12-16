#include <stdio.h>
#include <unistd.h>

int static my_global_var = 100;

int main()
{
	
        int static my_local_var = 200; 
        pid_t pid;

	//Clone

        printf("Hello Before \n");
        sleep(5);
	
	if( (pid = fork()) > 0)  //Parent process
	{
		sleep(5);
                printf("This is printed from the context of Parent Process--------\n");
                
                printf("Original Value of Global variable %d \n", my_global_var);
                printf("Original Value of Local variable %d \n", my_local_var);

                my_global_var = my_global_var + 10;
                my_local_var  = my_local_var + 10;
                printf("Modifed Value of Global variable %d \n", my_global_var);
                printf("Modifed Value of Local variable %d \n", my_local_var);
                printf("---------------------------------END of Parent \n");
                sleep(4);
  

	}
	else    //Child Process
	{
		printf("This is printed from the context of child Process-------\n");
                
                printf("Original Value of Global variable %d \n", my_global_var);
                printf("Original Value of Local variable %d \n", my_local_var);

                my_global_var = my_global_var + 20;
                my_local_var  = my_local_var + 20;
                printf("Modifed Value of Global variable %d \n", my_global_var);
                printf("Modifed Value of Local variable %d \n", my_local_var);
                printf("---------------------------------END of Child \n");
                sleep(4);
	}	
     
        
        printf("Hello After my th Process \n"); 
        getchar();

	return 0;
}

