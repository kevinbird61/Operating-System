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
#define SHM_KEY 1

int main(int argc , char *argv[]){
//===============================================================
	/* For Test strings file 　*/
	/* FIXME : Get the input file length and file content */
	char *filename , *searchString , *source; // file source
	int length,control,cmplen; // source file length
	/* Get the number of processor by user */
	/* TODO : the searching strings - user want to find 
		argv[1] => input filename
		argv[2] => search string
		argv[3] => process number	
	*/
	filename = argv[1];
	searchString = argv[2];
	control = atoi(argv[3]);
	/* Get the source */
	length = lengthof(filename);
	source = malloc(length * sizeof(char));
	source = contentof(filename,length);
	cmplen = strlen(searchString);
	//printf("File : %s ; and searchString : %s; And Length is %d \n" ,filename,searchString , length );
	/* For local variables */
	int i,re_val;
	char result[64];
	int startSearch=0 , searchLength = (int)(length/control);
	pid_t pid;
	/* Build the needed shared memory data */	
	int shmid , shmid_val;			// shared tag
	char *shmaddr,*shmval_addr;		// shared memory address - types
	struct shmid_ds buf;// structure for control shared data
	int flag = 0;		// for 'shmctl' flag control
	
//===============================================================	
	printf("input comm is %d\n\n",control);
	/*TODO Build the shm area
		The shared memory is used to store the string result
		Using strcpy , strcat
	*/
	//shmid = shmget(IPC_PRIVATE , RESULT_SIZE , IPC_CREAT|0666);
	shmid = shmget(SHM_KEY, RESULT_SIZE , IPC_CREAT|0666);
	shmid_val = shmget(SHM_KEY + 1 , 1 , IPC_CREAT|0666);
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
		//===================== Using the thread to calculate- start  ======================// 
		/* For processor >0 , Do the threads jobs */
		printf("The %d Pid - shmid is %d \n",pid , shmid);
		shmaddr = (char*) shmat(shmid , NULL , 0); 
		printf("The %d Pid - shmaddr is  %s \n",pid , shmaddr);
		shmval_addr = (char*)shmat(shmid_val , NULL , 0);
		if(pid>0){
			printf("This is iterative parent pid : %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
			/* Do the compare! */
			if(startSearch != 0){
				startSearch -= (cmplen - 1); // to have the buffer of one compare string
				searchLength += (cmplen - 1);
			 	re_val = fetch_specify_str(searchString , source , cmplen , startSearch , startSearch+searchLength );
			 	sprintf(result , "Process %d : %d\t",pid,re_val);
			 	/*TODO shm*/
				strcat(shmaddr , result);	
				*shmval_addr += re_val;
			}
			else{
			// start with 0 , do usual fetch_spec_str
				re_val = fetch_specify_str(searchString , source , cmplen , startSearch , startSearch+searchLength );
			 	sprintf(result , "Process %d : %d\t",pid,re_val);
			 	/*TODO shm*/
				strcat(shmaddr , result);	
				*shmval_addr += re_val;
			}
		}
		else{
			// Processor 0
			printf("This is iterative child pid %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
			startSearch -= (cmplen - 1); // to have the buffer of one compare string
			searchLength += (cmplen - 1);
			 re_val = fetch_specify_str(searchString , source , cmplen , startSearch , startSearch+searchLength );
			 sprintf(result , "Process %d : %d\t",pid,re_val);
			/*TODO shm and print the result of find*/
			strcat(shmaddr , result);		
			*shmval_addr += re_val;
		}
		wait(NULL);
		if(pid == 0){
			printf("The result  is \n%s \n",shmaddr);
			printf("The Total result is %d \n",*shmval_addr);
		}
		shmdt(shmaddr);
		shmdt(shmval_addr);
	}
	else{
		printf("Only one Thread!\n");
		/*TODO do one thread things*/
	}
	shmctl(shmid , IPC_RMID , NULL);
	shmctl(shmid_val , IPC_RMID , NULL);
	//wait(NULL);
	return 0;
}
