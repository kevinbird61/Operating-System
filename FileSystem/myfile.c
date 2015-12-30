#include "myfile.h"

/* Implement file system create and delete */
int myfs_create(const char *filesystemname , int max_size){
	// Create the file 
	FILE *fd = fopen(filesystemname , "w");
	// Store the max_size in this file (top)	
	
		
	return 1;
}

int myfs_destroy(const char *filesystemname);

/* File Operation */
int myfs_file_open(const char *filename);
int myfs_file_close(int fd);
int myfs_file_create(const char *filename);
int myfs_file_delete(const char *filename);
int myfs_file_read(int fd , char *buf , int count);
int myfs_file_write(int fd , char *buf , int count);
