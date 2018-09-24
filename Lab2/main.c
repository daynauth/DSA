#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "iSort.h"

typedef char *string;
typedef string *stringArray;

void printList(int *A, int n);
int compareInt(const void *key1, const void *key2);
int compareStr(const void *key1, const void *key2);
    
void allocate(stringArray *words, size_t num_words, size_t word_len);
void free_array(stringArray *array, size_t num_words);

int main(){
    int num_of_names = 3, length_of_names = 20;
    int i;

    stringArray names;
    allocate(&names, num_of_names, length_of_names);
    
    strcpy(names[0], "spiderman");
    strcpy(names[1], "wonderwoman");
    strcpy(names[2], "batman");

    insertionSort(names, num_of_names, sizeof(char *), compareStr);
/*
    insertionSort(names, num_of_names, sizeof(char) * length_of_names, compareStr);
    for(i = 0; i < 3; i++)
        printf("%s, ", names[i]);
    
    printf("\n");
*/
    /*
    char names[3][20] = {"spiderman", "wonderwoman","batman"};
    insertionSort(names, num_of_names, sizeof(char) * length_of_names, compareStr);
    for(i = 0; i < 3; i++)
        printf("%s, ", names[i]);
    

    printf("\n");
    */
    for(i = 0; i < 3; i++)
    {
        printf("%s\n", names[i]);
    }
    free_array(&names, num_of_names);
}

void allocate(stringArray *words, size_t num_words, size_t word_len){
  size_t i = 0;

  *words = malloc(sizeof(char *) * num_words * word_len);
 
  for(i = 0; i < num_words; i++)
  {
    (*words)[i] = malloc(sizeof(char) * word_len);
  }
}

void free_array(stringArray *array, size_t num_words){
  size_t i = 0;
 
  for(i = 0; i < num_words; i++)
    free((*array)[i]);
  
  free(*array);
}

void printList(int *A, int n){
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", A[i]);
    
    printf("\n");
}

int compareStr(const void *key1, const void *key2){
    char *s1 = *(char **)key1;
    char *s2 = *(char **)key2;
    return strcmp(s1, s2);
}
int compareInt(const void *key1, const void *key2){
    return *(int *)key1 - *(int *)key2;
}

