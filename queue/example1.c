#include<stdio.h>
#include<stdlib.h>
#define MAXQ 100

typedef struct{
    int head;
    int tail;
    int QA[MAXQ];
} queue, *queuePtr;

queuePtr initQueue();
int empty(queuePtr Q);
void enqueue(queuePtr Q, int n);
int dequeue(queuePtr Q);

int main(){
    int i;
    queuePtr Q = initQueue();

    for(i = 0; i < 20; i++){
        enqueue(Q, i);
    }

    for(i = 0; i < 10; i++){
        printf("Q%d: %d\n", i, dequeue(Q));
    }
    return 0;

    free(Q);
}

queuePtr initQueue(){
    queuePtr Q = malloc(sizeof(queue));
    Q->head = 0;
    Q->tail = 0;

    return Q;
}

int empty(queuePtr Q){
    return Q->head == Q->tail;
}

void enqueue(queuePtr Q, int n){
    Q->tail = (Q->tail + 1) % MAXQ;

    if(Q->tail == Q->head){
        printf("Queue is full\n");
        exit(1);
    }

    Q->QA[Q->tail] = n;
}

int dequeue(queuePtr Q){
    if(empty(Q)){
        printf("Queue is empty\n");
        exit(1);
    }
    Q->head = (Q->head + 1) % MAXQ;
    return Q->QA[Q->head];
}
