/** Name: Matthew Davenport
# Date: 2/8/2022
# Title: Lab5 Producer consumer 
# Description: This program solves the producer
# consumer problem utilizing condition variables
**/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define MAX_BUFFER 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int buffer[MAX_BUFFER];
int counter = 0;
int add =0;
int rem = 0;




void* producer(void* arg) {
    do { 
        printf("Inside producer\n");
        int item = rand() % 100;            //produce random item
        pthread_mutex_lock(&lock);          //lock critical section

        if(counter > MAX_BUFFER) exit(-1);  //exit due to overflow
        while(counter == MAX_BUFFER)         //busy waiting if buffer is full
            pthread_cond_wait(&empty, &lock);

        printf("Inside critcal region\n");
        //adding item to critical region

        buffer[add] = item;
        add = (add +1) % MAX_BUFFER;
        counter++;
        printf("Item %d has been produced\n",item);

        //Unlock/exit critical region
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&full);
        sleep(1);
    } while (1);

}

void* consumer(void* arg) {
    do {
        int item;
        pthread_mutex_lock(&lock);
        
        while(counter == 0)                //busy wait if buffer is full   
            pthread_cond_wait(&full, &lock);

        if(counter > 0) {
            item = buffer[rem];
            printf("Item %d has been consumed\n", item);
            rem = (rem + 1) % MAX_BUFFER;
            counter--;
        }   
        //unlock/exit critcal region
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&empty);

        sleep(1);
    } while (1);
}

int main(int argc, char* argv[]) {
    printf("Starting main\n");
    
    pthread_t pro, con;

    //ensure each thread is created successfully
    if(pthread_create(&pro, NULL, producer, NULL) != 0) {
        printf("ERROR: producer thread creation failed\n");
        exit(-1);
    }
    if(pthread_create(&con, NULL, consumer, NULL) != 0) {
        printf("ERROR: consumer thread creation failed\n");
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}

