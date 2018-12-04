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

TreeNodePtr createNode(int n);
void treeInsert(Tree T, int n);
Tree buildTree(int *list, int size);
void visit(TreeNodePtr node);
void inOrder(TreeNodePtr node);
TreeNodePtr treeMinimum(TreeNodePtr node);
TreeNodePtr treeSearch(TreeNodePtr node, int k);
void transplant(Tree T, TreeNodePtr u, TreeNodePtr v);
void treeDelete(Tree T, TreeNodePtr z);

int main(){
    int list[5] = {3,5, 4, 1, 6};


    Tree T = buildTree(list, 5);

    printf("The minimum value in the tree is: %d\n", treeMinimum(T->root)->key.value);

    TreeNodePtr item = treeSearch(T->root, 3);
    
    if(item != NULL){
        printf("Deleting item %d from the tree\n", item->key.value);
        treeDelete(T, item);
    }
    

    inOrder(T->root);
    printf("\n");

    return 0;
}

TreeNodePtr createNode(int n){
    TreeNodePtr node = malloc(sizeof(TreeNode));
    if(node == NULL){
        printf("Node could node be created\n");
        exit(1);
    }

    node->key.value = n;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void treeInsert(Tree T, int n){
    TreeNodePtr y = NULL;
    TreeNodePtr x = T->root;
    TreeNodePtr z = createNode(n);

    while(x != NULL){
        y = x;

        if(z->key.value < x->key.value)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;

    if(y == NULL)
        T->root = z;
    else if(z->key.value < y->key.value)
        y->left = z;
    else
        y->right = z;
    
}

Tree buildTree(int *list, int size){
    Tree T = malloc(sizeof(BinaryTree));
    if(T == NULL){
        printf("Tree could not be created.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < size; i++){
        treeInsert(T, list[i]);     
    }

    return T;
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

TreeNodePtr treeSearch(TreeNodePtr node, int k){
    if(node == NULL || k == node->key.value)
        return node;
    
    if(k < node->key.value)
        return treeSearch(node->left, k);
    else return treeSearch(node->right, k);
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
