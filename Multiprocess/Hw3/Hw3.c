#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
/* For shared memory API */
#include <sys/shm.h>
#include <sys/ipc.h>
/* Define the filename */
#include "fetchString.h"
#define RESULT_SIZE 1024 
#define SHM_KEY 1208

int main(int argc , char *argv[]){
//===============================================================
	/* For Test strings file 　*/
	/* FIXME : Get the input file length and file content */
	char Test[30] = "KevinChuChuisgood"; // file source
	int length = 30,control; // source file length
	/* Get the number of processor by user */
	/* TODO : the searching strings - user want to find 
		argv[1] => input filename
		argv[2] => search string
		argv[3] => process number	
	*/
	control = atoi(argv[1]);

	/* For local variables */
	int i;
	int startSearch=0 , searchLength = (int)(length/control);
	char search[16];
	pid_t pid;
	/* Build the needed shared memory data */	
	int shmid;			// shared tag
	char *shmaddr;		// shared memory address - types
	struct shmid_ds buf;// structure for control shared data
	int flag = 0;		// for 'shmctl' flag control
	
//===============================================================	
	printf("input comm is %d\n\n",control);
	
	/*TODO Build the shm area
		The shared memory is used to store the string result
		Using strcpy , strcat
	*/
	shmid = shmget(IPC_PRIVATE , RESULT_SIZE , IPC_CREAT|0600);
	printf("The %d Pid - shmid is %d \n",pid , shmid);
	if(control != 1){
		/*===================== Create the need amount of threads ======================*/
		pid = fork();
		for(i=1;i<control-1;i++)
		{
			if(pid==0){
				pid = fork();
				startSearch += (int)(length/control);
				searchLength = (int)(length/control);
			}
		}
		if(pid==0){
			// For pid = 0's range
			startSearch += (int)(length/control);
			searchLength = (int)(length/control) + (int)(length%control);
		}
		//===================== Create the need amount of threads - end  ======================// 
		/* For processor >0 , Do the threads jobs */
		if(pid>0){
			printf("This is iterative parent pid : %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
			/*TODO shm*/
			
		}
		else{
			// Processor 0
			printf("This is iterative child pid %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
			/*TODO shm and print the result of find*/
		}
	}
	else{
		printf("Only one Thread!\n");
		/*TODO do one thread things*/
	}
	wait(NULL);
	return 0;
}
