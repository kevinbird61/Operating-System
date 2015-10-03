#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

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

int socket_client(char *ip, int port)
{
    int sockfd = 0;
    char buffer[1024];
    struct sockaddr_in serv_addr; 

    memset(buffer, '\0',sizeof(buffer)); // memset() use to set all the specific space to a specific char
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)	// Check is connected or not 
    {
        printf("\n Error : Could not create socket\n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); // Same , initialize the buffer

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 		// htons : 通常用於deal with "little-Endian" or "Big-Endian"

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) 	// inet_pton convert IPv4 and IPv6 addresses from text to binary form
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
//========================connection complete=====================================//
	while(1){
	    if (read(sockfd, buffer, sizeof(buffer)) < 0)
	    {
		printf("\n Error : Read Failed \n");
		return 1;
	    }
   
	    printf("From Server port's message :\n%s\n", buffer);
	    if(!strcicmp(buffer,"End")){
		exit(1);
	    }
	    sleep(1);
	    //====================Data ready to deliver======================//
	    memset(buffer, '\0', sizeof(buffer));
	    //strcpy(buffer, "I get client message!");
	    
	    scanf("%s",&buffer);

	    if (write(sockfd, buffer, strlen(buffer)) < 0) //準備寫回server端
	    {
		printf("\n Error : Write Failed \n");
		return 1;
	    }
	}
//===========================End socket===========================================//
    close(sockfd);
    return 0;
}

int main(int argc, char *argv[])
{
    socket_client("127.0.0.1", 5000);
    return 0;
}
