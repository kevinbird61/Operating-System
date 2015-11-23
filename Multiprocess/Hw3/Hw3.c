#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
/* For shared memory API */
#include <sys/shm.h>
#include <sys/ipc.h>
/* Define the filename */
#define RESULT_SIZE 1024 

int main(int argc , char *argv[]){
//===============================================================
	/* For Test strings file 　*/
	/* FIXME : Get the input file length and file content */
	char Test[30] = "KevinChuChuisgood"; // file source
	int length = 30; // source file length
	
	/* For local variables */
	int i,control;
	int startSearch=0 , searchLength = (int)(length/control);
	char search[16];
	pid_t pid;
	
	/* Build the needed shared memory data */
	int shmid;			// shared tag
	char *shmaddr;		// shared memory address - types
	struct shmid_ds buf;// structure for control shared data
	int flag = 0;		// for 'shmctl' flag control
	
	/* Get the number of processor by user */
	/* TODO : the searching strings - user want to find */
	control = atoi(argv[1]);
//===============================================================	
	printf("input comm is %d\n\n",control);
	
	/*TODO Build the shm area
		The shared memory is used to store the string result
		Using strcpy , strcat
	*/
	shmid = shmget(IPC_PRIVATE , RESULT_SIZE , IPC_CREAT|0600);
	
	if(control != 1){
		/* Create the need amount of threads */
		pid = fork();
		for(i=1;i<control-1;i++)
		{
			if(pid==0){
				pid = fork();
				startSearch += (int)(length/control);
				searchLength = (int)(length/control);
			}
		}
		/* for processor = 0 */
		if(pid==0){
			startSearch += (int)(length/control);
			searchLength = (int)(length/control) + (int)(length%control);
			/*TODO attaching the shm to need */
			shmaddr = (char*)shmat(shmid , NULL , 0);
			if((int)shmaddr == -1){
				perror("shmat addr error");
				return -1;
			}
			strcpy(shmaddr , "Processor 0 is in!\n");
			shmdt(shmaddr);
		}
		/* For processor >0 , Do the threads jobs */
		if(pid>0){
			//printf("This is iterative parent pid : %d\n",pid);
			//printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
			/*TODO shared memory control*/
			flag = shmctl(shmid , IPC_STAT , &buf);
			if(flag==-1){
				perror("shmctl shm error");
				return -1;
			}
			shmaddr = (char*)shmat(shmid , NULL , 0);
			if((int)shmaddr == -1){
				perror("shmat addr error");
				return -1;
			}
			strcat(shmaddr , "Processor parent is in!\n");
			printf("%s",shmaddr);
			shmdt(shmaddr);
			shmctl(shmid , IPC_RMID , NULL);
		}
		else{
			printf("This is iterative child pid %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
		}
	}
	else{
		printf("Only one Thread!\n");
		/*TODO do one thread things*/
	}
	wait(NULL);
	return 0;
}
