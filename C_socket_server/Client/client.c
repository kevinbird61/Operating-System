#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
// For case insensitive ; 1 for different , and 0 for same
int strcicmp(char const *str1,char const *str2)
{
    int length = strlen(str1),check = strlen(str2),count=0;
    for(; count!=length; str1++,str2++) {
        int d = tolower(*str1) - tolower(*str2);
        if(d!=0 || !*str1) {
            return 1;
        }
        count++;
    }
    if(count!=check) {
        return 1;
    }
    return 0;
}
// Call For Socket Client
int socket_client(char *ip, int port)
{
    int sockfd = 0;
    char buffer[1024];
    struct sockaddr_in serv_addr;

    //memset(buffer, '\0',sizeof(buffer)); // memset() use to set all the specific space to a specific char

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {	// Check is connected or not
        printf("\n Error : Could not create socket\n");
        return 1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr)); // Same , initialize the buffer

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 		// htons : 通常用於deal with "little-Endian" or "Big-Endian"

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) {	// inet_pton convert IPv4 and IPv6 addresses from text to binary form
        printf("\n inet_pton error occured\n");
        return 1;
    }
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
//========================connection complete=====================================//
    char msg[1024];
    while(1) {
    	memset(buffer, '\0',sizeof(buffer));
        if (read(sockfd, buffer, sizeof(buffer)) < 0) {
            printf("\n Error : Read Failed \n");
            return 1;
        }
		
        if(!strcicmp(buffer,"End")) {
            exit(1);
        } else if(!strcicmp(buffer,"Please input the content you want to edit in this file")) {
            printf("From Server say :\n%s\n", buffer);
            //sleep(1);
            //read(sockfd, msg, sizeof(msg));
            while(strcicmp(msg,"OK!Stop~")) { // while not send the specify word
            	printf("Get Input ( \"StopIn\" to Stop input)\n");
                memset(msg, '\0', sizeof(msg));
                scanf("%s",msg);
                printf("Input The \"StopIn\" to Stop input\n");
                if (write(sockfd, msg, sizeof(msg)) < 0) { //準備寫回server端
                    printf("\n Error : Write Failed \n");
                    return 1;
                }
                memset(msg, '\0', sizeof(msg));
                read(sockfd,msg, sizeof(msg));
            }
            memset(buffer, '\0', sizeof(buffer));
        } else if(!strcicmp(buffer,"Show")) { // Do the "ls" instruction
            printf("The File List:\n");
            while(1) {
                char bk[128];
                read(sockfd, bk, sizeof(bk));
                if(!strcicmp(bk,"OK!STOPLS")) {
                    break;
                }
                printf("%s\n",bk);
                write(sockfd,"Y",1);
            }
            printf("========End of List========\n\n");
        } else if(!strcicmp(buffer,"DownLoad")) { // Do the DownLoad Instruction
            char dFile[1024];
            memset(dFile,'\0',sizeof(dFile));
            printf("Which file in \"Server端\" you want to download?\n");
            scanf("%s",dFile);
            write(sockfd,dFile,sizeof(dFile));
            memset(dFile,'\0',sizeof(dFile));
            read(sockfd,dFile,sizeof(dFile));
            printf("%s\n",dFile);
            memset(dFile,'\0',sizeof(dFile));
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) // Get Currently File Path
                strcpy(dFile,cwd);
            write(sockfd,dFile,sizeof(dFile));
            printf("End of DownLoad Input\n\n");

        } else {
            printf("========================================\n");
            printf("From Server port's message :\n%s\n", buffer);
            sleep(1);
            //====================Data ready to deliver======================//
            //strcpy(buffer, "I get client message!")
            memset(buffer, '\0', sizeof(buffer));
            scanf("%s",buffer);
            if(!strcicmp(buffer,"End")) {
                exit(1);
            }
            if (write(sockfd, buffer, sizeof(buffer)) < 0) { //準備寫回server端
                printf("\n Error : Write Failed \n");
                return 1;
            }
        }
    }
//===========================End socket===========================================//
    close(sockfd);
    return 0;
}

int main(int argc, char *argv[])
{
    char ip[9];
    printf("Please Enter the port you want to link:\n");
    scanf("%s",ip);
    socket_client(ip, 5000);
    return 0;
}
