// DLList.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, August 2014

#ifndef DLLIST_H
#define DLLIST_H

#include <stdio.h>


// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of strings (i.e. items are strings)

typedef struct DLListRep *DLList;

// create a new empty DLList
DLList newDLList();

// free up all space associated with list
void freeDLList(DLList);

// create an DLList by reading items from a file
// assume that the file is open for reading
DLList getDLList(FILE *);

DLList FileAppendDLList(FILE *, DLList);

DLList AlphaAppend(FILE *, DLList, DLList);

// return number of elements in a list
int DLListLength(DLList);


int Length(DLList);

//Given a position in a linked list, the following function
//Returns the value at at that position.
char * valueReturn(DLList, int);
// The following function prints a given linked list 
void printList(DLList);
// Given a list, and a word, the following function determines whether a word
// exists in the list. 
int elementExists (DLList, char*);

// Given a list, and a url, the following function determines whether a url
// exists in the list. 
int elementIsUrl(DLList, char*);
// Normalises a given word
char * normalise(char*);

// Removes grammar from a given word 
char * removegrammar (char *);
// Creates a linked list of words in an entire collection. 
DLList PureAppend(FILE *, DLList, DLList);
// Calculates the length of a DLList, starting at 1. 
int LengthForMalloc(DLList);

#endif
