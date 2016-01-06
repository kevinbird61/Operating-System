#include "myshell.h"

int main(int argc , char *argv[]){
	printf("Welcome to use Kevin - mini shell!\n");
	printf("Type in \"help\" to learn more , Type in \"exit\" to exit mini shell \n\n");
	// Initialize the valid file table
	int i;
	memset(current_disk,'\0',sizeof(current_disk));
	strcpy(current_disk,"NULL");
	for(i=0;i<128;i++){
		validFile[i].file_id = -1;
		validFile[i].name = "";
		validFile[i].disk = "";
	}
	// implement the mini shell , to ask user to do the operation
	fetch_command();
	return 0;
}
