#ifndef _MAIN_H_
#define _MAIN_H_
struct Node {
    char name[50];
    char telephone[15];
    long long balance;   
};
struct Tree {
  char name[50];
  struct Node *Account;
  int total;
  struct Tree *left;
  struct Tree *right;
};
typedef struct Node *keyvalue;
typedef struct Node *element_t;
typedef struct Tree* treeNode;
typedef struct Tree* tree;
tree createTree();
int isNullTree(tree t);
void makeNULLTree(tree *t);
element_t createData(char name[],char phone[],long long balance);
tree createNewNode(element_t x);
tree leftNode(tree t);
tree rightNode(tree t);
tree addLeftMost(tree t,treeNode x);
tree addRightMost(tree t,treeNode x);
int countNode(tree t);
int heightTree(tree t);
int isLeaf(tree t);
int countLeaf(tree t);
tree mergeTwoSubNode(tree node1,tree node2,treeNode x);
tree search(tree t , keyvalue x);
void insert(tree *t, keyvalue x);
tree deleteNode(tree root,keyvalue x);
void freeTree(tree t);
tree findMin(tree t); 
tree findMax(tree t);
void prettyPrint(tree t,char *prefix);
int countInnerNode(tree t);
int rightChildCount(tree t);
char* treeToString(tree t);
void traversal(tree t);
void printAccount(tree t);
#endif