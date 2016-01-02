#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
       
/* Implement file system create and delete */
int myfs_create(const char *filesystemname , int max_size);
int myfs_destroy(const char *filesystemname);

/* File Operation */
// if return 1 , remind this filename is open
int myfs_file_open(const char *filename,const char *diskname);

int myfs_file_close(int fd,const char *diskname);
int myfs_file_create(const char *filename);
int myfs_file_delete(const char *filename);
int myfs_file_read(int fd , char *buf , int count);
int myfs_file_write(int fd , char *buf , int count);

/* File Attributes data struction
Name , Identifier , Type , Location , Size , Protection , Time
*/
typedef struct __valid_file{
	char *name;
	int file_id;
}ValidF;
ValidF validFile[128];
/* Implement Open-file-Table Struction (file handler) */


/*
Bonus : 
1. directory structure
2. limited file size => so when size is full , show the message
3. concurrently access the file ( using Open-file table )
*/
int myfs_mkdir(const char *dir_name , const char *diskname);

int myfs_rmdir(const char *dir_name , const char *diskname);
