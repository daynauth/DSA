#include <stdio.h>
#include <stdlib.h>

/* Simple node for list */
struct node{
  int data; /* Data held by node */
  struct node *next; /* Address of next node */
};

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
  fprintf(stdout, "Data: %d\n", current->data); //Print data of n1
  
  /* Now remember, n1 was assigned the address of n2 (n1.next = &n2) */
  /* So to get the address of n2 we can simply do the following */

  current = current->next; /* Here we get the address of n2 and make it the current node */
  fprintf(stdout, "Data: %d\n", current->data); //Print data of n2

  /* Now remember, n2 was assigned the address of n3 (n2.next = &n3) */
  /* So to get the address of n3 we can simply do the following */

  current = current->next; /* Here we get the address of n3 and make it the current node */
  fprintf(stdout, "Data: %d\n", current->data); //Print data of n3

  /* Now remember, n3 was assigned the address of n4 (n3.next = &n4) */
  /* So to get the address of n3 we can simply do the following */

  current = current->next; /* Here we get the address of n4 and make it the current node */
  fprintf(stdout, "Data: %d\n", current->data); //Print data of n4

  /* Now remember, n4 was assigned the address of n5 (n4.next = &n5) */
  /* So to get the address of n5 we can simply do the following */

  current = current->next; /* Here we get the address of n5 and make it the current node */
  fprintf(stdout, "Data: %d\n", current->data); //Print data of n5

  return EXIT_SUCCESS;
}
