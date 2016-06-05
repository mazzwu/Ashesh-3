// DLList.c (taken from ideas of DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by Winnie Zheng & Vivian Bakiris

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

// data structures representing DLList

// create a new DLListNode (private function)
DLListNode *newDLListNode(char *it)
{
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    new->data = strdup(it);
    new->prev = new->next = NULL;
    new->i = 0;
    new->wordFreq = 0;
    new->totalFreq = 0;
    return new;
}

// create a new empty DLList
DLList newDLList()
{
    struct DLListRep *L;
    
    L = malloc(sizeof (struct DLListRep));
    assert (L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    L->curr = NULL;
    return L;
}

// free up all space associated with list
void freeDLList(DLList L)
{
    assert(L != NULL);
    DLListNode *curr, *prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(L);
}

DLList getDLList(FILE *in)
{
    DLList L;
 
    char *line = malloc(sizeof(char));
    L = newDLList();
    while (fscanf(in,"%s\n",line) != EOF) {
        DLListAfter(L,line);
            }

    return L;
}
// display items from a DLList, one per line
void showDLList(DLList L)
{
   // assert(out != NULL);
    if(L == NULL) {
        return;
    }
    DLListNode *curr;
    //printf("here\n");
    assert(L != NULL);

    for (curr = L->first; curr != NULL; curr = curr->next)
      //  printf("");
        printf("%s\n",curr->data);
}

// check sanity of a DLList (for testing)
int validDLList(DLList L)
{
    if (L == NULL) {
        fprintf(stderr,"DLList is null\n");
        return 0;
    }
    if (L->first == NULL) {
        // list is empty; curr and last should be null
        if (L->last != NULL || L->curr != NULL) {
            fprintf(stderr,"Non-null pointers in empty list\n");
            return 0;
        }
    }
    else {
        // list is not empty; curr and last should be non-null
        if (L->last == NULL || L->curr == NULL) {
            fprintf(stderr,"Null pointers in non-empty list\n");
            return 0;
        }
    }
    int count;
    DLListNode *curr;
    // check scanning forward through list
    count = 0;
    for (curr = L->first; curr != NULL; curr = curr->next) {
        if (curr->prev != NULL && curr->prev->next != curr) {
            fprintf(stderr, "Invalid forward link into node (%s)\n",curr->data);
            return 0;
        }
        if (curr->next != NULL && curr->next->prev != curr) {
            fprintf(stderr, "Invalid backward link into node (%s)\n",curr->data);
            return 0;
        }
        count++;
    }
    if (count != L->nitems) {
        fprintf(stderr, "Forward count mismatch; counted=%d, nitems=%d\n",
                count, L->nitems);
        return 0;
    }
    // check scanning backward through list
    count = 0;
    for (curr = L->last; curr != NULL; curr = curr->prev) {
        count++;
    }
    if (count != L->nitems) {
        fprintf(stderr, "Backward count mismatch; counted=%d, nitems=%d\n",
                count, L->nitems);
        return 0;
    }
    // nothing went wrong => must be ok
    return 1;
}

// return item at current position
char *DLListCurrent(DLList L)
{
    assert(L != NULL); assert(L->curr != NULL);
    return L->curr->data;
}


// insert an item before current item
// new item becomes current item
void DLListBefore(DLList L, char *it)
{
    assert(L != NULL);
    DLListNode *new = newDLListNode(it);
    new->next = L->curr; //new node will always point to the old current before adjusting the new current.
    if(L->curr->prev != NULL){ //if there is more than one node in the current list
        new->prev = L->curr->prev;
        L->curr->prev->next = new;
        L->curr->prev = new;
    } else { //if there is only one node in the list.
        new->prev = NULL; //
        L->first = new;
        L->curr->prev = new;
    }
    L->curr = new;
    L->nitems++;
}

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{
    DLListNode *new = newDLListNode(it);
    if(L->first == NULL) {
       // printf("heree\n");
        L->first = new;
        L->last = new;
        L->curr = new;
        L->nitems++;
        return;
    }
    assert(L != NULL);
    new->prev = L->curr;
    if(L->curr->next != NULL){
          // printf("hereee\n");
        new->next = L->curr->next;
        L->curr->next->prev = new;
    } else {
        new->next = NULL;
        L->last = new;
    }
    L->curr->next = new;
    L->curr = new;
    L->nitems++;
}

// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList L)
{
    assert (L !=NULL);
    
    DLListNode *temp;
    
    if (L->nitems == 0){
        printf("nope :)\n");
    }else if (L->nitems == 1) {
        L->first = NULL;
        L->last = NULL;
        L->curr = NULL;
        //free (L);
    } else if(L->curr->prev == NULL){ //first node
        temp = L->curr;
        L->curr = L->curr->next;
        L->curr->prev = NULL;
        L->first = L->curr;
        free (temp);
    } else if (L->curr->next == NULL){ //last node
        temp = L->curr;
        L->curr = L->curr->prev;
        L->curr->next = NULL;
        L->last = L->curr;
        free (temp);
    } else { //middle node
        temp = L->curr;
        L->curr = L->curr->next;
        temp->prev->next = L->curr;
        L->curr->prev = temp->prev;
        free(temp);
        
    }
 
    L->nitems--;
}

//return number of elements in a list
int DLListLength(DLList L)
{
    return (L->nitems);
}

// is the list empty?
int DLListIsEmpty(DLList L)
{
    return (L->nitems == 0);
}
DLList listcopy(DLList L) {
    
    DLList copy = newDLList();
    DLListNode *temp = newDLListNode(L->first->data);
    temp = L->first;
    
    while(temp->next != NULL) {
        DLListAfter(copy, temp->data);
        temp = temp->next;
        //printf("DLList copy %s\n", temp->data);
    }
     DLListAfter(copy, temp->data);
    
    return copy;
}


