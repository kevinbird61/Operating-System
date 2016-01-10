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
		fprintf(fd,"MAXIMAL_SIZE==%d\n",max_size);
		//fprintf(fd,"home:1\n");
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
	    	char start[16];
	    	int size;
	    	FILE *fp = fopen(diskname,"r+");
	    	if(fp == NULL){
	    		printf("open error");
	    		return -1;
	    	}
	    	while(fgets(linebuffer,512,fp)){
	    		sscanf(linebuffer,"%[^==]==%d\n",start,&size);
	    		//printf("start is %s ; size is %d\n",start,size);
	    		if(!strcmp(start,"MAXIMAL_SIZE")){
	    			current_disk_size = size;
	    			printf("Current disk size is %d\n",current_disk_size);
	    		}
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
	    return -1;
	}
	return -1;
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
		//fprintf(fp,"%s=>default\n",filename);
		char line[1024];
		char find[256];
		char buffer[1024];
		memset(find,'\0',256);
		memset(buffer,'\0',1024);
		while(fgets(line,1024,fp)){
			sscanf(line,"%[^\n]=>%[^\n]",find,buffer);
			if(!strcmp(filename,find)){
				// there exist the same file!
				printf("There have the same file!\n");
				fclose(fp);
				return 0;
			}
		}
		// Create one
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
		int res,filter = 0;
		FILE *fp = fopen(diskname,"r+"); 
		if(fp == NULL){
			printf("open error");
			return -1;
		}
		while(fgets(linebuffer,512,fp)){
			line_len = strlen(linebuffer);
			len += line_len;
			sscanf(linebuffer,"%[^=>]%[^\n]",buffer1,buffer2);
			if(!strcmp(filename,buffer1)){
				len -= strlen(linebuffer);
				int buflen = strlen(buffer2) + strlen(buffer1);
				res = fseek(fp,len,SEEK_SET);
				if(res < 0){
					perror("fseek error");
					return -1;
				}
				// size - strlen 
				current_disk_size += strlen(buffer2);
				if(current_disk_size > DISK_SIZE  ){
					filter = 2;
					fclose(fp);
					break;
				}
				// cover buffer2 , buffer1
				strcpy(buffer2,"\0");
				strcpy(buffer1,"\0");
				int i;
				for(i = 0 ; i < buflen ; i++){
					strcat(buffer1," ");
				}
				fprintf(fp,"%s",buffer1);
				fclose(fp);
				filter = 1;
				break;
			}
		}
		
		if(filter == 1){
		// found and store the size back to disk
			int size,i,res,len = 0;
			size_t line_len=0;
			char title[32],size_int[32];
			FILE *fp = fopen(diskname,"r+"); 
			if(fp == NULL){
			printf("open error");
			return -1;
			}
			while(fgets(linebuffer,512,fp)){
				line_len = strlen(linebuffer);
				len += line_len;
				sscanf(linebuffer,"%[^==]==%d\n",title,&size);
				//itoa( size , size_int , 10 );
				//printf("title is %s , size is %d\n",title,size);
				sprintf(size_int , "%d" ,size);
				//printf("title is %s , size is %s\n",title,size_int);
				if(!strcmp(title,"MAXIMAL_SIZE")){
					// prepare to replace the size
					len -= strlen(linebuffer);
					int buflen = strlen(size_int);
					sprintf(size_int , "%d" , current_disk_size);
					res = fseek(fp,len,SEEK_SET);
					if(res < 0){
					perror("fseek error");
					return -1;
					}
					if(current_disk_size < size){
						for(i = 0 ; i < buflen ; i++){
							strcat(size_int," ");
						}
					}
					strcat(title,"==");
					strcat(title,size_int);
					//printf("Store back is %s\n",title);
					fprintf(fp,"%s",title);
					fclose(fp);
					break;
				}
			}
		}
		else if(filter == 2){
		// size is bigger than before
			printf("Not enough space for file write! Write Error Occur!\n");
		}
		else{
		// not found
			printf("Not found in %s disk\n",diskname);
			fclose(fp);
		}
		
	} else {
	    	// disk doesn't exist
	   	printf("Can't find \"%s\" disk!\n",diskname);
	}
	return 1;
}

int myfs_file_read(int fd , char *buf , int count){
	// read from the chosen file with limited-number of word
	int i;
	char *filename,*diskname;
	for(i=0;i<128;i++){
		if(validFile[i].file_id == fd){
			//printf("Now you want to read is %s file\n",validFile[i].name);
			filename = validFile[i].name;
			diskname = validFile[i].disk;
			break;
		}
	}
	// Read from this filename's buffer 
	char linebuffer[512] = {0};
	char buffer1[512] = {0};
	char buffer2[512] = {0};
	int bufindex = 0;
	FILE *fp = fopen(diskname , "r+");
	if(fp == NULL){
		printf("Open disk in read file error\n");
		return -1;
	}
	while(fgets(linebuffer,512,fp)){
		sscanf(linebuffer , "%[^=>]=>%[^\n]\n",buffer1,buffer2);
		if(!strcmp(filename , buffer1)){
			break;
		}
	}
	buf = buffer2;
	// parse the buffer2
	printf("Count is %d\n",count);
	while(buffer2[bufindex] && (bufindex < count)){
		if(buffer2[bufindex] == FILE_NL_CHAR){
			printf("\n");
		}
		else{
			printf("%c",buffer2[bufindex]);
		}
		bufindex++;
	}
	printf("\n");
	return 1;
}

int myfs_file_write(int fd , char *buf , int count){
	// write in the chosen file with limited-number of word
	int i;
	char *filename,*diskname;
	for(i=0;i<128;i++){
		if(validFile[i].file_id == fd){
			filename = validFile[i].name;
			diskname = validFile[i].disk;
			break;
		}
	}
	// TODO : Write into this filename from the outside buffer
	printf("All you can type in here : (Press \":wq\" + Enter to leave)\n");
	char totalbuf[1024];
	char writebuf[1024];
	int bufindex = 0;
	memset(totalbuf,'\0',1024);
	memset(writebuf,'\0',1024);
	while(1){
		char temp;
		temp = getchar();
		if(temp == 10){
			// TODO : leave
			if(!strcmp(writebuf,":wq")){
				printf("End of Input , prepare to store into \"%s\" file\n",filename);
				break;
			}
			else{
				printf("For a line write : %s , prepare to store in buffer\n",writebuf);
				strcat(totalbuf,writebuf);
				strcat(totalbuf,FILE_NL_STR); // For next line replace character => for read
				// clear buf
				memset(writebuf,'\0',1024);
				bufindex = 0;
			}
		}
		else if( temp == 8){
			// Backspace = 8
			bufindex--;
			writebuf[bufindex] = 0;
		}	
		else{
			// write in buffer
			writebuf[bufindex] = temp;
			bufindex++;
		}
	}
	//printf("Total buffer is %s\n" , totalbuf);
	// Prepare to store in file
	char linebuffer[512] = {0};
	char buffer1[512] = {0};
	char buffer2[512] = {0};
	int line_len = 0;
	int len = 0;
	int res;
	// Open file (disk) to write
	FILE *fp = fopen(diskname,"r+");
	if(fp == NULL){
		printf("Open disk in write error");
		return -1;
	}
	while(fgets(linebuffer , 512 , fp)){
		line_len = strlen(linebuffer);
		len += line_len;
		sscanf(linebuffer,"%[^\n]=>%[^\n]\n",buffer1,buffer2);
		printf("buffer1 in file write is %s , buffer2 is %s\n",buffer1,buffer2);
		if(!strcmp(filename,buffer1)){
			// compare is get
			len -= strlen(linebuffer);
			int buflen = strlen(buffer2);
			// check whether it has the rest space
			current_disk_size += buflen;
			int writelen = strlen(totalbuf);
			current_disk_size -= writelen;
			if(current_disk_size < 0){
				printf("There hasn't the extra space to store your file!\n");
				break;
			}
			res = fseek(fp , len , SEEK_SET);
			if(res < 0 ){
				perror("fseek in write file error");
				return -1;
			}
			// and then copy the data from totalbuf to buffer2
			memset(buffer2 , '\0' , 512); // clear the buffer2
			strcpy(buffer2 , totalbuf);
			int total = (int)strlen(totalbuf);
			//printf("Totalbuf strlen : %d ; buflen : %d\n",total,buflen);
			if(total< buflen){
			// use blank to eliminate dead character
				int i;
				for(i=0;i<buflen;i++){
					strcat(buffer2, " ");
				}
			}
			//printf("Buffer2 now is %s\n",buffer2);
			strcat(buffer1, "=>"); // for sign
			strcat(buffer1,buffer2);
			//printf("The write back now is %s\n",buffer2);
			// Write back to file (disk)
			fprintf(fp,"%s",buffer1);
			fclose(fp);
			//return 1;
		}
	}
	// Store back the size of disk
	// found and store the size back to disk
	int size;
	len = 0;
	line_len=0;
	char title[32],size_int[32];
	FILE *fs = fopen(diskname,"r+"); 
	if(fs == NULL){
		printf("open error");
		return -1;
	}
	while(fgets(linebuffer,512,fs)){
		line_len = strlen(linebuffer);
		len += line_len;
		sscanf(linebuffer,"%[^==]==%d\n",title,&size);
		sprintf(size_int , "%d" ,size);
		//printf("title is %s , size is %s\n",title,size_int);
		if(!strcmp(title,"MAXIMAL_SIZE")){
			// prepare to replace the size
			len -= strlen(linebuffer);
			int buflen = strlen(size_int);
			printf("Past size is %s\n",size_int);
			sprintf(size_int , "%d" , current_disk_size);
			printf("Current size is %s\n",size_int);
			res = fseek(fs,len,SEEK_SET);
			if(res < 0){
				perror("fseek error");
				return -1;
			}
			if(current_disk_size < size){
				for(i = 0 ; i < buflen ; i++){
				strcat(size_int," ");
				}
			}
			strcat(title,"==");
			strcat(title,size_int);
			printf("Store back is %s\n",title);
			fprintf(fs,"%s",title);
			fclose(fs);
			break;
		}
	}
	return 1;
}

/* make directory */
int myfs_mkdir(const char *dir_name , const char *diskname){
	
}

int myfs_rmdir(const char *dir_name , const char *diskname){

}
