// DLList.h - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by Winnie Zheng & Vivian Bakiris
#ifndef DLLIST_H
#define DLLIST_H

#include <stdio.h>
#include "DLList.h"

// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of strings (i.e. items are strings)

typedef struct DLListRep *DLList;

typedef struct DLListNode {
    char   *data;  // data of this list item (string)
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    int i;
    char *word;  //query term
  
    //counters used to calculate tfdf
    
    int wordFreq; //the frequency of each word contained in this particular page
    int totalFreq; //used to calculate total frequency
    int numDocs; //the number of urls/documents that contain this word.
} DLListNode;

typedef struct DLListRep {
    int  nitems;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *curr;  // current node in list
    DLListNode *last;  // last node in list
} DLListRep;

// create a new empty DLList
DLList newDLList();
DLListNode *newDLListNode(char *it);
// free up all space associated with list
void freeDLList(DLList);

// create an DLList by reading items from a file
// assume that the file is open for reading
DLList getDLList(FILE *);
// display list on output, one item per line
void showDLList(DLList);

// check sanity of a DLList (for testing)
int validDLList(DLList);

// return item at current position
char *DLListCurrent(DLList);

// insert an item before current item
// new item becomes current item
void DLListBefore(DLList, char *);

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList, char *);

// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList);

// return number of elements in a list
int DLListLength(DLList);

DLList listcopy(DLList L);

#endif
