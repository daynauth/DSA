#include<stdio.h>
#include<stdlib.h>
#define STACK_MAX 100

typedef struct{
    int top;
    int ST[STACK_MAX];
} stack, *stackPtr;

stackPtr stack_init();
void push(stackPtr sp, int n);
int pop(stackPtr sp);
int stack_empty(stackPtr sp);
int peek(stackPtr sp);

int main(){
    stackPtr S = stack_init();
    int i;

    for(i = 0; i < STACK_MAX; i++){
        push(S, i);
    }

    for(int i = 0; i < 10; i++){
        printf("pop: %d\n", pop(S));
    }
    free(S);
    return 0;
}

stackPtr stack_init(){
    stackPtr sp = malloc(sizeof(stack));
    if(sp == NULL){
        printf("stack could not be created");
        exit(1);
    }

    sp->top = -1;
    return sp;
}

void push(stackPtr sp, int n){
    sp->top++;

    if(sp->top == STACK_MAX){
        printf("Stack Overflow");
        exit(1);
    }

   sp->ST[sp->top] = n;
}

int pop(stackPtr sp){
    if(stack_empty(sp)){
        printf("Empty stack\n");
        exit(1);
    }

    int temp = sp->ST[sp->top];

    sp->top--;
    return temp;
}

int stack_empty(stackPtr sp){
    return sp->top == -1;
}

int peek(stackPtr sp){
    if(stack_empty(sp)){
        printf("Empty stack\n");
        exit(1);
    }

    return sp->ST[sp->top];
}
