#include <stdio.h>
#include <stdlib.h>

/* Simple node for list */
struct node{
  int data; /* Data held by node */
  struct node *next; /* Address of next node */
};

void printList(struct node *current);

int main()
{
  /* Now create several nodes */
  struct node n1;
  struct node n2;
  struct node n3;
  struct node n4;
  struct node n5;

  /* Give each node data */
  n1.data = 22;
  n2.data = 10;
  n3.data = 9;
  n4.data = -45;
  n5.data = 1024;

  /* Now link them all together (create the linked list) */

  n1.next = &n2; /* n1.next is assigned the address of n2 */
  n2.next = &n3; /* n2.next is assigned the address of n3 */
  n3.next = &n4; /* n3.next is assigned the address of n4 */
  n4.next = &n5; /* n4.next is assigned the address of n5 */
  n5.next = NULL; /* n5.next is assigned NULL to indicate it's the end of the list */

  /* Now to print the list moving from node to node */

  struct node *current = NULL; //This will be the pointer we move from one node to the other

  current = &n1; //Get the address of n1

  printList(current);

  return EXIT_SUCCESS;
}

void printList(struct node *current){
    if(current != NULL){
      fprintf(stdout, "Data: %d\n", current->data); 
      printList(current->next);
    }
}
