// COEN 146L : Lab 1 - file tansfer for txt and bin files
// # Name: Matthew Davenport
// # Date: 9/22/2022
// # Title: Lab1 – file tansfer data for binary r text
// # Description: This program transfers text from one txt or binary file to another 
//					using functions and then system calls 
//					then evaluates the time taken for both. 

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048 //BUFFER SIZE



// FUNCTIONS
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




// SYSTEM CALLS
// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char* src_filename, char* dst_filename)  {
	int src_fd = open(src_filename, O_RDONLY);	// opens a file for reading
	if (src_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		close(src_fd);
		exit(0);
	}
	// O_WRONLY - write only
	// O_CREAT - create file if it doesn't exist
	// O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
	// opens a file for writing; erases old file/creates a new file
	int dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC);	
	if (dst_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		close(dst_fd);
		exit(0);
	}


	// read/ write loop
	char *buf = malloc((size_t)BUF_SIZE);   // allocate a buffer to store read data
	int size_read = read(src_fd, buf, BUF_SIZE);// reads up to BUF_SIZE bytes from src_filename
	int size_writ = write(dst_fd, buf, size_read); // writes bytes_read to dst_filename
	
	close(src_fd);// closes src_fd file descriptor
	close(dst_fd);// closes dst_fd file descriptor
	free(buf);// frees memory used for buf

	return 0;
}





// TIME CHECKER
// checks the runtime to copy a file using functions vs syscalls
void check_copy_times(char* src_filename, char* dst_filename) {
	clock_t func_start, func_end, syscall_start, syscall_end;
	double func_time, syscall_time;
	// capture runtime of func_copy() using start clock, call the copy, end the clock
	func_start = clock();
    func_copy(src_filename, dst_filename);
    func_end = clock();
    func_time = ((double) (func_end - func_start)); // CLOCKS_PER_SEC;

	// capture runtime of syscall_copy() using start clock, call the copy, end the clock
	syscall_start = clock();
    syscall_copy(src_filename,dst_filename);
    syscall_end = clock();
    syscall_time = ((double) (syscall_end - syscall_start)); // CLOCKS_PER_SEC;

	printf("time to copy using functions: %.7f\n", func_time);
	printf("time to copy using syscalls: %.7f\n", syscall_time);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}
	//get the source and destination files from the command line arguments
	char* src_filename = argv[1];
	char* dst_filename = argv[2];
	//call the check copy times function
	check_copy_times(src_filename, dst_filename);
	return 0;
}