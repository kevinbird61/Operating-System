#include "myfile.h"

/* Implement file system create and delete */
int myfs_create(const char *filesystemname , int max_size){
	// Create the file  FIXME -> check the currently file , if is not exist => and then create , else , show the error message and then return
	if( access( filesystemname, F_OK ) != -1 ) {
	    // file exists
	    printf("Oops! the named disk has been created before!\n");
	} else {
	    // file doesn't exist
	    // file not exist
		FILE *fd = fopen(filesystemname , "w");
		if(fd < 0 ){
			// Open file error
			return -1;
		}
		// Store the max_size in this file (top)	
		fprintf(fd,"%d\n",max_size);
		fclose(fd);
	}
	return 1;
}
/* Find the disk-used file and destroy it */
int myfs_destroy(const char *filesystemname){
	remove(filesystemname);
	return 1;
}

/* File Operation */
int myfs_file_open(const char *filename){
	// Check out the data structure and file attributes to get correct reading point
	
}

int myfs_file_close(int fd){
	// Close the chosen current writing point
}

int myfs_file_create(const char *filename){
	// Create a new file with the correct data structure and file attributes
}

int myfs_file_delete(const char *filename){
	// Delete the chosen current file in data structure and file attributes
}

int myfs_file_read(int fd , char *buf , int count){
	// read from the chosen file with limited-number of word
}

int myfs_file_write(int fd , char *buf , int count){
	// write in the chosen file with limited-number of word
}
