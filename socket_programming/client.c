#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 25001

void send_to_server(int sockfd) 
{
	char buffer[256];
	int n;
	memset(buffer, '\0', sizeof(buffer));
	printf("\n Enter the message to server:");
	fgets(buffer, 256, stdin);
	n = write(sockfd, buffer, sizeof(buffer));
	if(n < 0) {
		perror("error on send - client");
		exit(1);
	}
	
	memset(buffer, '\0', sizeof(buffer));
	n = read(sockfd, buffer, sizeof(buffer));
	if(n < 0) {
		perror("error on read - client");
		exit(1);
	}
	printf("\n message from server = %s", buffer);
	return;
}
int main(int argc, char *argv[])
{
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	socklen_t size;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	if(sockfd < 0) {
		perror("error on opening socket");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	size = sizeof(struct sockaddr_in);
	if(connect(sockfd, (struct sockaddr *)&serv_addr, size) < 0) {
		perror("error on connect");
		exit(1);
	}
	send_to_server(sockfd);
	return 0;
}
