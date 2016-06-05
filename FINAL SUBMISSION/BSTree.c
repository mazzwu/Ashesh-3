//  BSTree.c
//  Assignment 2 COMP1927
//  3 June 2016
//  Created by John Shepherd
//  Created/Modified by Winnie Zheng && Vivian Bakiris

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "Queue.h"
#include "DLList.h"

typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
    char * value;
    BSTLink left, right;
} BSTNode;


// make a new node containing a value
static BSTLink newBSTNode(char * v)
{
    
    BSTLink new = malloc(sizeof(BSTNode));
    assert(new != NULL);
    new->value = v;
    new->left = new->right = NULL;
    return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
    
    return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
    if (t == NULL) return;
    dropBSTree(t->left);
    dropBSTree(t->right);
    free(t);
}



// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, char * v)
{
    
    
    if (t == NULL){
        
        return newBSTNode(v);
        
    }
    
    
    else if (strcmp(v,t->value) < 0){
        
        t->left = BSTreeInsert(t->left, v);
    }
    else if (strcmp(v,t->value) > 0){
        
        t->right = BSTreeInsert(t->right, v);
    }
    else {
        
    }
    return t;
}

// check whether a value is in a BSTree
int BSTreeFind(BSTree t, char * v)
{
    if (t == NULL)
        return 0;
    else if (strcmp(v,t->value) < 0)
        return BSTreeFind(t->left, v);
    else if (strcmp (v,t->value) > 0)
        return BSTreeFind(t->right, v);
    else // (v == t->value)
        return 1;
}


// Creates a BST of all the words in a given file
BSTree getBSTree(FILE *urlFILE, int size){
    
    char *wordArray[1000];
    BSTree T = NULL;
    char * normalised = NULL;
    char * removedgrammar = NULL;
    int i= 0;
    for(i = 0; i<size; i++){
        wordArray[i] = malloc(sizeof(char));
        fscanf(urlFILE, "%s", wordArray[i]);
        
        normalised = norm(wordArray[i]);
        removedgrammar = removeg(normalised);
        T = BSTreeInsert(T, removedgrammar);
    }
    
    return T;
}

void treeTraverse(BSTNode *T){
    
    if(T!= NULL)
    {
        treeTraverse(T->left); // recursively print smaller item
        printf("%s ",T->value); // print current item
        treeTraverse(T->right); //
        return; 
        
    }
}

int sizeOfFile(FILE *urlFILE){
    
    int filesize = 0;
    char string[1000];
    while(fscanf(urlFILE,"%s",string)!= EOF){
        filesize++;
    }
    
    return filesize;
}

char * norm (char* str){
  int i;
  for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
       str[i]=str[i]+32;
  }

  return str;
}

char * removeg (char * str){
    int p = 0;
  for(p = 0; p<=(strlen(str));p++){
        if(str[p]=='.'|| str[p]==','|| str[p]=='?'|| str[p]=='!'){
            str[p]='\0';
        }
    
  }

  return str;

}



