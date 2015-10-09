#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int strcicmp(char const *str1,char const *str2){
	int length = strlen(str1),count=0;
	for(;count!=length;str1++,str2++){
		int d = tolower(*str1) - tolower(*str2);
		if(d!=0 || !*str1){
			return 1;
		}
	count++;
	}
	return 0;
}
// For Create File
int Create(char *str){
	strcat(str,".txt");
	FILE *fp = fopen(str,"w");
	fprintf(fp,"\0");
	fclose(fp);
}

// For Editor File
int Edit(){

}

int socket_server(int port)
{
    int listenfd = 0, connfd = 0 , flags = 0;
    struct sockaddr_in serv_addr; 
    char buffer[1024];
//==============================create socket===================================//
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 
//==============================bind socket===================================//
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
//==============================wait for accept===================================//
    listen(listenfd, 10); 
//==============================get accept===================================//
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
//==============================start communication===================================//
printf("成功開啟Server 等待client端的連線\n");
	while(1){
	    	memset(buffer, '0', sizeof(buffer)); 
		// First , connection accept  => deliver the message first)	    
		strcpy(buffer, "Welcome to Kevin's server , May I help u sir?\n=============================================\nC] 輸入檔名，在server端建立一空的檔案\nE] 輸入欲編輯檔名，在server端確定檔案存在後，便可開始輸入文字進入檔案中\nR] 輸入欲刪除的檔名，在server端的檔案刪除\nL] 顯示server端所有檔案名稱\nD] 輸入指定檔名，並從server端下載此檔案至client端資料夾\n");		
		if(flags == 0){
			if (write(connfd, buffer, strlen(buffer)) < 0)
			{
				printf("\n Error : Write Failed \n");
				return 1;
			} 
		}
		memset(buffer, '\0', sizeof(buffer));     

		if (read(connfd, buffer, sizeof(buffer)) < 0)
	    	{
			printf("\n Error : Read Failed \n");
			return 1;
	   	} 
		
		switch(){
			case 0:
				printf("The client says : [%s]\n", buffer);
				break;
			case 1:
				printf("Get the filename: %s\n", buffer);
				Create(buffer);
				flags = 0;
				break;
			case 2:
				printf("Get the filename: %s\n", buffer);
				Edit(buffer);
				flags = 0;
				break;
		}
		//write(connfd, buffer, strlen(buffer));
		// Judge which instruction should operate
		if(!strcicmp(buffer,"End")){ 
			write(connfd, buffer, strlen(buffer));		
			break;
		}
		if(!strcicmp(buffer,"C")){
			char file[30];
			memset(file, '\0', sizeof(file)); 
			strcpy(file,"Please Input the filename\n");
			write(connfd, file, strlen(file));
			memset(file, '\0', sizeof(file));
			flags = 1;
		}
		if(!strcicmp(buffer,"E")){
			char file[30];
			memset(file, '\0', sizeof(file)); 
			strcpy(file,"Please Input the filename you want to edit\n");
			write(connfd, file, strlen(file));
			memset(file, '\0', sizeof(file));
			flags = 2;
		}
		// =====================End=====================
	}
    close(connfd);

    return 0;
}

int main(int argc, char *argv[])
{

    socket_server(5000); // 用來接收來自client的控制訊息

    return 0;
}
