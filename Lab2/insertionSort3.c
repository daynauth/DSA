#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int (*comparePtr)(const void *key1, const void *key2);
void insertionSort(void const *A, int n, int vSize, comparePtr compare);
void printList(int *A, int n);
int compareInt(const void *key1, const void *key2);

int main(){
    int n = 5;
    int arr[] = {5, 1, 3, 2, 4};
    printList(arr, n);
    insertionSort(arr, n, sizeof(int), compareInt);

    printList(arr, n);
}

void insertionSort(void const *A, int n, int vSize, comparePtr compare){
    int i;

    char *data = (char *)A;
    void *key;

    if((key = (char *)malloc(sizeof(vSize))) == NULL){
        printf("Out of memory\n");
        exit(1);
    }

    for(i = 1; i < n; i++){
        memcpy(key, data + (i * vSize), vSize);
        int j = i - 1;

        while(j >= 0 && compare(&data[j * vSize], key) > 0){
            memcpy(&data[(j + 1) * vSize], &data[j * vSize], vSize);
            j--;
        }
        memcpy(&data[(j + 1) * vSize], key, vSize);
    }

    free(key);
}

void printList(int *A, int n){
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", A[i]);
    
    printf("\n");
}

int compareInt(const void *key1, const void *key2){
    return *(int *)key1 - *(int *)key2;
}
