// UDP Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


//Declare a Header structure that holds length of a packet
typedef struct {
    int len;
} Header;

//Declare a packet structure that holds data and header
typedef struct {
    Header header;
    char data[1024];
} Packet;

// As you can see above there are two parameters to this structure, one that stores the length of the
// data being read or written, other the actual data itself.


int main(int argc, char *argv[]){
	 //Get from the command line port#
 	if (argc != 2){
		printf ("Usage: %s <port #> \n",argv[0]);
		exit(0);
 	} 
 	//Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
 	int sockfd;

 	//Declare server address to which to bind for receiving messages and client address to fill in sending address
 	struct sockaddr_in servAddr, clienAddr;
	socklen_t addrLen = sizeof(struct sockaddr);

 	//Open a UDP socket, if successful, returns adescriptor associated with an endpoint 
 	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    	perror("Failure to setup an endpoint socket");
    	exit(1);
 	}
 
 	//Setup the server address to bind using socket addressing structure
 	servAddr.sin_family = AF_INET;
 	servAddr.sin_port = htons(atoi(argv[1])); //Port 5000 is assigned
 	servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)

 	//Set address/port of server endpoint for socket socket descriptor
 	if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
		perror("Failure to bind server address to the endpoint socket");
    	exit(1);
 	}
 
	//Sever continuously waits for messages from client, then prints incoming messages.

    printf("Server waiting for messages from client: \n");
	Packet packToRecv;
	int nr = recvfrom(sockfd, packToRecv.data, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen);
	packToRecv.data[nr] = '\0';
	packToRecv.header.len = strlen(packToRecv.data);
	printf("Client with IP: %s and Port: %d sent message: %s\n", inet_ntoa(clienAddr.sin_addr),ntohs(clienAddr.sin_port), packToRecv.data);
	printf("Contents of file: %s", packToRecv.data);
	FILE *dst = fopen("dst.txt", "w");
	if (dst == NULL) { // fopen() error checking
        fprintf(stderr, "unable to open/create %s for writing: %i\n", packToRecv.data, errno);
        exit(0);
    }
	fwrite(packToRecv.data, sizeof(char), packToRecv.header.len, dst);
	fclose(dst);
	close(sockfd);

 	return 0;
}
