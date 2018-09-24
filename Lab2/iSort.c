#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "iSort.h"

void insertionSort(void const *A, int n, int vSize, comparePtr compare){
    (void) compare;
    int i;

    char *data = (char *)A;
    char *key;

    if((key = malloc((vSize))) == NULL){
        printf("Out of memory\n");
        exit(1);
    }

    for(i = 0; i < n; i++){
        memcpy(key, data + i * vSize, vSize);
        //fprintf(stdout, "Key: %s\n", key);
        int j = i - 1;

        while(j >= 0 && compare(&data[j * vSize], key) > 0){
            memcpy(data + (j + 1) * vSize,  data + j * vSize, vSize);
            j--;
        }
        memcpy(&data[(j + 1) * vSize], key, vSize);
    }

    free(key);
}
