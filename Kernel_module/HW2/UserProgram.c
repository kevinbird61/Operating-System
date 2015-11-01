/* For reading /proc/hw2_proc message */
#include <stdio.h>
#include <error.h>

int main(){
	FILE *fp;
	char buf[1024];
	// For reading file 
	fp = fopen("/proc/hw2_proc","r");
	if(fp==NULL){
		perror("fopen");
		return -1;
	}
	printf("The message store in /proc/hw2_proc :\n==========================\n");
	while(!feof(fp)){
		if(fgets(buf,sizeof(buf),fp)!=NULL)
			printf("%s",buf);
	}
	fclose(fp);
	
	return 0;
}


