#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int value;
}NodeData;

typedef struct treenode{
    NodeData key;
    struct treenode *left, *right, *parent;
}TreeNode, *TreeNodePtr;

typedef struct{
    TreeNodePtr root;
} BinaryTree;

typedef BinaryTree *Tree;

/*Give an integer n, create a new node for the tree*/
TreeNodePtr createNode(int n);

/*Insert a integer n into the Binary Search Tree T*/
void treeInsert(Tree T, int n);

/*A utility function for building a tree given a list of integers*/
Tree buildTree(int *list, int size);

/*Visit the node of the tree and print its element*/
void visit(TreeNodePtr node);

/*Inorder traversal of the tree*/
void inOrder(TreeNodePtr node);

/*Find the minimum element of a subtree, pass the root to 
 * search the entire tree */
TreeNodePtr treeMinimum(TreeNodePtr node);

/*Search a subtree for an integer k*/
TreeNodePtr treeSearch(TreeNodePtr node, int k);

/*Transplant a node v, into the position occupied by u*/
void transplant(Tree T, TreeNodePtr u, TreeNodePtr v);

/*Delete a node z from the tree*/
void treeDelete(Tree T, TreeNodePtr z);

int main(){
    int list[5] = {3,5, 4, 1, 6};


    //Use the utility function to create a tree of 5 elements
    Tree T = buildTree(list, 5);

    //print the smallest element in the tree
    printf("The minimum value in the tree is: %d\n", treeMinimum(T->root)->key.value);

    //search for the node containing the item 3
    TreeNodePtr item = treeSearch(T->root, 3);
    
    if(item != NULL){
        //delete the node that contains 3
        printf("Deleting item %d from the tree\n", item->key.value);
        treeDelete(T, item);
    }
    

    //do an inorder traversal to print all the elements of the tree
    inOrder(T->root);
    printf("\n");

    return 0;
}

void visit(TreeNodePtr node){
    printf("%d ", node->key.value);
}

void inOrder(TreeNodePtr node){
    if(node != NULL){
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

TreeNodePtr treeMinimum(TreeNodePtr node){
    while(node->left != NULL)
        node = node->left;
    
    return node;
}

void transplant(Tree T, TreeNodePtr u, TreeNodePtr v){
    if(u->parent == NULL)
        T->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    
    if(v != NULL)
        v->parent = u->parent;
}

void treeDelete(Tree T, TreeNodePtr z){
    if(z->left == NULL)
        transplant(T, z, z->right);
    else if(z->right == NULL)
        transplant(T, z, z->left);
    else {
        TreeNodePtr y = treeMinimum(z->right);

        if(y->parent != z){
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    free(z);
}
