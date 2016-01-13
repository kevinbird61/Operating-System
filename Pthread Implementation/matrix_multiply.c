#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *matrix_mul(void *rank);
int **allocate_dim(int row , int col);
/*  Global variable */
int thread_count ;
int row_size , col_size , sec_mat_col;
int **mat_first;
int **mat_after;
int **mat_result;

int main(int argc,char *argv[]){
	int i,j;
	/* Get the thread count and File name*/
	//thread_count = strtol(argv[1] , NULL , 10);
	char *filename = argv[1] ;
	FILE *fp = fopen(filename , "r");
	/* Get the input file (by .txt) 
	mat_first for the first matrix
	mat_after for the second matrix
	mat_result for the result matrix
	Example : for matrix 3x5 * 5*4 =>
	row_size = 3 , col_size = 5 , sec_mat_col = 4
	*/
	/* Dealing with the file , and make it to the array */
	fscanf(fp, "%d %d",&row_size,&col_size);
	//printf("First row is %d , col is %d \n", row_size , col_size);
	long thread;
	//printf("Thread count = %d , filename is %s\n" , thread_count , filename);
	mat_first = allocate_dim(row_size , col_size);
	for(i = 0; i< row_size ; i++){
		for(j = 0 ; j< col_size ; j++){
			fscanf(fp , "%1d" , &mat_first[i][j]);
		}
	}
	fscanf(fp,"\n"); // escape from blank
	fscanf(fp, "%d %d",&col_size,&sec_mat_col);
	thread_count = row_size * sec_mat_col;
	pthread_t *thread_handlers = malloc(thread_count*sizeof(pthread_t));
	//printf("Second row is %d , col is %d \n", col_size , sec_mat_col);
	mat_after =  allocate_dim(col_size , sec_mat_col);
	for(i = 0; i< col_size ; i++){
		for(j = 0 ; j< sec_mat_col ; j++){
			fscanf(fp , "%1d" , &mat_after[i][j]);
		}
	}
	/* Dealing with the file , and make it to the array  ~ OVER (Check OK!)*/
	/* Allocate the result matrix*/
	mat_result = allocate_dim(row_size , sec_mat_col);
	/* Start to use pthread to calculate */
	for(thread = 0 ; thread < thread_count ; thread ++ ){
		pthread_create(&thread_handlers[thread],NULL,matrix_mul,(void*)thread);
	}
	for(thread = 0 ; thread < thread_count ; thread ++ ){
		pthread_join(thread_handlers[thread],NULL);
	}
	/* Print the result */
	printf("%d %d \n" , row_size , sec_mat_col);
	for(i = 0; i< row_size ; i++){
		for(j = 0 ; j< sec_mat_col ; j++){
			printf("%d ", mat_result[i][j]);
		}
		printf("\n");
	}
	/* Free the memory */
	free(mat_first);
	free(mat_after);
	free(mat_result);
	return 0;
}
/* Allocate the 2D - dimension array*/
int **allocate_dim(int row , int col){
	int i;
	int **a = (int **)malloc(row * sizeof(int*) + (row*col*sizeof(int)) );
	int *mem = (int*) (a + row);
	for(i = 0; i< row ; i++){
		a[i] = mem+(i*col);
	}
	return a;
}

void *matrix_mul(void *rank){
	long my_rank = (long)rank;
	int i;
	int mult_row = (my_rank / sec_mat_col);
	int mult_col = (my_rank % sec_mat_col);
	for(i = 0; i < col_size ; i++){
		mat_result[mult_row][mult_col] += mat_first[mult_row][i] * mat_after[i][mult_col];
	}
	//printf("Now rank is %ld \n", my_rank);
	return NULL;
}
