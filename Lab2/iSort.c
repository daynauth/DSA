#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "iSort.h"

void insertionSort(void const *A, size_t n, size_t vSize, comparePtr compare){
    size_t i;

    char *data = (char *)A;
    void *key;

    if((key = malloc((vSize))) == NULL){
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    for(i = 1; i < n; i++){
        memcpy(key, data + i * vSize, vSize);
        ssize_t j = i - 1;

        while(j >= 0 && compare(&data[j * vSize], key) > 0){
            memcpy(data + (j + 1) * vSize,  data + j * vSize, vSize);
            j--;
        }
        memcpy(&data[(j + 1) * vSize], key, vSize);
    }

    free(key);
}
