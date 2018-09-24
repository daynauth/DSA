#ifndef ISORT_H
#define ISORT_H


typedef int (*comparePtr)(const void *key1, const void *key2);
void insertionSort(void const *A, size_t n, size_t vSize, comparePtr compare);
#endif



