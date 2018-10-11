#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
    int data;
    struct _node *next;
} node, *nodePtr;

typedef nodePtr list;

typedef struct {
    nodePtr list;
} stack, *stackPtr;


nodePtr createNode(int n);
void LIST_push(list *l, int n);
int LIST_pop(list *l);
void LIST_destroy(list *l);

stackPtr stack_init();
void push(stackPtr S, int n);
int pop(stackPtr S);
void destroy(stackPtr S);

int main(){
    stackPtr S = stack_init();
    int i;

    for(i = 0; i < 10; i++){
        push(S, i);
    }

    for(i = 0; i < 5; i++){
        printf("pop: %d\n", pop(S));
    }

    destroy(S);
    return 0;
}

stackPtr stack_init(){
    stackPtr S = malloc(sizeof(node));

    if(S == NULL){
        printf("Stack could not be created\n");
        exit(1);
    }

    return S;
}

void push(stackPtr S, int n){
    LIST_push(&S->list, n);
}

int pop(stackPtr S){
    if(S->list == NULL){
        printf("List is empty\n");
        exit(1);
    }

    return LIST_pop(&S->list);
}

void destroy(stackPtr S){
    LIST_destroy(&S->list);

    free(S);
}

nodePtr createNode(int n){
    nodePtr newNode = malloc(sizeof(node));
    newNode->data = n;
    newNode->next = NULL;
    return newNode;
}

void LIST_push(list *l, int n){
    nodePtr newNode = createNode(n);

    newNode->next = *l;
    *l = newNode;
}

int LIST_pop(list *l){
    nodePtr current = *l;
    int data = current->data;

    *l = current->next;
    free(current);
    return data;
}

void LIST_destroy(list *l){
    nodePtr current = *l;
    nodePtr next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    
    *l = NULL;
}
