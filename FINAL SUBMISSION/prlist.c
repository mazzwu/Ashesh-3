// prlist.c (taken from ideas of DLList.c - Implementation of doubly-linked list ADT
// Comp1927 Assignment2 June 3 2016
// Written by John Shepherd, March 2013
// Modified by Winnie Zheng & Vivian Bakiris

//this prlist differs to other dLList files as this one is specifically used to support pagerank.c funcitons//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "prlist.h"
#include <string.h>

// data structures representing DLList

// create a new DLListItem (private function)
DLListItem *newDLListItem(char *it)
{
    DLListItem *new;
    new = malloc(sizeof(DLListItem));
    assert(new != NULL);
    new->data = strdup(it);
    new->prev = new->next = NULL;
    new->outDegree = 0;
    new->PR = 0;
    return new;
}

// create a new empty DLList
DLListPR newDLListPR()
{
    struct DLListRepPR *L;
    
    L = malloc(sizeof (struct DLListRepPR));
    assert (L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    L->curr = NULL;
    return L;
}

// free up all space associated with list
void freeDLListPR(DLListPR L)
{
    assert(L != NULL);
    DLListItem *curr, *prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(L);
}

// trim off \n from strings (private function)
// this is needed for getDLList() because of fgets()
// alternatively, we could use the evil gets() function
static char *trimSpace(char *s)
 {
 int end = strlen(s)-1;
 if (s[end] == '\n') s[end] = '\0';
 return s;
 }


// create an DLList by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
DLListPR getDLListPR(FILE *in)
{
    DLListPR L;
    
    char *line = malloc(sizeof(char*)*(sizeof(in)));
    L = newDLListPR();
    while (fscanf(in,"%s\n",line) != EOF) {
        DLListPRAfter(L,line);
    }
    
    return L;
}
// display items from a DLList, one per line
void showDLListPR(DLListPR L)
{
    // assert(out != NULL);
    if(L == NULL) {
        return;
    }
    DLListItem *curr;
    //printf("here\n");
    assert(L != NULL);
    
    for (curr = L->first; curr != NULL; curr = curr->next)
        //  printf("");
        printf("shD: %s\n",curr->data);
}

// check sanity of a DLList (for testing)
int validDLListPR(DLListPR L)
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
    DLListItem *curr;
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

// insert an item after current item
// new item becomes current item
void DLListPRAfter(DLListPR L, char *it)
{
    DLListItem *new = newDLListItem(it);
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


//used to rearrange pagerankList.txt in descending order
DLListPR PageRankAppend(FILE *in, DLListPR L){
    
    char word[1000];
    
    // printf("Is it even doing this?\n");
    int counter = 0;
    
    DLListItem *curr = L->first;
    DLListItem *new = L->first;
    DLListItem *lastcalled = L->first;
    while (fscanf(in,"%s",word) != EOF) {
        
        counter++;
        char * value = strdup(trimSpace(word));
        
        if(counter == 1){
            new = newDLListItem(value);
            lastcalled = new;
            continue;
        }
        if(counter == 2){
            lastcalled->outDegree = value;
            continue;
        }
        
        if(counter == 3){
            lastcalled-> PR = value;
            counter = 0;
        }
        
        
        if (L->first == NULL) {
            L->first = new;
            L->last = new;
            curr = L->last;
        }
        else {
            if(strcmp(new->PR,L->last->PR)<0){
                
                L->last->next = new;
                new->prev = L->last;
                L->last = new;
                curr = L->last;
            }
            else if (strcmp(new->PR,L->last->PR)>0){
                while ((strcmp(new->PR,curr->PR)>0) && (curr->prev != NULL)){
                    curr = curr->prev;
                }
                if(L->nitems == 1){
                    new->next = curr;
                    curr->prev = new;
                    L->first = new;
                    curr = L->last;
                }
                
                else if((strcmp(new->PR,curr->PR)>0)&& (curr->prev == NULL)){
                    new->next = curr;
                    curr->prev = new;
                    L->first = new;
                    curr = L->last;
                    
                }
                else {
                    new->next = curr ->next;
                    new->prev = curr;
                    curr->next->prev = new;
                    curr->next = new;
                    curr = L->last;
                }
            }
        }
        
        L->nitems++;
    }
    L->curr = L->first;
    return L;
}
//return number of elements in a list
int DLListPRLength(DLListPR L)
{
    return (L->nitems);
}
//used to rearrange pageranklist.txt in descending order
void printListPR (DLListPR L) {
    
    FILE* pr = fopen("pagerankList.txt", "w");
    DLListItem *curr = L->first;
    
    // printf(" %s \n",L->first->data);
    assert(L!= NULL);
    
    while(curr != NULL){
        fprintf(pr, "%s %s %s \n",curr->data, curr->outDegree, curr->PR);
        curr=curr->next;
    }
    fclose(pr);
    printf("\n");
    
    return;
}


DLListPR listcopyPR(DLListPR L) {
    
    DLListPR copy = newDLListPR();
    DLListItem *temp = newDLListItem(L->first->data);
    temp = L->first;
    
    while(temp->next != NULL) {
        DLListPRAfter(copy, temp->data);
        temp = temp->next;
        //printf("DLList copy %s\n", temp->data);
    }
    DLListPRAfter(copy, temp->data);
    
    return copy;
}


