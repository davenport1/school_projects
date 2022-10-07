//COEN 146L : Lab3 - Steps 1 TCP server
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab2 – Write a C program for a TCP server 
//             that accepts a client connection for file transfer. 

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



// struct sockaddr_in {
//     sa_family_t    sin_family; /* address family: AF_INET */
//     in_port_t      sin_port;   /* port in network byte order... INADDR_ANY for local host */
//     struct in_addr sin_addr;   /* internet address ... */
// };
// /* Internet address. */
// struct in_addr {
//     uint32_t       s_addr;     /* address in network byte order */
// };
// int sockfd = socket(domain, type, protocol) protocol = 0 for internet protocol 
// int bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// int listen(int sockfd, int backlog);
// int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// Reading and writing over socket: 
//   bzero(buffer, 256);
//      n = read(newsockfd, buffer, 255);
//      if (n < 0) error("ERROR reading from socket");
//      printf("Here is the message: %s\n", buffer);
//
// NEED TO USE two terminals, one client one server.  client specifies IP address and port, then source and destination folders. 
// server side arguments are just the port number **

int main(int argc, char* argv[]) {
	if (argc != 2){												// Check for proper amount of arguments given
	printf ("Usage: %s <port #> \n",argv[0]);
	exit(0);
} 


	int server_fd, connect_fd, sin_size;					// Declare server socket file descriptor
	char rbuf[1024], sbuf[1024];								// Declare receiving and sending buffers of size 1k bytes

	struct sockaddr_in servaddr;								// init serv/client socket addrs
	struct sockaddr_in clienaddr; 

	servaddr.sin_family = AF_INET;								// specify address family as IPv4
	servaddr.sin_port = htons(atoi(argv[1]));					// get port number from arguments given to main
	servaddr.sin_addr.s_addr = INADDR_ANY;						// set IP address to local host
	sin_size = sizeof(struct sockaddr_in);					




	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {	//create socket
		perror("cannot create socket");
		return -1;
	}
	if(bind (server_fd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) != 0) {	//bind server to local host 
		perror("cannot bind socket");
		return -1;
	}		
	if(listen(server_fd, 5) != 0) {								//listen for connection
		perror("listen failed");
		return -1;
	}
	else {
		printf("Server listening for client at port %d...\n", atoi(argv[1]));
	}


	while(1) {
		//attempt connection  with the client 
		if(connect_fd = accept(server_fd, (struct sockaddr *)&clienaddr, (socklen_t*)&sin_size) < 0) {
			perror("Failed to accept connection with client");
			return -1;
		} 
		else {
			printf("Connection estblished with client %d at port %d \n",atoi(inet_ntoa(clienaddr.sin_addr)), ntohs(clienaddr.sin_port));
		}

		int s_read;
		while(s_read = read(connect_fd, rbuf, sizeof(rbuf)) > 0) {
			bzero(sbuf, 256);
        	int n = read(server_fd, sbuf, 255);
        	if (n < 0) error("ERROR reading from socket");
        	printf("Here is the message: %s\n", sbuf);
		}
		close(connect_fd);
	}
	
	close(server_fd);

    
    return 0;
}