//COEN 146L : Lab3 - Steps 1 TCP server
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab3 – Write a C program for a TCP server 
//             that accepts a client connection for file transfer. 

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 

int main(int argc, char* argv[]) {
    // check correct amount of cli args given
    if(argc != 5) {
        printf ("Usage: %s <port #> \n",argv[0]);
        return -1;
    }



    int clien_fd, rb, sin_size; 
    char rbuf[1024], sbuf[1024];
    struct sockaddr_in servAddr;
    struct hostent *host;
    host = (struct hostent *) gethostbyname(argv[1]);

    if((clien_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create socket");
        return -1;
    }

	servAddr.sin_family = AF_INET;								// specify address family as IPv4
	servAddr.sin_port = htons(atoi(argv[2]));					// get port number from arguments given to main
	servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    //Connect to the server
    if (connect(clien_fd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))){
        perror("Failure to connect to the server");
        return -1;
    }
    
    char *src_filename = argv[3];
    char *dst_filename = argv[4]; 
    
    printf("src_filename: %s\n", src_filename);
    write(clien_fd, src_filename, sizeof(src_filename));

    if((rb = read(clien_fd, rbuf, sizeof(rbuf))) > 0) {
        rbuf[rb] = '\0';
    }
    printf("Server: sent message: %s\n", rbuf);

    FILE *dst = fopen(dst_filename, "w");   // opens a file for writing; erases old file/creates a new file
    if (dst == NULL) { // fopen() error checking
        fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
        exit(0);
    }
    fwrite(rbuf, sizeof(char), strlen(rbuf), dst);         //write up to size read from server

    //Close socket descriptor
    close(clien_fd);
    fclose(dst);
    return 0;
}
