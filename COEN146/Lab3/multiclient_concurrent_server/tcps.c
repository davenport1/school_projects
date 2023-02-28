
//COEN 146L : Lab3 - Step 4 TCP concurrent server
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab2 – Write a C program for a TCP server 
//             that accepts multiple clients connection for file transfer. 

#include <stdio.h>  
#include <math.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // pen(), close()
#include <errno.h>   // errno
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define N 5 
pthread_t threads[N];
void *file_transfer(void *arg);


int main(int argc, char* argv[]) {
	if (argc != 2){												// Check for proper amount of arguments given
	printf ("Usage: %s <port #> \n",argv[0]);
	exit(0);
} 


	int sock_fd, sin_size;					// Declare server socket file descriptor

	struct sockaddr_in servaddr;								// init serv/client socket addrs
	struct sockaddr_in clienaddr; 

	servaddr.sin_family = AF_INET;								// specify address family as IPv4
	servaddr.sin_port = htons(atoi(argv[1]));					// get port number from arguments given to main
	servaddr.sin_addr.s_addr = INADDR_ANY;						// set IP address to local host
	sin_size = sizeof(struct sockaddr_in);					




	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {	//create socket
		perror("cannot create socket");
		return -1;
	}
	if(bind(sock_fd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) != 0) {	//bind server to local host 
		perror("cannot bind socket");
		return -1;
	}		
	if(listen(sock_fd, 5) != 0) {								//listen for connection
		perror("listen failed");
		return -1;
	}
	else {
		printf("Server listening for client at port %d...\n", atoi(argv[1]));
	}
	for(int i = 0; i < N; i++) {
		int* connfd=malloc(sizeof(int));
		*connfd = accept(sock_fd, (struct sockaddr *)&clienaddr, (socklen_t*)&sin_size);
		pthread_create(&threads[i], NULL, file_transfer, connfd);
		sleep(5);
	}
	close(sock_fd);
	
    return 0;
}


void *file_transfer(void *arg) {
	int connfd, rb, size_read;
	char rbuf[1024], sbuf[1024];								// Declare receiving and sending buffers of size 1k bytes
	FILE* src;
	
	connfd = *(int*)arg;
	if((rb = read(connfd, rbuf, sizeof(rbuf))) > 0) {
		bzero(sbuf, sizeof(sbuf));
		rbuf[rb] = '\0';
		printf("Client sent: %s\n", rbuf);

		if ((src = fopen(rbuf, "r")) == NULL) {
			perror("File failed to open\n");
		} 
		fread(sbuf, sizeof(char), sizeof(sbuf), src);	
		printf("file name: %s\n", rbuf);
		printf("contents read: %s\n", sbuf);
		write(connfd, sbuf, sizeof(sbuf));
	}
	else {
		printf("Connection Failed\n");
	}

	fclose(src);
	close(connfd);

}