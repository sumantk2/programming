#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for memset */
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORTNO 25001

void read_from_client(int socketfd)
{
	int n;
	char buffer[256];
	char *server_string = "Hello from server";
	memset(buffer, '\0', sizeof(buffer));
	
	n = read(socketfd, buffer, 256);
	if(n < 0) {
		perror("error on read");
		exit(1);
	}
	printf("Message from the client = %s", buffer);
	printf("size of buffer = %d", sizeof(buffer));
	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, server_string);
	
	n = write(socketfd, buffer, sizeof(buffer));
	if(n < 0) {
		perror("error on write to client");
		exit(1);
	}
	return;
}
	

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, port, client_address;
	pid_t pid;
	char buf[256];
	struct sockaddr_in serv_addr, cl_addr;
	socklen_t size;
	
	/* create a socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("\nerror opening socket");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_port = htons(SERVER_PORTNO);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	/* have a look at it */
	serv_addr.sin_family = AF_INET;
	
	/*bind the socket */
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("error on binding the socket");
		exit(1);
	}
	
	listen(sockfd, 5);
	size = sizeof(cl_addr);
	for(;;) {
		newsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &size);
		if(newsockfd < 0) {
			perror("error on accept");
			exit(1);
		}
		if((pid = fork()) < 0) {
			perror("error on fork");
			exit(1);
		}
		else if(pid) {
			/* parent process */
			close(newsockfd);
		} else {
			close(sockfd);
			read_from_client(newsockfd);
			close(newsockfd);	
			exit(0);
		}
	}
		
}
