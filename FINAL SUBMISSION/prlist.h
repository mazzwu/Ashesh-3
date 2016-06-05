// prlist.h (taken from ideas of DLList.c - Implementation of doubly-linked list ADT
// Comp1927 Assignment2 June 3 2016
// Written by John Shepherd, March 2013
// Modified by Winnie Zheng & Vivian Bakiris


#ifndef prlist_H
#define prlist_H

#include <stdio.h>
//#include "prlist.h"

// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of strings (i.e. items are strings)

typedef struct DLListRepPR *DLListPR;

typedef struct DLListItem {
    char   *data;  // data of this list item (string)
    struct DLListItem *prev;
    // pointer previous node in list
    struct DLListItem *next;
    //double pr;
    char *PR; 
    char *outDegree;
  
} DLListItem;

typedef struct DLListRepPR {
    int  nitems;      // count of items in list
    DLListItem *first; // first node in list
    DLListItem *curr;  // current node in list
    DLListItem *last;  // last node in list
} DLListRepPR;

DLListPR PageRankAppend(FILE *in, DLListPR L);

DLListItem *newDLListItem(char *it);
// create a new empty DLList

DLListPR newDLListPR();

// free up all space associated with list
void freeDLListPR(DLListPR);

// create an DLList by reading items from a file
// assume that the file is open for reading
DLListPR getDLListPR(FILE *);
// display list on output, one item per line

void showDLListPR(DLListPR);

// check sanity of a DLList (for testing)
int validDLListPR(DLListPR);

void DLListPRAfter(DLListPR, char *);

void DLListPRDelete(DLListPR);

// return number of elements in a list
int DLListPRLength(DLListPR);


DLListPR listcopyPR(DLListPR L);

void printListPR (DLListPR L);

#endif
