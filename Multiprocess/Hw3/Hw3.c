#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/* Define the filename */

int main(int argc , char *argv[]){
	/* For Test strings file 　*/
	/* FIXME : Get the input file length and file content */
	char Test[30] = "KevinChuChuisgood";
	int length = 30;
	/* For local variables */
	int i,control;
	int startSearch=0 , searchLength = (int)(length/control);
	char search[16];
	pid_t pid;
	/* Get the number of processor by user */
	/* TODO : the searching strings - user want to find */
	control = atoi(argv[1]);
	
	printf("input comm is %d\n\n",control);
	
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
		}
		/* Do the threads jobs */
		if(pid>0){
			printf("This is iterative parent pid : %d\n",pid);
			printf("Pid %d searching data's startIndex %d and Length is %d \n\n",pid,startSearch,searchLength);
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
