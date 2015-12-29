#include "myshell.h"

void fetch_command(){
	char *line;
	int status = 1;
	do{
		printf("kevin@mini-shell:~$");
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
		if(cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't'){
			printf("Goodbye!\n");
			return 0;
		}
		else{
			printf("%s , is not in our command list !!\n",cmd);
			return 1;
		}
	}
	
	return 1;
}
