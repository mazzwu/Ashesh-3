// List.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, August 2014

#ifndef List_H
#define List_H

#include <stdio.h>


// External view of List
// Implementation given in List.c
// Implements a List of strings (i.e. items are strings)

typedef struct ListRep *List;

// create a new empty List
List newList();

// free up all space associated with list
void freeList(List);

// create an List by reading items from a file
// assume that the file is open for reading
List getList(FILE *);

List FileAppendList(FILE *, List);

List AlphaAppend(FILE *, List, List);

// return number of elements in a list
int ListLength(List);


int Length(List);

//Given a position in a linked list, the following function
//Returns the value at at that position.
char * valueReturn(List, int);
// The following function prints a given linked list 
void printList(List);
// Given a list, and a word, the following function determines whether a word
// exists in the list. 
int elementExists (List, char*);

// Given a list, and a url, the following function determines whether a url
// exists in the list. 
int elementIsUrl(List, char*);
// Normalises a given word
char * normalise(char*);

// Removes grammar from a given word 
char * removegrammar (char *);
// Creates a linked list of words in an entire collection. 
List PureAppend(FILE *, List, List);
// Calculates the length of a List, starting at 1. 
int LengthForMalloc(List);

#endif
