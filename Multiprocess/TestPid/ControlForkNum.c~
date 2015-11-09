#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc , char *argv[]){
	int i,control;
	pid_t pid;
	control = atoi(argv[1]);
	printf("input comm is %d\n\n",control);
	if(control != 1){
		/* Create the need amount of threads */
		pid = fork();
		for(i=1;i<control-1;i++)
		{
			if(pid==0){
				pid = fork();
			}
		}
		/* Do the threads jobs */
		if(pid>0){
			printf("This is iterative parent pid : %d\n",pid);
		}
		else{
			printf("This is iterative child pid %d\n",pid);
		}
	}
	else{
		printf("Only one Thread!\n");
		/*TODO do one thread things*/
	}
	wait(NULL);
	return 0;
}
