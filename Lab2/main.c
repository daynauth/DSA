#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "insertion_sort.h"

#define NUMBER_OF_NAMES   3
#define LENGTH_OF_NAME    20

typedef char *string;
typedef string *stringArray;

void printList(int *A, int n);
int compareInt(const void *key1, const void *key2);
int compareStr(const void *key1, const void *key2);

void allocate(stringArray *words, size_t num_words, size_t word_len);
void free_array(stringArray *array, size_t num_words);

int main()
{
  size_t i;

  stringArray names;
  allocate(&names, NUMBER_OF_NAMES, LENGTH_OF_NAME);

  strcpy(names[0], "spiderman");
  strcpy(names[1], "wonderwoman");
  strcpy(names[2], "batman");

  insertionSort(names, NUMBER_OF_NAMES, sizeof(char *), compareStr);

  for(i = 0; i < NUMBER_OF_NAMES; i++)
  {
    fprintf(stdout, "%s\n", names[i]);
  }

  free_array(&names, NUMBER_OF_NAMES);

  return EXIT_SUCCESS;
}

void allocate(stringArray *words, size_t num_words, size_t word_len)
{
  size_t i = 0;

  *words = malloc(sizeof(char *) * num_words * word_len);

  if(*words == NULL)
  {
    fprintf(stderr, "Failed to allocate word memory\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < num_words; i++)
  {
    (*words)[i] = malloc(sizeof(char) * word_len);

    if((*words)[i] == NULL)
    {
      fprintf(stderr, "Failed to allocate character memory!\n");
      exit(EXIT_FAILURE);
    }
  }
}

void free_array(stringArray *array, size_t num_words)
{
  size_t i = 0;

  for(i = 0; i < num_words; i++)
  {
    free((*array)[i]);
  }

  free(*array);
}

int compareStr(const void *key1, const void *key2)
{
  char *s1 = *(char **)key1;
  char *s2 = *(char **)key2;

  return strcmp(s1, s2);
}
