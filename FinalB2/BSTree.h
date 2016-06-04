// BSTree.h ... interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H


typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char *);
// check whether a value is in a BSTree
int BSTreeFind(BSTree, char *);
// delete a value from a BSTree
//BSTree BSTreeDelete(BSTree, char *);

BSTree getBSTree(FILE *, int);


void treeTraverse(BSTree);

int sizeOfFile(FILE *urlFILE);

#endif
