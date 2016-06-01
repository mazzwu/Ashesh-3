// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015
// Modified by Vivian Bakiris and Jacob Sturges 2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"

// data structures representing DLList

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer prev node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *curr;  // current node in list
	DLListNode *last;  // last node in list
} DLListRep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = strdup(it);
	new->prev = new->next = NULL;
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

// trim off \n from strings (private function)
// this is needed for getDLList() because of fgets()
// alternatively, we could use the evil gets() function
static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n') s[end] = '\0';
	return s;
}

// create an DLList by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
DLList getDLList(FILE *in)
{
	DLList L;
	DLListNode *new;
	char line[1000];

	L = newDLList();
	while (fgets(line,1000,in) != NULL) {
		char *value = strdup(trim(line));
		new = newDLListNode(value);
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




DLList FileAppendDLList(FILE *in, DLList L){
    //DLList L;
    DLListNode *new;
    char word[1000];

    if(L == NULL){
        L = newDLList();
    }
    

    while (fscanf(in,"%s",word) != EOF) {

        char *value = strdup(trim(word));
        new = newDLListNode(value);

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

DLList FileAppendDLList2(FILE *in, DLList L, DLList D){
    //DLList L;
    DLListNode *new;
    char word[1000];

    if(L == NULL){
        L = newDLList();
    }
    

    while (fscanf(in,"%s",word) != EOF) {

        char *value = strdup(trim(word));
        new = newDLListNode(value);

        if (elementExists(L,value) != 0) continue;
        if (elementIsUrl(D, value) != 0) continue;


        if (L->first== NULL) {
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

DLList AlphaAppend(FILE *in, DLList L, DLList D){

    DLListNode *new;
    char word[1000];
    DLListNode *curr;
 
    while (fscanf(in,"%s",word) != EOF) {
        printf("Now inserting %s\n", word);     
        char * valueold = strdup(trim(word));
        char * value = normalise(valueold);
        new = newDLListNode(value);
        //printf("Confirm Insertion %s\n",new->value);

        if (elementExists(L,value) != 0) continue;
        //printf("The element does not exist \n");
        if (elementIsUrl(D, value) != 0) continue;
        //printf("The element is not a URL\n");

        if (L->first == NULL) {
            //printf("The list is empty, adding %s to be first\n", new->value);
            L->first = new;
            L->last = new;
            curr = L->last;
        }

        else {
            //int prevvalue = strcmp(new->value,curr->value);
           // printf("The strcmp prevvalue of %s and %s is %d\n", new->value, curr->value, prevvalue);
            
            if(strcmp(new->value,L->last->value)>0){
               // printf("Adding value to end of the list\n");
                L->last->next = new;
                new->prev = L->last;
                L->last = new;
                curr = L->last;
            }

                
            else if (strcmp(new->value,L->last->value)<0){
            
                //printf("The word does not append to the end, so now we are\n");
                //printf("Comparing %s ", new->value);
                //printf("with  %s\n", L->last->value);
                //int value = strcmp(new->value,curr->value);
                //printf("The strcmp value of %s and %s is %d\n", new->value, curr->value, value);


                while((strcmp(new->value,curr->value)<0) && (curr->prev != NULL)){
                    curr = curr->prev; 
                    //printf("Iterating through while loop looking\n");
                }
                // If you're adding it to the front of the list 

                if(L->nitems == 1){
                   // printf("Adding to the front of the list\n");
                   // printf("current is %s\n", curr->value);
                    //printf("New->next[%s] = curr[%s]\n",new->next->value,curr->value);
                    new->next = curr;
                    curr->prev = new;  
                    L->first = new; 
                    curr = L->last;
                    //printf("L->first = [%s]\n", L->first->value);
                    //printf("L->first->next = [%s]\n", L->first->next->value);
                    //printf("L->last = [%s]\n", L->last->value);

                }

                else if((strcmp(new->value,curr->value)<0)&& (curr->prev == NULL)){// You get to the end and you need to insert it at the front
                    //printf("If the new value is smaller than the first ele\n");
                    new->next = curr; 
                    curr->prev = new;
                    L->first = new;
                    curr = L->last; 

                }
                else {
                printf("Adding in the middle\n");

                new->next = curr ->next; 
                new->prev = curr; 
                curr->next->prev = new; 
                curr->next = new; 
                curr = L->last;
                //printf("Changing pointers to insert now in order\n");
              }
            }
        }

        L->nitems++;
        printf("The new list is ");
        printList(L);
    }   
    L->curr = L->first;
    return L;
}



// display items from a DLList, one per line
void showDLList(FILE *out, DLList L)
{
	assert(out != NULL); assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
		fprintf(out,"%s\n",curr->value);
}


// return item at current position
char *DLListCurrent(DLList L)
{
	assert(L != NULL); assert(L->curr != NULL);
	return L->curr->value;
}

// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
// if current is currently null, return 1
int DLListMove(DLList L, int n)
{
	assert(L != NULL);
	if (L->curr == NULL)
		return 1;
	else if (n > 0) {
		while (n > 0 && L->curr->next != NULL) {
			L->curr = L->curr->next;
			n--;
		}
	}
	else if (n < 0) {
		while (n < 0 && L->curr->prev != NULL) {
			L->curr = L->curr->prev;
			n++;
		}
	}
	return (L->curr == L->first || L->curr == L->last);
}

// move to specified position in list
// i'th node, assuming first node has i==1
int DLListMoveTo(DLList L, int i)
{
	assert(L != NULL); assert(i > 0);
	L->curr = L->first;
	return DLListMove(L, i-1);



}

// insert an item before current item
// new item becomes current item
void DLListBefore(DLList L, char *it)
{
	assert(L != NULL);
    //Creates a new node to be placed in the list
    DLListNode *new = newDLListNode(it);
    

    //if the list empty
    if (L->nitems == 0) {
        L->curr = new;
        L->last = new;
        L->first = new;
        //increases the value of nitems
        L->nitems++;

    } else {
        //if the node is being place at the front of the list this also reassigns first as new
        if (L->curr == L->first) {

            L->first = new;
            new->next = L->curr;
            L->curr->prev = new;
            L->curr = new;
            L->nitems++;
            
        } else {
            //place the node in the place before current in the list
            new->next = L->curr;
            new->prev = L->curr->prev;            
            L->curr->prev->next = new;
            L->curr->prev = new;
            L->curr = new;
            //increases the vealue of nitems
            L->nitems++;
        }
    
    }
}







// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{

	assert(L != NULL); 
    //Creates a new node to be placed in the list
    DLListNode *new = newDLListNode(it);
    

    //if the list empty
    if (L->nitems == 0) {
        L->curr = new;
        L->last = new;
        L->first = new;
        //increases the value of nitems
        L->nitems++;

    } else {
        
        if (L->curr == L->last){
            new->prev = L->last;
            L->last->next = new;
            L->last = new;
            L->curr = new;
            L->nitems++;

        } else {

            new->next = L->curr->next;
            new->prev = L->curr;
            L->curr->next->prev = new;
            L->curr->next = new;
            L->curr = new;
            //increases the value of nitems
            L->nitems++;
        }
    
    }
}






// return number of elements in a list
int DLListLength(DLList L)
{
	return (L->nitems);
}

// is the list empty?
int DLListIsEmpty(DLList L)
{
	return (L->nitems == 0);
}

int Length(DLList L){
    return (L->nitems);

}

char * help(DLList L, int x){

    DLListNode *curr;  
    curr = L->first;
    //printf("The value x is %d \n", x);
    int i = 0; 

    while((curr->next != NULL) && (i < x)){

        curr = curr->next;
        i++; 

    }
    //printf("Return function \n");
    //printf("Returning the value %s \n", curr->value);
    return(curr->value);  
  

}

void printList(DLList L){

    DLListNode *curr;
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
int elementExists (DLList L, char* word){
    DLListNode *curr;
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
            exists++;
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
int elementIsUrl(DLList D, char *oldWord){
    int IsUrl = 0; 
    DLListNode *curr; 
    curr = D->first;
   // char * word = NULL; 

     
    //printf("The old word is %s\n", oldWord);


    if (D->first == NULL){
        if(strcmp(oldWord,D->first->value)==0){
            IsUrl = IsUrl +1;
            //printf(GREEN"WORD IS A URL\n"RESET);
            return IsUrl;
        }
        else {
               // printf("%s IsURL value is %d \n", oldWord, IsUrl);
                
            }

        
    }

    else{


        while(curr != NULL){
        if (strcmp(oldWord, curr->value) == 0){
            // then the word has been found 
            IsUrl++;
            //printf(GREEN"WORD IS A URL \n" RESET);
            return IsUrl;

        }
        else {   
           
                //printf("%s IsURL value is %d \n", oldWord, IsUrl);      
                
            } 

            curr = curr->next;
        }
        
        
        
        
    
    }

    return IsUrl;

}

DLList sort(DLList D){
    DLListNode *curr; 
    curr = D->first; 

    while(curr -> next != NULL){
        
        if (curr->next == NULL){     
            break; 
        } //If theres nothing stop
        else if(strcmp(curr->value,curr->next->value)<0){
            curr = curr->next; 

        }
        else if(strcmp(curr->value, curr->next->value)>0){
            
            //swap them
            curr->prev->next = curr->next; 
            curr->next->next->prev = curr;
            curr->next->prev = curr->prev; 
            curr->next -> next = curr; 
            curr->prev = curr->next; 
            curr->next = curr->next->next;

            curr = curr->next; 

        }
        break;
       printf("%s\n", curr->value);
        printf("Does it get here?\n");
       
    }

   // printList(D);
    return D;
}

char * normalise (char* str){
  int i;
  for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
       str[i]=str[i]+32;
  }
  return str;

}


