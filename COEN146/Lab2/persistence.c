//COEN 146L : Lab2, step 4
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab2 –  
// # Description: 
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {  // check correct usage
		fprintf(stderr, "usage: %s <n connections> \n", argv[0]);
		exit(1);
	}
        //Declare and values to n (n connections), np (np parralel connections), RTT0, RTT1, RTT2, RTTHTTP, RTTDNS, .. 
        int RTT0 = 3;           //first DNS server
        int RTT1 = 20;          //second DNS server
        int RTT2 = 26;          //third DNS server
        int RTTHTTP = 47;       //local host to web server
        int objects = 6;
        
        int oneObject = RTT0 + RTT1 + RTT2 + 2*RTTHTTP;     //one object RTT
        int sixObjects = RTT0 + RTT1 + RTT2 + 2*RTTHTTP + 2*objects*RTTHTTP;        //six objects non persistent

        
        printf("One object: %d msec\n", oneObject);
        printf("Non-Persistent 6 objects: %d msec\n", sixObjects);

        //find how many np (parralel connections)
        int n = atoi(argv[1]);

        int pers = RTT0 + RTT1 + RTT2 + 2*RTTHTTP + 2 * objects / n * RTTHTTP;
        int nonPers = RTT0 + RTT1 + RTT2 + 2*RTTHTTP + 2 * objects / n * 2 * RTTHTTP;

        printf("%d parallel connection - Persistent: %d msec\n", n, pers);
        printf("%d parallel connection - Non-Persistent: %d msec\n", n, nonPers);

return 0;
}