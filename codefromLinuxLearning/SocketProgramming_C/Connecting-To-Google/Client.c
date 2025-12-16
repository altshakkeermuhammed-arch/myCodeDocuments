#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


#define MAX 80 
#define PORT 8080 

#define SA struct sockaddr
// Function designed for chat between client and server. 
#if 0
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 
#endif
int main(int argc , char *argv[])
{
	
	int socket_desc;
	struct sockaddr_in server;
	char *message, server_reply[2000];

	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("216.58.193.206"); // Google IP address  ,176.28.50.165
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );

	if (connect(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connecting server - error");
		return 1;
	}
	
	puts("Connected");

	message = "GET / HTTP/1.1\r\n\r\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply);
	
	close(socket_desc);
	
	return 0;
	
 }    
       

