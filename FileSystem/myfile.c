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
		fprintf(fd,"home : 1");
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
int myfs_file_open(const char *filename,const char *diskname){
	// Check out the data structure and file attributes to get correct reading point
	if( access( diskname, F_OK ) != -1 ) {
		// disk exists
		// search the file in this disk
	    	char linebuffer[512] ;
	    	char buffer1[512];
	    	char buffer2[512];
	    	FILE *fp = fopen(diskname,"r+");
	    	if(fp == NULL){
	    		printf("open error");
	    		return -1;
	    	}
	    	while(fgets(linebuffer,512,fp)){
	    		sscanf(linebuffer,"%[^=>]=>%[^\n]",buffer1,buffer2);
	    		//printf("%s , %s\n\n",filename , buffer1);
	    		if(!strcmp(filename,buffer1)){
	    			printf("Now you can have the file %s to operate\n",filename);
	    			return 1;
	    		}
	    	}
	    	// Not found
	    	printf("Your search is not in disk : %s\n",diskname);
	    	return 0;
	} else {
	    // disk doesn't exist
	    printf("Can't find \"%s\" disk !\n",diskname);
	}
}

int myfs_file_close(int fd,const char *diskname){
	// Close the chosen current writing point
	if( access( diskname , F_OK ) != -1 ) {
		// disk exist
		int i;
		char *filename;
		for(i=0;i<128;i++){
			if(validFile[i].file_id == fd){
				// have the compare result
				// erase the valid file 
				validFile[i].file_id = -1;
				validFile[i].name = "";
				break;
			}
		}
	} else {
		// disk not exits
		printf("Can't find \"%s\" disk!\n",diskname);
	}
	return 1;
}

int myfs_file_create(const char *filename , const char *diskname){
	// Create a new file with the correct data structure and file attributes
	if( access( diskname , F_OK ) != -1 ) {
		// disk exist
		FILE *fp = fopen(diskname,"a");
		fprintf(fp,"%s=>default\n",filename);
		fclose(fp);
	} else {
		// file doesn't exist
		printf("Can't find \"%s\" disk!\n",diskname);
	}
	return 1;
}

int myfs_file_delete(const char *filename,const char *diskname){
	// Delete the chosen current file in data structure and file attributes
	if( access( diskname , F_OK ) != -1 ) {
		// disk exist
		char linebuffer[512] = {0};
		char buffer1[512] = {0};
		char buffer2[512] = {0};
		size_t line_len=0;
		int len = 0;
		int res;
		FILE *fp = fopen(diskname,"r+"); 
		if(fp == NULL){
			printf("open error");
			return -1;
		}
		while(fgets(linebuffer,512,fp)){
			line_len = strlen(linebuffer);
			len += line_len;
			sscanf(linebuffer,"%[^=>]%s",buffer1,buffer2);
			if(!strcmp(filename,buffer1)){
				len -= strlen(linebuffer);
				int buflen = strlen(buffer2) + strlen(buffer1);
				res = fseek(fp,len,SEEK_SET);
				if(res < 0){
					perror("fseek error");
					return -1;
				}
				strcpy(buffer2,"\0");
				strcpy(buffer1,"\0");
				int i;
				for(i = 0 ; i < buflen ; i++){
					strcat(buffer1," ");
				}
				fprintf(fp,"%s",buffer1);
				fclose(fp);
				return 1;
			}
		}
		// not found
		printf("Not found in %s disk\n",diskname);
	} else {
	    	// disk doesn't exist
	   	printf("Can't find \"%s\" disk!\n",diskname);
	}
	return 1;
}

int myfs_file_read(int fd , char *buf , int count){
	// read from the chosen file with limited-number of word
	int i;
	char *filename;
	for(i=0;i<128;i++){
		if(validFile[i].file_id == fd){
			//printf("Now you want to read is %s file\n",validFile[i].name);
			filename = validFile[i].name;
			break;
		}
	}
	// TODO : Read from this filename's buffer 
	
	return 1;
}

int myfs_file_write(int fd , char *buf , int count){
	// write in the chosen file with limited-number of word
}

/* make directory */
int myfs_mkdir(const char *dir_name , const char *diskname){
	
}

int myfs_rmdir(const char *dir_name , const char *diskname){

}
