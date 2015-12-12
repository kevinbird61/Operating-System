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
/* MUTEX */
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;
int counter[2] = {0 ,0};

int main(int argc,char *argv[]){
	int i,j;
	/* Get the thread count and File name*/
	thread_count = strtol(argv[1] , NULL , 10);
	long thread;
	pthread_t *thread_handlers = malloc(thread_count*sizeof(pthread_t));
	char *filename = argv[2] ;
	FILE *fp = fopen(filename , "r");
	printf("Thread count = %d , filename is %s\n" , thread_count , filename);
	/* Get the input file (by .txt) 
	mat_first for the first matrix
	mat_after for the second matrix
	mat_result for the result matrix
	Example : for matrix 3x5 * 5*4 =>
	row_size = 3 , col_size = 5 , sec_mat_col = 4
	*/
	/* Dealing with the file , and make it to the array */
	fscanf(fp, "%d %d",&row_size,&col_size);
	printf("First row is %d , col is %d \n", row_size , col_size);
	mat_first = allocate_dim(row_size , col_size);
	for(i = 0; i< row_size ; i++){
		for(j = 0 ; j< col_size ; j++){
			fscanf(fp , "%1d" , &mat_first[i][j]);
		}
	}
	fscanf(fp,"\n"); // escape from blank
	fscanf(fp, "%d %d",&col_size,&sec_mat_col);
	printf("Second row is %d , col is %d \n", col_size , sec_mat_col);
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
	
	printf("%d %d \n" , row_size , sec_mat_col);
	for(i = 0; i< row_size ; i++){
		for(j = 0 ; j< sec_mat_col ; j++){
			printf("%d ", mat_result[i][j]);
		}
		printf("\n");
	}
	
	free(mat_first);
	free(mat_after);
	free(mat_result);
	return 0;
}

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
	int i , j , k;
	int local_m = row_size/ thread_count;
	int my_first_row = my_rank == 0 ? 0 :my_rank * local_m + 1;
	int my_last_row = (my_rank == thread_count-1) ? ((my_rank+1)*local_m)+row_size % thread_count : ((my_rank+1)*local_m) ;
	/* limitation of the row and thread number , result will not fail*/
	if(my_last_row >= row_size-1){ my_last_row = row_size-1 ;}
	
	for(i = my_first_row ; i <= my_last_row ; i++){
		for(k = 0;k<sec_mat_col;k++){
			mat_result[i][k] = 0.0;
			for(j = 0; j < col_size ; j++){
				mat_result[i][k] += mat_first[i][j] * mat_after[j][k];
			}
		}
	}
	//printf("Now rank is %ld \n", my_rank);
	return NULL;
}