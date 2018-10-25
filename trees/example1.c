#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MaxWordSize 20

typedef struct{
    char word[MaxWordSize + 1];
}NodeData;

typedef struct treenode{
    NodeData data;
    struct treenode *left, *right;
} TreeNode, *TreeNodePtr;

typedef struct {
    TreeNodePtr root;
} BinaryTree;

TreeNodePtr buildTree(FILE *in);
void visit(TreeNodePtr node);
void preOrder(TreeNodePtr node);
void inOrder(TreeNodePtr node);
void postOrder(TreeNodePtr node);

int main(){
    FILE *in = fopen("btree.in", "r");
    BinaryTree b;
    b.root = buildTree(in);

    printf("Pre-Order Traversal: ");
    preOrder(b.root);
    printf("\n");
    
    printf("In-Order Traversal: ");
    inOrder(b.root);
    printf("\n");

    printf("Post-Order Traversal: ");
    postOrder(b.root);
    printf("\n");

    fclose(in);

    return 0;
}

TreeNodePtr buildTree(FILE *in){
    char str[MaxWordSize + 1];
    fscanf(in, "%s", str);

    if(strcmp(str, "@") == 0)return NULL;

    TreeNodePtr p = malloc(sizeof(TreeNode));
    strcpy(p->data.word, str);

    p->left = buildTree(in);
    p->right = buildTree(in);

    return p;
}

void visit(TreeNodePtr node){
    printf("%s ", node->data.word);
}

void preOrder(TreeNodePtr node){
    if(node != NULL){
        visit(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(TreeNodePtr node){
    if(node != NULL){
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}


void postOrder(TreeNodePtr node){
    if(node != NULL){
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}
