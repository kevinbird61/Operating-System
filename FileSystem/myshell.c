#include "myshell.h"

void fetch_command(){
	char *line;
	int status = 1;
	do{
		printf("kevin@mini-shell:~$ ");
		// fetch user input
		line = command_read();
		//printf("%s\n",line);
		status = command_execute(line);
		//
	}while(status);	
}

char *command_read(){
	int bufsize = READBUF;
	int position = 0;
	char *buffer = malloc(bufsize*sizeof(char));
	char c;
	/* if buffer create fail */
	if(!buffer){
		fprintf(stderr , "cmd read : buffer malloc error\n");
	}
	
	while(1){
		// read a character
		c = getchar();
		// judge to keep or stop
		if(c==EOF || c=='\n'){
			buffer[position] = '\0';
			//return result
			return buffer;
		}
		else{
			buffer[position] = c;
		}
		position++;
		
		// FIXME : if buffer size is not enought
	}
}

int command_execute(char *cmd){
	/* Judge the first character */	
	if(cmd[0] == 'h'){
	/* If command is help */ 
		if(cmd[1] == 'e' && cmd[2] == 'l' && cmd [3] == 'p' && cmd[4] == '\0'){
			printf("Thanks for using help command\n");
			printf("Here comes some useful tips:\n");
			printf("\t\"disk_create disk_name size\" - create disk\n");
			printf("\t\"disk_destroy disk_name\" - destroy the disk\n");
			printf("\t\"file_open file_name diskname\" - open a exist file\n");
			printf("\t\"file_close file_name diskname\" - close a exist file\n");
			printf("\t\"file_create filename diskname\" - create a file\n");
			printf("\t\"file_delete filename diskname\" - delete a file\n");
			printf("\t\"file_read filename diskname\" - read from a file\n");
			printf("\t\"file_write filename diskname\" - write from a file\n");
			printf("\t\"exit\" - to leave mini-shell\n");
			printf("Hope its useful for you!!\n\n");
			return 1;
		}
		else{
			printf("%s , is not in our command list !!\n",cmd);
			return 1;
		}
	}
	else if(cmd[0] == 'e'){
	/* if command is exit */
		if(cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't'){
			printf("Goodbye!\n");
			return 0;
		}
		else{
			printf("%s , is not in our command list !!\n",cmd);
			return 1;
		}
	}
	else if(cmd[0] == 'd'){
	/* if command is operating with disk*/
		if(cmd[1] == 'i' && cmd[2] == 's' && cmd[3] == 'k' && cmd[4] == '_'){
		/* enter "disk_" */
			if(cmd[5] == 'c' && cmd[6] == 'r' && cmd[7] == 'e' && cmd[8] == 'a' && cmd[9] == 't' && cmd[10] == 'e' ){
			/* enter "disk_create"*/
				// fetch the disk name and size
				char diskname[64];
				memset(diskname , '\0' , 64);
				int max_size = -1;
				if(cmd[12] != '\0'){
					// read for the disk name and size
					sscanf(cmd,"%s %s %d",diskname,diskname,&max_size);
					if(max_size == -1){
						printf("Your disk name : %s ; But your haven't input the size !\n",diskname);
						return 1;
					}
					else{
						printf("Your input : %s ; size is %d\n", diskname , max_size);
					}
				}
				else{
					// Type error
					printf("You must input diskname and max size => use \"help\" to check more!!\n");
					return 1;
				}
				// TODO Create the disk => use "myfile.c"
				myfs_create(diskname , max_size);
				
				return 1;
			}
			else if(cmd[5] == 'd' && cmd[6] == 'e' && cmd[7] == 's' && cmd[8] == 't' && cmd[9] == 'r' && cmd[10] == 'o' && cmd[11] == 'y' ){
			/* enter "disk_destroy" */
				// fetch the disk name
				char comd[64],diskname[64];
				memset(diskname , '\0' , 64);
				memset(comd,'\0',64);
				if(cmd[13] != '\0'){
					// read for the disk name and size
					sscanf(cmd,"%s %s",comd,diskname);
					//printf("%s , %s , %s \n",cmd ,comd ,diskname);
					if(diskname[0] == '\0'){
						printf("Your haven't input the disk name you want to delete !\n");
						return 1;
					}
					else{
						printf("The disk you want to delete : %s \n", diskname);
					}
				}
				else{
					// Type error
					printf("You must input diskname => use \"help\" to check more!!\n");
					return 1;
				}
				// TODO destroy the disk (file) => find if it is exist or not
				myfs_destroy(diskname);
								
				return 1;
			}
			else{
			/* exception */
				 printf("%s , is not fit with disk operation!!\nPlease try :\n\"disk_create diskname size\"\n\"disk_destroy diskname\"\n",cmd);
			}
		}
		else{
			printf("%s , is not fit with disk operation!!\nPlease try :\n\"disk_create diskname size\"\n\"disk_destroy diskname\"\n",cmd);
		}	
	}
	else if(cmd[0] == 'f'){
	/* if command is dealing with file */
		if(cmd[1] == 'i' && cmd[2] == 'l' && cmd[3] == 'e' && cmd[4] == '_' ){
		/* enter "file_"*/
			if(cmd[5] == 'o' && cmd[6] == 'p' && cmd[7] == 'e' && cmd[8] == 'n' ){
			/* enter "file_open" */
				// fetch file and current diskname 
				char comd[64], diskname[64] , filename[64];
				if(cmd[10] != '\0'){
				// read for the disk name and filename
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
						return 1;
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
						return 1;
					}
					else{
						printf("The file you want to open : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
					return 1;
				}
				// do the operation
				int i,filter;
				filter = myfs_file_open(filename,diskname);
				if(filter){
					/* store in validFile */
					for(i = 0; i < 128 ; i++){
						if(validFile[i].file_id == -1){
							validFile[i].file_id = i;
							validFile[i].name = filename;
							printf("Now open file : %s => Fild id is %d \n",validFile[i].name,validFile[i].file_id);
							break;
						}
					}
				}
				else{
					/* not found */
				}
				return 1;
			}
			else if(cmd[5] == 'c' && cmd[6] == 'l' && cmd[7] == 'o' && cmd[8] == 's' && cmd[9] == 'e' ){
			/* enter "file_close" */
				// fetch file and current diskname 
				char comd[64], diskname[64] , filename[64];
				if(cmd[11] != '\0'){
				// read for the disk name and filename
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
						return 1;
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
						return 1;
					}
					else{
						printf("The file you want to close : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
					return 1;
				}
				// do the operation
				// search the validFile
				int i,close_id,filter = 0;
				for(i=0;i<128;i++){
					if(!strcmp(filename,validFile[i].name)){
						// have the compare result
						close_id = validFile[i].file_id;
						printf("Now closed file : %s => Fild id is %d has already closed\n",validFile[i].name,validFile[i].file_id);
						filter = 1;
						break;
					}
				}
				if(filter){
					myfs_file_close(close_id,diskname);
				}
				else{
					printf("Sorry , not found this active file handler !\n");
				}
				return 1;
			}
			else if(cmd[5] == 'c' && cmd[6] == 'r' && cmd[7] == 'e' && cmd[8] == 'a' && cmd[9] == 't' && cmd[10] == 'e'){
			/* enter "file_create" */
				// fetch file and current diskname 
				char comd[64], diskname[64] , filename[64];
				if(cmd[12] != '\0'){
				// read for the disk name and filename
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
						return 1;
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
						return 1;
					}
					else{
						printf("The file you want to create : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
					return 1;
				}
				// do the  create operation
				
				
				return 1;	
			}
			else if(cmd[5] == 'd' && cmd[6] == 'e' && cmd[7] == 'l' && cmd[8] == 'e' && cmd[9] == 't' && cmd[10] == 'e' ){
			/* enter "file_delete" */
				// fetch file and current diskname 
				if(cmd[12] != '\0'){
				// read for the disk name and filename
					char comd[64], diskname[64] , filename[64];
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
					}
					else{
						printf("The file you want to delete : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
				}
				// do the  delete operation
				
				return 1;
			}
			else if(cmd[5] == 'r' && cmd[6] == 'e' && cmd[7] == 'a' && cmd[8] == 'd'){
			/* enter "file_read" */
				// fetch file and current diskname 
				if(cmd[10] != '\0'){
				// read for the disk name and filename
					char comd[64], diskname[64] , filename[64];
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
					}
					else{
						printf("The file you want to read : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
				}
				// do the  read operation
				
				return 1;
			}
			else if(cmd[5] == 'w' && cmd[6] == 'r' && cmd[7] == 'i' && cmd[8] == 't' && cmd[9] == 'e'){
			/* enter "file_write" */
				// fetch file and current diskname 
				if(cmd[11] != '\0'){
				// read for the disk name and filename
					char comd[64], diskname[64] , filename[64];
					memset(comd , '\0' , 64);
					memset(diskname , '\0' , 64);
					memset(filename , '\0' , 64);
					sscanf(cmd,"%s %s %s",comd,diskname,filename);
					if(diskname[0] == '\0'){
						printf("You don't have input the diskname!\n");
					}
					else if(filename[0] == '\0'){
						printf("You don't have input the filename!\n");
					}
					else{
						printf("The file you want to write : %s , which is in disk : %s\n",filename,diskname);
					}
				}
				else{
					printf("You have to input diskname and filename ! \nPlease use \"help\" to check it ! \n");	
				}
				// do the  write operation
				
				return 1;
			}
			else{
			/* exception */
				printf("%s , is not fit with file operation!!\nPlease check with command \"help\"\n",cmd);
			}
			return 1;
		}
		else{
			printf("%s , is not fit with file operation!!\nPlease check with command \"help\"\n",cmd);
		}
	}
	else if(cmd[0] == 'l'){
		if(cmd[1] == 's'){
			// do 'ls' command
			DIR *d;
			struct dirent *dir;
			d = opendir(".");
			if(d){
				printf("The current directory's file : \n");
				while((dir = readdir(d))!=NULL){
					// read if directory is not empty
					if (dir->d_type == DT_REG){
						// check if it isn't sys file
						printf("%s ", dir -> d_name);
					}	
				}
				printf("\n");
				closedir(d);
			}
		}
	}
	else{
	/* If command is fit with nothing */
		 printf("%s , is not in our command list !!\n",cmd);
	}	
	return 1;
}
