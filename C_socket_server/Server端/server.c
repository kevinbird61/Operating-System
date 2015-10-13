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
#include <ctype.h>
#include <dirent.h>

int strcicmp(char const *str1,char const *str2){
	int length = strlen(str1),check = strlen(str2),count=0;
	for(;count!=length;str1++,str2++){
		int d = tolower(*str1) - tolower(*str2);
		if(d!=0 || !*str1){
			return 1;
		}
	count++;
	}
	if(count!=check){return 1;}
	return 0;
}
// For Create File
void Create(char *str){
	strcat(str,".txt");
	FILE *fp = fopen(str,"w");
	fclose(fp);
}

// For Remove File
void Remove(char fname[]){
	remove(fname);
}

void imple_LS(int connfd){
        struct dirent *pDirent;
        DIR *pDir;
        char result[128];
        memset(result,'\0',sizeof(result));
        char *str = "/home/kevin/桌面/OS/Operating-System/C_socket_server/Server端";
       
        pDir = opendir (str);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", str);
        }

        while ((pDirent = readdir(pDir)) != NULL) {
           	memset(result,'\0',sizeof(result));
           	strcpy(result,pDirent->d_name);
           	write(connfd,result,sizeof(result));
            printf ("[%s]\n", pDirent->d_name);
            read(connfd,result,sizeof(result));
            //printf("%s\n",result);
        }
        memset(result,'\0',sizeof(result));
        strcpy(result,"OK!STOPLS");
        write(connfd,result,sizeof(result));
        printf ("Out of Dir\n");
        closedir (pDir);
}

void downLoad(char dFile[]){
	char *cp = "/home/kevin/桌面/OS/Operating-System/C_socket_server/Client端/";
	char *sp = "/home/kevin/桌面/OS/Operating-System/C_socket_server/Server端/";
	char *clientPath = (char*)malloc(strlen(cp)+strlen(dFile));
	char *serverPath = (char*)malloc(strlen(sp)+strlen(dFile));

	strcat(clientPath,cp);
	strcat(clientPath,dFile);
	strcat(serverPath,sp);
	strcat(serverPath,dFile);
	char c;
	printf("clientPath :%s\n",clientPath);
	printf("serverPath :%s\n",serverPath);
	FILE *fsource = fopen(serverPath,"r");
	if(fsource==NULL){
		// Print Back to Client!!
		printf("Download Not Found!!\n");
	} 
	else{
		// Have Found
		FILE *fdest = fopen(clientPath,"w+");
		while(!feof(fsource)){
			fscanf(fsource,"%c",&c);
			fprintf(fdest,"%c",c);
		}
		printf("File is fully DownLoad\n");
		fclose(fdest);
	}
	free(clientPath);
	free(serverPath);
	fclose(fsource);
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
		strcpy(buffer, "\nWelcome to Kevin's server , May I help u sir?\n=============================================\nC] 輸入檔名，在server端建立一空的檔案\nE] 輸入欲編輯檔名，在server端確定檔案存在後，便可開始輸入文字進入檔案中\t輸入StopIn來結束輸入\nR] 輸入欲刪除的檔名，在server端的檔案刪除(記得輸入副檔名)\nL] 顯示server端所有檔案名稱\nD] 輸入指定檔名，並從server端下載此檔案至client端資料夾\n");		
		if(flags == 0){
			if (write(connfd, buffer, strlen(buffer)) < 0)
			{
				printf("\n Error : Write Failed \n");
				return 1;
			} 
			//int len = strlen(buffer);
			//buffer[len] = '\0';
		}
		memset(buffer, '\0', sizeof(buffer));     

		if (read(connfd, buffer, sizeof(buffer)) < 0)
	    {	
			printf("\n Error : Read Failed \n");
			return 1;
	   	} 
		
		switch(flags){
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
				strcat(buffer,".txt");
				FILE *fp = fopen(buffer,"w");
				if(!fp){
					printf("File Not Found\n");
					memset(buffer, '\0', sizeof(buffer)); 
					strcpy(buffer,"File Not Found\n");
					write(connfd, buffer, strlen(buffer));
				}
				else{
				char str[100];
				int start=0;
				memset(str, '\0', sizeof(str)); 
				strcpy(str,"Please input the content you want to edit in this file\n");
				write(connfd, str, strlen(str));
					while(1){	
						if(!strcicmp(str,"StopIn")){
							memset(str, '\0', sizeof(str)); 
							strcpy(str,"OK!Stop~");
							write(connfd, str, sizeof(str));
							break;
						}
						else{
							if(start!=0){
							fprintf(fp,"%s\n",str);
							}
							write(connfd, str, sizeof(str));
							memset(str, '\0', sizeof(str)); 
						}
						memset(str, '\0', sizeof(str)); 
						read(connfd, str, sizeof(str));
						printf("Client server input: %s\n",str); 
						start++;
					}
					//printf("Result : %s\n",result);
				//Edit(buffer,result);
				}
				fclose(fp);
				flags = 0;
				break;
			case 3:
				printf("Get the filename: %s\n",buffer);
				Remove(buffer);
				flags = 0;
				break;
		}
		//write(connfd, buffer, strlen(buffer));
		// Judge which instruction should operate
		if(!strcicmp(buffer,"End")){ 
			printf("It's end!!\n");
			write(connfd, buffer, sizeof(buffer));
			break;
		}
		else if(!strcicmp(buffer,"E")){
			char file[100];
			memset(file, '\0', sizeof(file)); 
			strcpy(file,"Please Input the filename you want to edit\n");
			write(connfd, file, sizeof(file));
			memset(file, '\0', sizeof(file));
			flags = 2;
		}
		else if(!strcicmp(buffer,"C")){
			char file[30];
			memset(file, '\0', sizeof(file)); 
			strcpy(file,"Please Input the filename\n");
			write(connfd, file, sizeof(file));
			memset(file, '\0', sizeof(file));
			flags = 1;
		}
		else if(!strcicmp(buffer,"R")){
			char file[30];
			memset(file, '\0', sizeof(file)); 
			strcpy(file,"Please Input the filename you want to delete\n");
			write(connfd, file, sizeof(file));
			memset(file, '\0', sizeof(file));
			flags = 3;
		}
		else if(!strcicmp(buffer,"L")){
			memset(buffer, '\0', sizeof(buffer)); 
			strcpy(buffer,"Show");
			write(connfd, buffer, sizeof(buffer));
			//read(connfd, buffer, strlen(buffer));
			imple_LS(connfd);
			printf("Reading Complete!!\n");
		}
		else if(!strcicmp(buffer,"D")){
			memset(buffer, '\0', sizeof(buffer)); 
			strcpy(buffer,"DownLoad");
			write(connfd, buffer, sizeof(buffer));
			printf("Wait For DownLoaded File Name..\n");
			read(connfd, buffer, sizeof(buffer));
			printf("DownLoaded File Name Gets: %s\n",buffer);
			// Get File Name
			downLoad(buffer);
			printf("DownLoading Complete!!\n");
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
