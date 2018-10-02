#include<stdio.h>
#include<stdlib.h>

typedef void *nodeData;

typedef struct _node{
    nodeData data;
    struct _node *next;
} node, *nodePtr;

typedef nodePtr List;

nodePtr createNode(nodeData data);
void LIST_append(nodePtr *head, nodeData data);
nodePtr LIST_last(List l);
void LIST_free(nodePtr current);
int LIST_isEmpty(List l);
typedef void (* printFunction)(const void *data);
void LIST_print(List l, printFunction f);
void printInt(const void *data);
void LIST_destroy(List *l);

int main(){
    List l = NULL;
    int arr[] = {1,2,3,4,5}, i;

    for(i = 0; i < 5; i++){
        //pass a reference to the list and the data to be added
        LIST_append(&l, arr + i);
    }


    LIST_print(l, printInt);
    //LIST_free(l);
    LIST_destroy(l);
    return EXIT_SUCCESS;
}

void LIST_print(List l, printFunction f){
    while(l != NULL){
        f(l->data);
        l = l->next;
    }
}

void printInt(const void *data){
    fprintf(stdout, "data: %d\n", *(int *)data);
}

void LIST_free(nodePtr current){
    while(current != NULL){
        nodePtr temp = current;
        current = current->next;

        free(temp);
    }
}

void LIST_append(nodePtr *head, nodeData data){
    //deference the pointer and assigns it to a variable that iterates through the list
    nodePtr current = *head;
    nodePtr newNode = createNode(data);

    if(LIST_isEmpty(*head)){
        *head = newNode;
    }
    else{
        LIST_last(current)->next = newNode;
    }
}


nodePtr createNode(nodeData data){
    nodePtr newNode = malloc(sizeof(node));

    if(newNode == NULL){
        printf("Node enough memory");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int LIST_isEmpty(List l){
    return l == NULL;
}

nodePtr LIST_last(List l){
    while(l->next != NULL)
        l = l->next;

    return l;
}

void LIST_destroy(List *l){
    nodePtr current = *l;
    nodePtr next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    *l = NULL;
}
