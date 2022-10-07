/** Name: Matthew Davenport
# Date: 2/8/2022
# Title: Lab5 Producer consumer
# Description: This program solves the producer
# consumer problem utilizing semaphores 
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define MAX_BUFFER 10

pthread_t pro;                  //producer thread
pthread_t con;                  //consumer thread
sem_t *mutex;                   
sem_t *full;
sem_t *empty; 
int buffer[MAX_BUFFER];
int counter = 0;

void* producer(void* arg) {
    do {
        int item = rand() % 1000 + 1;   //entering an integer between 0 and 1000
        sem_wait(empty);                //reduce the empty slot by one       
        sem_wait(mutex);                //lock critical region
        
        //add item into buffer
        while(counter == MAX_BUFFER) ;  //busy wait if buffer full

        if(counter < MAX_BUFFER) {
            buffer[counter] = item;
            counter++;
        }

        printf("Item produced is: %d\n", buffer[counter -1]);
        sem_post(mutex);                //exit critical region
        sem_post(full);                 //one item added
        sleep(1);
    } while(1);
}

void* consumer() {
    do {
        int item;                       //item to consume
        sem_wait(full);                 //decrement, consuming one item
        sem_wait(mutex);                //lock critical region

        //remove next item from buffer
        while(counter == 0) ;           //busy wait if no item to consume

        if(counter > 0) {
            item = buffer[--counter];
        }

        printf("Item consumed is: %d\n", item);
        sem_post(mutex);                //unlock
        sem_post(empty);                //one less item 
        sleep(1);
    } while(1);
}

int main(int argc, char *argv[]) {
    int err = 0;                        //variable to hold error code

    //ensure each semaphore is initialized successfully
    mutex = sem_open("mutex",O_CREAT, 0644, 1);
    if(mutex == SEM_FAILED) {
        printf("Failed to open semaphore for 'mutex'\n");
        exit(-1);
    }
    full = sem_open("full",O_CREAT, 0644, 0);
    if(full == SEM_FAILED) {
        printf("Failed to open semaphore for 'full'\n");
        exit(-1);
    }
    empty = sem_open("empty",O_CREAT, 0644, MAX_BUFFER);
    if(empty == SEM_FAILED) {
        printf("Failed to open semaphore for 'empty'\n");
        exit(-1);
    }
    
    //ensure each thread is created successfully
    err = pthread_create(&pro, NULL, producer, NULL);   //create producer thread
    if(err != 0) {
        printf("ERROR: producer thread returned: %d\n", err);
        exit(-1);
    }

    err = pthread_create(&con, NULL, consumer, NULL);   //create consumer thread
    if(err != 0) {
        printf("ERROR: consumer thread returned: %d\n", err);
        exit(-1);
    }


    pthread_exit(NULL);

    return 0;

}
