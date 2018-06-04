#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int sudoku_matrix[9][9];
int line[9];
int column[9];
int grid[9];
pthread_mutex_t line_mutex, column_mutex, grid_mutex; 

int verify(int *vector){
	/*
	verify retuns 0 if there's a error.
		   returns 1 if there's no error.
	*/

	int i, my_vector[9] = {0}, j = 0;
	for(i=0; i<9; i++){
		if(i == 0){
			my_vector[i] = vector[i];
		}
		else{
			j = 0;
			while(j <= i){
				if(my_vector[j] == vector[i]){
					return 0;
				}
				else if(j == i){
					my_vector[j] = vector[i];
					break;
				}
				j++;
			}
		}

	}

	return 1;
}

void *column_thread(void *param){
	int *my_id = (int *) param, i, my_vector[9];;
	for(i=0; i<9; i++){
		pthread_mutex_lock(&line_mutex);	
			my_vector[i] = sudoku_matrix[i][*my_id];
		pthread_mutex_unlock(&line_mutex);	
	}

	column[*my_id] = verify(my_vector);
	pthread_exit(0);
}

void *line_thread(void *param){
	int *my_id = (int *) param, j, my_vector[9];
    
	for(j=0; j<9; j++){
		pthread_mutex_lock(&column_mutex);
			my_vector[j] = sudoku_matrix[*my_id][j];
		pthread_mutex_unlock(&column_mutex);
	}
	line[*my_id] = verify(my_vector);
	pthread_exit(0);
}

void *grid_thread(void *param){

	int *my_id = (int *) param, i, j, k = 0, my_vector[9];

	for(i= 3*((*my_id/3)); i < 3*((*my_id/3) + 1); i++){
		for(j=3*((*my_id + 3)%3); j< 3*((*my_id+3)%3 + 1); j++){
			pthread_mutex_lock(&grid_mutex);
				my_vector[k] = sudoku_matrix[i][j];
				k++;
			pthread_mutex_unlock(&grid_mutex);
		}
	}
	grid[*my_id] = verify(my_vector);
	pthread_exit(0);
}