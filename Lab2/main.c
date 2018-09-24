#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insertion_sort.h"

#define NUMBER_OF_NAMES   3
#define LENGTH_OF_NAME    20

typedef char *string;
typedef string *stringArray;

int compareInt(const void *key1, const void *key2);
int compareStr(const void *key1, const void *key2);

void allocate(stringArray *words, size_t num_words, size_t word_len);
void free_array(stringArray *array, size_t num_words);

int main()
{
  size_t i = 0;

  stringArray names = NULL;

  /* We first need to allocate memory to hold the
   * strings we need to sort.
   */
  allocate(&names, NUMBER_OF_NAMES, LENGTH_OF_NAME);

  /* After memory has been allocated, we can now store
   * the strings we need to sort in the allocated memory.
   */
  strcpy(names[0], "spiderman\0");
  strcpy(names[1], "wonderwoman\0");
  strcpy(names[2], "batman\0");

  /* Now the strings can be sorted using an insertion sort.
   * Since we're passing an array of character pointers, the
   * size of each element is sizeof(char *).
   */
  insertionSort(names, NUMBER_OF_NAMES, sizeof(char *), compareStr);

  /* Print sorted list */
  for(i = 0; i < NUMBER_OF_NAMES; i++)
  {
    fprintf(stdout, "%s\n", names[i]);
  }

  /* Free the memory we allocated to store the strings */
  free_array(&names, NUMBER_OF_NAMES);

  return EXIT_SUCCESS;
}

void allocate(stringArray *words, size_t num_words, size_t word_len)
{
  size_t i = 0;

  /* Allocate memory to hold the number of words we want */
  *words = malloc(sizeof(char *) * num_words);

  /* Check if allocation was successful */
  if(*words == NULL)
  {
    fprintf(stderr, "Failed to allocate word memory\n");
    exit(EXIT_FAILURE);
  }

  /* For each word, allocate space for the number of characters */
  for(i = 0; i < num_words; i++)
  {
    (*words)[i] = malloc(sizeof(char) * (word_len + 1)); //Add 1 for NULL terminator

    /* Once again, ensure allocation was successful */
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

  /* To free all memory we need to iterate and free the
   * memory that was allocated for each word.
   */
  for(i = 0; i < num_words; i++)
  {
    free((*array)[i]);
  }

  /* Now we can free the memory allocated for the number of words */
  free(*array);
}

int compareStr(const void *key1, const void *key2)
{
  /* The void pointer we receive here is a pointer to a
   * pointer to an array of characters. So these first ned
   * to be cast to char ** and the dereferenced to char *
   * to get the value. 
   */
  char *s1 = *(char **)key1;
  char *s2 = *(char **)key2;

  /* Return result of comparsion */
  return strcmp(s1, s2);
}
