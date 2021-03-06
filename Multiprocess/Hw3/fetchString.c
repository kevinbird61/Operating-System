#include "fetchString.h"

int fetch_specify_str(char* spec_str,char* source, int size_spec , int start , int end){
	int i , j , judge = 0, count = 0;
	for( i = start ; i < end ; i++){
		if(source[i] == spec_str[0]){
			for(j = i ; j < i + size_spec ; j++){
				if(source[j] != spec_str[j-i])break;
				judge++;
			}
			if(judge != size_spec){
			// not match
			judge = 0;
			}
			else{
			// compare match!
			judge = 0;
			count++;
			}
		}
	}
	return count;
}

int lengthof(char *src ){
	char c ;
	int count = 0;
	FILE *fp;
	fp = fopen(src , "r"); 
	if(fp == NULL){
		perror("Error Opening File");
	}
	while((c=fgetc(fp)) != EOF){
		count++;
	}
	return count;
}

char *contentof(char *filename , int size){
	char c ;
	char *dest = malloc(size*sizeof(char));
	int index = 0;
	FILE *fp;
	fp = fopen(filename , "r"); 
	if(fp == NULL){
		perror("Error Opening File");
	}
	while((c=fgetc(fp)) != EOF){
		dest[index] = c;
		index++;
	}
	/* clean the dirty char */
	dest[index] = '\0';
	return dest;
}
