// COEN 146L : Lab 2 - transfer contents of files using threads
// # Name: Matthew Davenport
// # Date: 9/28/2022
// # Title: Lab2 – file tansfer data using threads
// # Description: This program transfers file contnent
//					using threads 
#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
#include <string.h>

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	
	FILE *src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	FILE *dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	char *buf = malloc((size_t)BUF_SIZE);	//allocate buffer size
	int size_read = 0;						//counter for amount of bytes read
	while(!feof(src)) {
		int count = fread(buf, 1, 10, src);
		size_read += count;					//update amount of bytes read
	}
	fwrite(buf, 1, size_read, dst);			//write up to size_read

	fclose(src);// closes src file pointer
	fclose(dst);// closes dst file pointer
	free(buf); //free buffer 
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function
	int x = func_copy(params.src_filename, params.dst_filename);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	// check correct usage of arguments in command line
	if (argc != 7) {  
		fprintf(stderr, "usage: %s <n connections> ........\n", argv[0]);
		exit(1);
	}
	char* src_filename;
	char* dst_filename;
	char* src_filenames[3]; // array of source files (10 source files)
	// get source filenames from command line
    for(int i = 1; i < 4; i++) {			
        src_filenames[i - 1] = argv[i];
    }
    
	char* dst_filenames[3]; // array of desintation files (10 destination files)
	int j = 0;
	// get destination filenames from command line
    for(int i = 4; i < 7; i++) {
        dst_filenames[j] = argv[i];
		j++;
    }

	int num_threads = 3; // number of threads to create
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	for (i = 0; i < num_threads; i++) {
		thread_params[i].thread_id = threads[i]; // initialize thread parameters
        thread_params[i].src_filename = src_filenames[i];
        thread_params[i].dst_filename = dst_filenames[i];
		pthread_create(&threads[i], NULL, &copy_thread, (void*)&thread_params[i]); // create each copy thread
		// use pthread_create(.....);
	}
    printf("MAde it!");

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
}