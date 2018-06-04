#include <stdio.h>
#include "functions.h"

//$ gcc main.c -o sudoku -lpthread
//$ ./sudoku assets/1.txt

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Use: ./bin assets/some-sudoku.txt\n");
		exit(0);
	}

	pthread_mutex_init(&line_mutex, NULL);
	pthread_mutex_init(&column_mutex, NULL);
	pthread_mutex_init(&grid_mutex, NULL);

	int fd, i, j, my_id[9] = {0,1,2,3,4,5,6,7,8}, error = 0;
	char c; 

	fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		printf("Error opening the file where sudoku is.\n Use: ./main assets/some-sudoku.txt\n");
	}

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			
			while(1){
					read(fd, &c, 1);
					if(c >= '1' && c <= '9'){
						break;
					}	
				}
					
			sudoku_matrix[i][j] = c - '0';
			
		}
	}

	pthread_t line_tid[9];
	pthread_attr_t line_attr[9];
	pthread_t column_tid[9];
	pthread_attr_t column_attr[9];
	pthread_t grid_tid[9];
	pthread_attr_t grid_attr[9];

	for(i = 0; i < 9; i++){
		pthread_attr_init(&line_attr[i]);
		pthread_create(&line_tid[i],&line_attr[i], line_thread, &my_id[i]);
		pthread_attr_init(&column_attr[i]);
		pthread_create(&column_tid[i],&column_attr[i], column_thread, &my_id[i]);
		pthread_attr_init(&grid_attr[i]);
		pthread_create(&grid_tid[i],&grid_attr[i], grid_thread, &my_id[i]);
	}

	for(i = 0; i < 9; i++){
		pthread_join(line_tid[i], NULL);
		pthread_join(column_tid[i], NULL);
		pthread_join(grid_tid[i], NULL);
	}

	for(i = 0; i < 9; i++){
		for(j = 0; j< 9; j++){

			printf("%d ",sudoku_matrix[i][j]);
		}
		printf("\n");
	}
	
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
		printf("%d error(s) found in your sudoku.\n", error);
	}

	pthread_mutex_destroy(&line_mutex);
	pthread_mutex_destroy(&column_mutex);
	pthread_mutex_destroy(&grid_mutex);

	return 0;
}
