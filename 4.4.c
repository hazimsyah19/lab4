#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{		
    while(1){
	int socket_desc;
	struct sockaddr_in server;
	char message[2000],buffer [2000];

	// Create the socket 
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
		printf("Socket create failed... \n");
		exit(0);
	}

	// Assign IP and PORT
	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = inet_addr("10.0.2.18");
	server.sin_port = htons(5555);

	//Connect to remote server
	if(connect(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0)
	{
		puts("Connect error \n");
		return 1;
	}
	else
		printf("connected to the server... \n");

	//Send some data
	printf("Enter message to send to server : ");
	fgets(message,2000,stdin);
	if(send(socket_desc,message,strlen(message),0) < 0)
	{	
		puts("Send failed");
		return 1;
	}

	printf("Waiting for the server to reply.... \n");
	recv(socket_desc,buffer,2000,0);
	printf("Message from the server : %s\n",buffer);
    }
	return 0;
}
