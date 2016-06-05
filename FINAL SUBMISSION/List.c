// List.c - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
//  Assignment 2 COMP1927
//  June 2016
//  Modified by Winnie Zheng && Vivian Bakiris
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "List.h"


// data structures representing List

typedef struct ListNode {
    char   *value;  // value of this list item (string)
    struct ListNode *prev;
                   // pointer prev node in list
    struct ListNode *next;
                   // pointer to next node in list
} ListNode;

typedef struct ListRep {
    int  nitems;      // count of items in list
    ListNode *first; // first node in list
    ListNode *curr;  // current node in list
    ListNode *last;  // last node in list
} ListRep;

// create a new ListNode (private function)
static ListNode *newListNode(char *it)
{
    ListNode *new;
    new = malloc(sizeof(ListNode));
    assert(new != NULL);
    new->value = strdup(it);
    new->prev = new->next = NULL;
    return new;
}

// create a new empty List
List newList()
{
    struct ListRep *L;

    L = malloc(sizeof (struct ListRep));
    assert (L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    L->curr = NULL;
    return L;
}

// free up all space associated with list
void freeList(List L)
{
    assert(L != NULL);
    ListNode *curr, *prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(L);
}

// trim off \n from strings (private function)
// this is needed for getList() because of fgets()
// alternatively, we could use the evil gets() function
static char *trim(char *s)
{
    int end = strlen(s)-1;
    if (s[end] == '\n') s[end] = '\0';
    return s;
}

// create an List by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
List getList(FILE *in)
{
    List L;
    ListNode *new;
    char line[1000];

    L = newList();
    while (fgets(line,1000,in) != NULL) {
        char *value = strdup(trim(line));
        new = newListNode(value);
        if (L->last == NULL) {
            L->first = L->last = new;
        }
        else {
            L->last->next = new;
            new->prev = L->last;
            L->last = new;
        }
        L->nitems++;
    }   
    L->curr = L->first;
    return L;
}




List FileAppendList(FILE *in, List L){
    //List L;
    ListNode *new;
    char word[1000];

    if(L == NULL){
        L = newList();
    }
    

    while (fscanf(in,"%s",word) != EOF) {

        char *value = strdup(trim(word));
        new = newListNode(value);

        if (elementExists(L,value) != 0) continue;
        //if (elementIsUrl(D, value) != 0) continue;


        if (L->last == NULL) {
            L->first = L->last = new;
        }
        else {
            L->last->next = new;
            new->prev = L->last;
            L->last = new;
        }
        L->nitems++;
    }   
    L->curr = L->first;
    return L;
}


//The following function takes in a file, inserting each element in 
// alphabetical order without duplicates. 

List PureAppend(FILE *in, List L, List D){

    ListNode *new;
    char word[1000];
 
 
    while (fscanf(in,"%s",word) != EOF) {
          
        char * valueold = strdup(trim(word));
        char * value = normalise(valueold);
        char * value2 = removegrammar(value);
        ListNode *curr = L->last;
        
        new = newListNode(value2);

        if (elementExists(L,value2) != 0) continue;
       
        if (elementIsUrl(D, value2) != 0) continue;

        if (L->first == NULL) {
            L->first = new;
            L->last = new;
            curr = L->last;
        }

        else {
            
            if(strcmp(new->value,L->last->value)>0){
            
                L->last->next = new;
                new->prev = L->last;
                L->last = new;
                curr = L->last;
            }

                
            else if (strcmp(new->value,L->last->value)<0){

                while((strcmp(new->value,curr->value)<0) && (curr->prev != NULL)){
                    curr = curr->prev; 
                   
                }
               

                if(L->nitems == 1){
                    new->next = curr;
                    curr->prev = new;  
                    L->first = new; 
                    curr = L->last;
                }

                else if((strcmp(new->value,curr->value)<0)&& (curr->prev == NULL)){   
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

// return number of elements in a list
int ListLength(List L)
{
    return (L->nitems);
}


int Length(List L){
    int length = 0;
    ListNode *curr; 
    curr = L->first;
    while(curr->next != NULL){
        length = length +1;
        curr = curr->next; 
    }
    return (length);

}

int LengthForMalloc(List L){
    int length = 1;
    ListNode *curr; 
    curr = L->first; 
    while(curr->next != NULL){
        length = length +1; 
        curr = curr->next; 
    }
    return(length);
    }

//Given a position in a linked list, the following function
//Returns the value at at that position. 
char * valueReturn(List L, int x){

    ListNode *curr;  
    curr = L->first;
    //printf("The value x is %d \n", x);
    int i = 0; 

    while((curr->next != NULL) && (i < x)){

        curr = curr->next;
        i++; 

    }

    return(curr->value);  
  

}

void printList(List L){

    ListNode *curr;
    curr = L-> first;
    assert(L!= NULL);

    printf("[%s]->",curr->value);

    while(curr->next != NULL){
        printf("[%s]->",curr->next->value);
        curr=curr->next; 
    }
    printf("\n");

    return;
}

// Returns 0 if word doesn't exist
int elementExists (List L, char* word){
    ListNode *curr;
    curr = L->first; 
    int exists = 0; 

    

    if(L->first == NULL){

        if(strcmp(word,"#start")==0){
            exists = exists + 1;
            return exists;
        }

        else if(strcmp(word, "#end") == 0){
            exists = exists + 1;
            return exists;
        }

        else if (strcmp(word, "section-1")==0){
            exists = exists + 1;
            return exists;
        }
        else if (strcmp(word,"section-2")==0){
            exists = exists + 1;
            return exists;
        }

        else{

        return exists;

        }

    }

    else if(strcmp(word,"#end")==0){
        exists = exists + 1;
        return exists;
    }

    else if (strcmp(word, "section-1")==0){
            exists = exists + 1;
            return exists;
        }

    else if (strcmp(word,"section-2")==0){
            exists = exists + 1;
            return exists;
        }
    if(strcmp(word,"#start")==0){
            exists = exists + 1;
            return exists;
        }
    
    else {

    while(curr->next != NULL){


        if (strcmp(word, curr->value) == 0){
            // then the word has been found 
            exists = exists + 1;
            return exists;
        }
        else{         
            // Leave check as is 
       
        }

        curr = curr->next;
    
    }
}
    return exists; 

}

//returns 0 if it is not a url, returns an int otherwise 
int elementIsUrl(List D, char *oldWord){
    int IsUrl = 0; 
    ListNode *curr; 
    curr = D->first;

    if (D->first == NULL){
        if(strcmp(oldWord,D->first->value)==0){
            IsUrl = IsUrl +1;
            
            return IsUrl;
        }
        else {
             
                
            }

        
    }

    else{


        while(curr != NULL){
        if (strcmp(oldWord, curr->value) == 0){
            // then the word has been found 
            IsUrl++;
           
            return IsUrl;

        }
        else {         
                
            } 

            curr = curr->next;
        } 
            
    }

    return IsUrl;

}


char * normalise (char* str){
  int i;
  for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
       str[i]=str[i]+32;
  }

  return str;
}

char * removegrammar (char * str){
    int p = 0;
  for(p = 0; p<=(strlen(str));p++){
        if(str[p]=='.'|| str[p]==','|| str[p]=='?'|| str[p]=='!'){
            str[p]='\0';
        }
    
  }

  return str;

}



