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
    char *PR; 

    char *outDegree;
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
    new->PR = 0;
    new->outDegree= 0;
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
          
        char * valueold = strdup(trim(word));
        char * value = normalise(valueold);
        new = newDLListNode(value);

        if (elementExists(L,value) != 0) continue;
        if (elementIsUrl(D, value) != 0) continue;

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
       // printf("After inserting %s, L->nitems = %d \n", value, L->nitems);

    }   
    L->curr = L->first;
    return L;
}

DLList PureAppend(FILE *in, DLList L, DLList D){

    DLListNode *new;
    char word[1000];
    DLListNode *curr;
   // printf("Is it even doing this?\n");
 
    while (fscanf(in,"%s",word) != EOF) {
          
        char * valueold = strdup(trim(word));
        char * value = normalise(valueold);
        char * value2 = removegrammar(value);
        new = newDLListNode(value2);

        if (elementExists(L,value2) != 0) continue;
        //printf("%s does not exist already, proceed \n",value2);
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
       // printf(GREEN"After inserting %s the list looks like \n"RESET,value2);
        //printList(L);

       // printf("After inserting %s, L->nitems = %d \n", value, L->nitems);

    }   
    L->curr = L->first;
    return L;
}

DLList PageRankAppend(FILE *in, DLList L){

    DLListNode *new;
    char word[1000];
    DLListNode *curr;
    DLListNode *lastcalled; 
   // printf("Is it even doing this?\n");
    int counter = 0;
 
    while (fscanf(in,"%s",word) != EOF) {

        counter ++;   
        char * value = strdup(trim(word));
        //char * value = normalise(valueold);
        
        if(counter == 1){
        new = newDLListNode(value);
        lastcalled = new;
        continue; 
        }

        if(counter == 2){
            lastcalled -> outDegree = value;
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
       // printf(GREEN"After inserting %s the list looks like \n"RESET,value2);
        //printList(L);

       // printf("After inserting %s, L->nitems = %d \n", value, L->nitems);

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
    int length = 0;
    DLListNode *curr; 
    curr = L->first;
    while(curr->next != NULL){
        length = length +1;
        curr = curr->next; 
    }
    return (length);

}

int LengthForMalloc(DLList L){
    int length = 1;
    DLListNode *curr; 
    curr = L->first; 
    while(curr->next != NULL){
        length = length +1; 
        curr = curr->next; 
    }
    return(length);
    }

//Given a position in a linked list, the following function
//Returns the value at at that position. 
char * valueReturn(DLList L, int x){

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

    printf("%s %s %s \n",curr->value, curr->outDegree, curr->PR);

    while(curr->next != NULL){
        printf("%s %s %s \n",curr->next->value, curr->next->outDegree, curr->next->PR);
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

        //printf(GREEN"comparing given word %s with current word %s, strcmp value is %d \n"RESET,word,curr->value,(strcmp(word,curr->value)));
        if (strcmp(word, curr->value) == 0){
            // then the word has been found 
            exists = exists + 1;
           // printf("%s has been found\n",word);
            return exists;
        }
        else{         
            // Leave check as is 
           // printf("%s has not been found \n",word);
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


char * normalise (char* str){
  int i;
  for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
       str[i]=str[i]+32;
  }

  return str;
}

char * removegrammar (char * str){
   // printf("The word is %s\n", str);
   // printf("The max value of p is  %lu\n", strlen(str));
  for(int p = 0; p<=(strlen(str));p++){
        if(str[p]=='.' || str[p]==','){
            str[p]='\0';
        }
    
  }

  return str;

}





