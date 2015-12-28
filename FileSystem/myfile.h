#include <stdio.h>
#include <stdlib.h>

/* Implement file system create and delete */
int myfs_create(const char *filesystemname , int max_size);
int myfs_destroy(const char *filesystemname);

/* File Operation */
int myfs_file_open(const char *filename);
int myfs_file_close(int fd);
int myfs_file_create(const char *filename);
int myfs_file_delete(const char *filename);
int myfs_file_read(int fd , char *buf , int count);
int myfs_file_write(int fd , char *buf , int count);

/* File Attributes data struction
Name , Identifier , Type , Location , Size , Protection , Time
*/


/* Implement Open-file-Table Struction (file handler) */


/*
Bonus : 
1. directory structure
2. limited file size => so when size is full , show the message
3. concurrently access the file ( using Open-file table )
*/
