#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

//$ gcc main.c -o main -lpthread
//$ ./main sudoku1.txt

int sudoku_matrix[9][9];
int line[9];
int column[9];
int grid[9];

pthread_mutex_t line_mutex, column_mutex, grid_mutex; 

int verify(int *vector);
void *line_thread(void *param);
void *column_thread(void *param);
void *grid_thread(void *param);

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Use: ./main sudokus/sudoku[number].txt\n");
		exit(0);
	}

	pthread_mutex_init(&line_mutex, NULL);
	pthread_mutex_init(&column_mutex, NULL);
	pthread_mutex_init(&grid_mutex, NULL);

	int fd, i, j, my_id[9] = {0,1,2,3,4,5,6,7,8}, error = 0;
	char c; 

	fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		printf("Error open the file where sudoku is.\n Use: ./main sudoku[number].txt\n");
	}

	for(i = 0; i < 9; i++){
		for(j = 0; j< 9; j++){
			
			do{
				read(fd,&c,1);
			}while(c == ' ' || c == '\n');

			sudoku_matrix[i][j] = c - '0';
		}
	}

	pthread_t line_tid[9];
	pthread_attr_t line_attr[9];
	pthread_t column_tid[9];
	pthread_attr_t column_attr[9];
	pthread_t grid_tid[9];
	pthread_attr_t grid_attr[9];

	for(i=0; i<9; i++){
		pthread_attr_init(&line_attr[i]);
		pthread_create(&line_tid[i],&line_attr[i], line_thread, &my_id[i]);
		pthread_attr_init(&column_attr[i]);
		pthread_create(&column_tid[i],&column_attr[i], column_thread, &my_id[i]);
		pthread_attr_init(&grid_attr[i]);
		pthread_create(&grid_tid[i],&grid_attr[i], grid_thread, &my_id[i]);
	}

	for(i=0;i<9;i++){
		pthread_join(line_tid[i], NULL);
		pthread_join(column_tid[i], NULL);
		pthread_join(grid_tid[i], NULL);
	}

	//testing
	/*
	for(i = 0; i < 9; i++){
		for(j = 0; j< 9; j++){

			printf("%d ",sudoku_matrix[i][j]);
		}
		printf("\n");
	}
	*/

	for(i=0;i<9;i++){
		if(line[i] == 0){
			printf("Error in line: %d\n", i + 1);
			error++;
		}
		if(column[i] == 0){
			printf("Error in column: %d\n", i + 1);
			error++;
		}
		if(grid[i] == 0){
			printf("Error in grid: %d\n", i + 1);
			error++;
		}
	}

	if(error == 0){
		printf("No errors were found in your sudoku.\n");
	}

	else{
		printf("%d error(s) was/were found in your sudoku.\n", error);
	}


	pthread_mutex_destroy(&line_mutex);
	pthread_mutex_destroy(&column_mutex);
	pthread_mutex_destroy(&grid_mutex);

	return 0;

}

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