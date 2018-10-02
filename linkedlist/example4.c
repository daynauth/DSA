#include <stdio.h>
#include <stdlib.h>

/* Simple node for list */
typedef struct _node{
  int data; /* Data held by node */
  struct _node *next; /* Address of next node */
} node, *nodePtr;
typedef nodePtr List;

void printList(nodePtr current);
nodePtr createNode(int data);
void LIST_distroy(List *l);

int main()
{
  /* Now create several nodes*/
  nodePtr n1 = createNode(22);
  nodePtr n2 = createNode(10);
  nodePtr n3 = createNode(9);
  nodePtr n4 = createNode(-45);
  nodePtr n5 = createNode(1024);


  /* Now link them all together (create the linked list) */
  n1->next = n2; /* n1.next is assigned the address of n2 */
  n2->next = n3; /* n2.next is assigned the address of n3 */
  n3->next = n4; /* n3.next is assigned the address of n4 */
  n4->next = n5; /* n4.next is assigned the address of n5 */
  n5->next = NULL; /* n5.next is assigned NULL to indicate it's the end of the list */

  /* Now to print the list moving from node to node */
  nodePtr current = NULL; //This will be the pointer we move from one node to the other

  current = n1; //Get the address of n1

  /*Call the print function to iterate through the list and print each element*/
  printList(current);

  return EXIT_SUCCESS;
}

void printList(nodePtr current){
    if(current != NULL){
      fprintf(stdout, "Data: %d\n", current->data); 
      printList(current->next);
    }
}


nodePtr createNode(int data){
    nodePtr newNode = malloc(sizeof(struct node));

    //make sure that the memory was correctly allocated
    if(newNode == NULL){
        printf("Out of memory");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void LIST_distroy(List *l){
    nodePtr current = *l;
    nodePtr next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    *l = NULL;
}
