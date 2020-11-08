#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>


int main (int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_reply[2000];

	//Create socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
	    printf("Could not create socket");
	}
	
	server.sin_addr.s_addr = inet_addr("10.0.2.18");
	server.sin_family      = AF_INET;
	server.sin_port        = htons(8888);


	//Connect to remote server
	if(connect(socket_desc,(struct sockaddr *)&server,sizeof(server))<0)
	{
	    puts("connect error");
	    return 1;
	}

	puts("Connected \n");

	//send some data
	message = "connect";
	if(send(socket_desc,message,strlen(message),0)<0)
	{
	    puts("Send failed");
	    return 1;
	}
	puts("Data Send \n ");

	//Receive a reply from server
	if(recv(socket_desc, server_reply ,2000,0)<0)
	{
	    puts("\n receiving fails \n");
	    return 1;
	}
	puts("\n Receiving fails \n");
	return 0;

	close(socket_desc);
}
