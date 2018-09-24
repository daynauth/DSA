#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insertion_sort.h"

/* A          A pointer to the data to be sorted
 * n          The number of elements to be sorted
 * vSize      The size of each element
 * compare    A callback function to be used for comparing elements
 *
 * This is a generic insertionSort so it takes a void data type, for this reason
 * some more information needs to be passed so sorting can occur correctly. The
 * Extra information needed is the number of elements and the size of each element.
 * Since we don't know what type of element we're sorting, a callback function
 * needs to be used to do comparsions on the types.
 *
 * The callback function required here takes the address of two void types, 
 * dereferences them and performs a comparsion. 
 */
void insertionSort(void const *A, size_t n, size_t vSize, comparePtr compare){
  size_t i;

  char *data = (char *)A;
  void *key = NULL;

  /* Allocate memory that matches size of every element */
  key = malloc(vSize);

  /* Ensure we successfully allocated memory */
  if(key == NULL)
  {
    printf("Out of memory\n");
    exit(EXIT_FAILURE);
  }

  for(i = 1; i < n; i++)
  {
    memcpy(key, data + i * vSize, vSize);
    ssize_t j = i - 1;

    while(j >= 0 && compare(&data[j * vSize], key) > 0)
    {
      memcpy(data + (j + 1) * vSize,  data + j * vSize, vSize);
      j--;
    }
    memcpy(&data[(j + 1) * vSize], key, vSize);
  }
  free(key);
}
