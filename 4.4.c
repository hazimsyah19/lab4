#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	int socket_desc,new_socket;
	struct sockaddr_in server,client;
	char message[2000],buffer[2000];


	// Socket creation 
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc == -1)
	{
		printf("Socket creation is failed");
		exit(0);
	}

	puts("Socket created... ");

	//assign ip and port
	server.sin_family      =   AF_INET;
	server.sin_addr.s_addr =   INADDR_ANY;
	server.sin_port        =   htons(5555);
	
	//bind socket
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
	}
	puts("Bind done");

	listen(socket_desc,3);


	int c = sizeof(struct sockaddr_in);
	while(new_socket = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c))
	{
		printf("Waiting message from the client... \n");
		if((recv(new_socket, buffer, 2000, 0)) > 0)
		{
			printf("Message from client: %s \n",buffer);
			//Send data to client
			printf("Enter message for client: ");
			fgets(buffer,2000,stdin);
			send(new_socket,buffer,2000,0);
		}
		else if ((recv(new_socket,buffer,2000,0)) == 0)
		{
			puts("Client disconnected ..\n");
			fflush(stdout);
		}
	}


	if(new_socket < 0)
	{
		perror("accept()");
	}
	return 0;
}
