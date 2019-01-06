#include<stdio.h>
#include<stdlib.h>

void test(int **arr){
    *arr = malloc(sizeof(int) * 2);
    (*arr)[0] = 3;
    (*arr)[1] = 4;
}


int main(){
    int *b = NULL;

    test(&b);

    printf("%d\n", b[0]);
    printf("%d\n", b[1]);

    free(b);
    return EXIT_SUCCESS;
}
