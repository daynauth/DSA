#include <stdio.h>
#include <stdlib.h>

/* Simple node for list */
struct node{
  int data; /* Data held by node */
  struct node *next; /* Address of next node */
};

void printList(struct node *current);
struct node createNode(int data);

int main()
{
  /* Now create several nodes */
  struct node n1 = createNode(22);
  struct node n2 = createNode(10);
  struct node n3 = createNode(9);
  struct node n4 = createNode(-45);
  struct node n5 = createNode(1024);


  /* Now link them all together (create the linked list) */

  n1.next = &n2; /* n1.next is assigned the address of n2 */
  n2.next = &n3; /* n2.next is assigned the address of n3 */
  n3.next = &n4; /* n3.next is assigned the address of n4 */
  n4.next = &n5; /* n4.next is assigned the address of n5 */
  n5.next = NULL; /* n5.next is assigned NULL to indicate it's the end of the list */

  /* Now to print the list moving from node to node */
  struct node *current = NULL; //This will be the pointer we move from one node to the other

  current = &n1; //Get the address of n1

  /*Call the print function to iterate through the list and print each element*/
  printList(current);

  return EXIT_SUCCESS;
}

void printList(struct node *current){
    if(current != NULL){
      fprintf(stdout, "Data: %d\n", current->data); 
      printList(current->next);
    }
}


struct node createNode(int data){
    struct node newNode;
    newNode.data = data;
    return newNode;
}
