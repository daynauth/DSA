#include<stdio.h>

void insertionSort(int *A, int n);
void printList(int *A, int n);
int compare(int a, int b);

int main(){
    int n = 5;
    int arr[] = {5, 1, 3, 2, 4};
    printList(arr, n);
    insertionSort(arr, n);

    printList(arr, n);
}

void insertionSort(int *A, int n){
    int i;

    for(i = 1; i < n; i++){
        int key = A[i];

        int j = i - 1;

        while(j >= 0 && compare(A[j], key) > 0){
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

void printList(int *A, int n){
    int i;

    for(i = 0; i < n; i++){
        printf("%d ", A[i]);
    }

    printf("\n");
}

int compare(int a, int b){
    if(a < b)return -1;
    return 1;
}
