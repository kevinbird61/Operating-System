#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc , char *argv[])
{
	int iteration = 1;
	pid_t pid,getid;
	
	pid = fork();
	pid = fork();
	
	
	if(pid>0){
		printf("This is %d and iteration is %d\n",pid,iteration);
		getid = getpid();
		printf("This is %d and getpid is %d\n",pid,getid);
	}
	else{
		printf("This is %d and iteration is %d\n",pid,iteration);
		getid = getpid();
		printf("This is %d and getpid is %d\n",pid,getid);
	}
	return 0;
}
