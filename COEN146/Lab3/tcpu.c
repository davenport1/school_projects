//COEN 146L : Lab3 - Steps 1 TCP server
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab2 – Write a C program for a TCP server 
//             that accepts a client connection for file transfer. 



#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>




// struct sockaddr_in {
//     sa_family_t    sin_family; /* address family: AF_INET */
//     in_port_t      sin_port;   /* port in network byte order */
//     struct in_addr sin_addr;   /* internet address */
// };
// /* Internet address. */
// struct in_addr {
//     uint32_t       s_addr;     /* address in network byte order */
// };
// in terminal pass IP address, port number, source file then destination file.  *******
// client steps: 
// get socket
// connect --> open connection to server using client socket created
// read and write data transfer with server once connection established 
// close connection 


int main(int argc, char* argv[]) {
    // check correct amount of cli args given
    if(argc != 5) {
        printf ("Usage: %s <port #> \n",argv[0]);
        return -1;
    }


    int clien_fd, rb, sin_size; 
    char rbuf[1024], sbuf[1024];
    if((clien_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create socket");
        return -1;
    }


    struct sockaddr_in clienaddr;
    struct hostent *host;
    host = (struct hostent *) gethostbyname(argv[1]);

	clienaddr.sin_family = AF_INET;								// specify address family as IPv4
	clienaddr.sin_port = htons(atoi(argv[2]));					// get port number from arguments given to main
	clienaddr.sin_addr = *((struct in_addr *)host->h_addr);

    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    //Connect to the server
    if (connect(clien_fd, (struct sockaddr *)&clienaddr, sizeof(struct sockaddr))){
        perror("Failure to connect to the server");
        return -1;
    }
    
    //Client begins to write and read from the server
    while(1){
        printf("Client: Type a message to send to Server\n");
        scanf("%s", sbuf);
        write(clien_fd, sbuf, sizeof(sbuf));
        read(clien_fd, rbuf, sizeof(rbuf));
        printf("Server: sent message: %s\n", rbuf);
    }
    //Close socket descriptor
    close(clien_fd);
    return 0;
}