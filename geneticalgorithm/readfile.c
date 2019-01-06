#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DIMENSION_LINE 5
#define DATA_START_LINE 8

typedef struct info{
	size_t id;
	double x;
	double y;
}info_t;

size_t get_dimension(char *line){
	char *dim = strrchr(line, ':');
	size_t dimension = 0;

	if(dim != NULL){
		sscanf(dim+1, "%zu", &dimension);
	}else{
		fprintf(stderr, "Failed to get dimension from line: %s!\n", line);
		exit(EXIT_FAILURE);
	}
	return dimension;
}

void print_info(size_t dimension, info_t *info){
	size_t i = 0;

	for(i = 0; i < dimension; i++){
		fprintf(stdout, "%zu %.4lf %.4lf\n", info[i].id, info[i].x, info[i].y);
	}
}

int main(){
	FILE *fp = NULL;
	char line[128];
	char *fname = "lu980.tsp";
	size_t dimension = 0;

  info_t *info = NULL;

	fp = fopen(fname, "r");

	if(fp == NULL){
		fprintf(stderr, "Failed to open %s\n", fname);
		exit(EXIT_FAILURE);
	}

	unsigned int line_number = 1;
	size_t idx = 0;
	while(fgets(line, sizeof(line), fp) != NULL){
		if(line_number == DIMENSION_LINE){
			dimension = get_dimension(line);
			info = malloc(sizeof(info_t) * dimension);

			if(info	== NULL){
				fprintf(stderr, "Failed to allocate memory for info\n");
				exit(EXIT_FAILURE);
			}
		}

		if(line_number >= DATA_START_LINE && idx <= dimension){
			sscanf(line, "%zu %lf %lf", &info[idx].id, &info[idx].x, &info[idx].y);
			idx++;
		}

		line_number++;
	}

	print_info(dimension, info);

	free(info);
	fclose(fp);

	return EXIT_SUCCESS;
}
