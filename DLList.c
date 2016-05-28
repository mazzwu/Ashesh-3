// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015
// Modified by Vivian Bakiris and Jacob Sturges 2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

// data structures representing DLList

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer previous node in list
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

// display items from a DLList, one per line
void showDLList(FILE *out, DLList L)
{
	assert(out != NULL); assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
		fprintf(out,"%s\n",curr->value);
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
			fprintf(stderr, "Invalid forward link into node (%s)\n",curr->value);
			return 0;
		}
		if (curr->next != NULL && curr->next->prev != curr) {
			fprintf(stderr, "Invalid backward link into node (%s)\n",curr->value);
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











//this function still needs work
// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList L)
{
	assert (L != NULL);
    DLListNode *marker;

    if (L->nitems == 0) {
       //do nothing

    } else if (L->nitems == 1) {

        free(L->curr->value);
        free(L->curr);
        L->curr = NULL;
        L->first = NULL;
        L->last = NULL;     
        L->nitems--;

    } else if (L->curr == L->first) {

        L->first->next->prev = NULL;
        L->first = L->curr->next;
        marker = L->curr;
        L->curr = L->curr->next;
        free(marker->value);
        free(marker);        

        L->nitems--;
        

    } else if (L->curr == L->last) {

        L->last = L->last->prev;
        L->last->next = NULL;
        marker = L->curr;
        L->curr = L->last;

        free(marker->value);
        free(marker);
        L->nitems--; 

    } else {


        L->curr->prev->next = L->curr->next;
        L->curr->next->prev = L->curr->prev;
        marker = L->curr;
        L->curr = L->curr->next;
        free(marker->value);
        free(marker);   
        L->nitems--;


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





//function which tests the before function
int testBefore() {

    int status = 0;

    DLList l = newDLList();
    //adds a new item to the list "ab"
    DLListBefore(l,"ab");

    //test all links from the list itself
    if (strcmp(l->curr->value,"ab") != 0 || strcmp(l->first->value,"ab") != 0 || strcmp(l->last->value,"ab") != 0) {

        status = 1;

    }

    // check the pointers

    if(l->last->next != NULL || l->first->prev != NULL){
        status = 1;
    }



    //adds new item to the front of the list (special case where new item is at the front of the list)
    DLListBefore(l,"bc");

    //test all links from the list itself
    if (strcmp(l->curr->value,"bc") != 0 || strcmp(l->first->value,"bc") != 0 ||strcmp(l->last->value,"ab") != 0){

        status = 1;

    }

    //tests all links between the nodes
    if (strcmp(l->curr->next->value,"ab") != 0 || strcmp(l->last->prev->value,"bc") != 0) {

        status = 1;

    }

    // testing the pointers 

    if (l->curr->prev != NULL || l->last->next != NULL){
        status = 1;
    }

    if (l->curr->next!= l->last || l->last->prev != l->curr){
        status = 1;
    }
    
    //adds new item "cd" to the middle of the list
    l->curr = l->curr->next;

    DLListBefore(l,"cd");


    //test all links from the list itself
    if (strcmp(l->curr->value,"cd") != 0 || strcmp(l->first->value,"bc") != 0 ||strcmp(l->last->value,"ab") != 0){

        status = 1;

    }
    //tests all links between the nodes
    if (strcmp(l->curr->next->value,"ab") != 0 || strcmp(l->curr->prev->value,"bc") != 0){
        status = 1; 
    }

    if (strcmp(l->first->next->value,"cd") != 0 || strcmp(l->last->prev->value, "cd") != 0) {

        status = 1;

    }

    // testing pointers 
   
    if(l->first->prev != NULL || l->last-> next != NULL){
        status = 1;
    }


return status;
}

//function which test the after fucntion
int testAfter() {

    int status = 0;

    DLList l = newDLList();


    //Add another item "ab" to the list. (tests special case of empty list)
    DLListAfter(l,"ab");

    //test all links from the list itself
    if (strcmp(l->curr->value,"ab") != 0 || strcmp(l->first->value,"ab") != 0) {

        status = 1;

    }

    if(strcmp(l->last->value,"ab") != 0) {
        status = 1;
    }
    // testing pointers 

    if (l->first->prev != NULL || l->last-> next != NULL){
        status = 1;
    }
    
    
    //add another item "bc" at the end of the list (test the append special case)
    DLListAfter(l,"bc");

    //test all links from the list itself
    if (strcmp(l->curr->value,"bc") != 0 || strcmp(l->first->value,"ab") != 0 || strcmp(l->last->value,"bc") != 0) {

        status = 1;

    }
    //tests all links between nodes
    if (strcmp(l->curr->prev->value,"ab") != 0 || strcmp(l->first->next->value,"bc") != 0) {

        status = 1;

    }

    // testing pointers 
      
    if (l->first->prev != NULL || l->last-> next != NULL){
        status = 1;
    }


    //add another item "cd" between two items (checks the case of placing in a list)

    l->curr = l->curr->prev;

    DLListAfter(l,"cd");

     
    //test all links from the list itself
    if (strcmp(l->curr->value,"cd") != 0 || strcmp(l->first->value,"ab") != 0 || strcmp(l->last->value,"bc") != 0) {

        status = 1;

    }

    //tests all links between the nodes
    if (strcmp(l->curr->next->value,"bc") != 0 || strcmp(l->curr->prev->value,"ab") != 0 ) {

        status = 1;
    }
    if (strcmp(l->first->next->value,"cd") != 0 || strcmp(l->last->prev->value, "cd") != 0){
        status = 1;
    }
    // testing pointers 
    if (l->first->prev != NULL || l->last-> next != NULL){
        status = 1;
    }
return status;

}

// function which tests the delete function 

int testDelete(){
    int status = 0; 

    DLList l = newDLList();
    // test the empty list 
    DLListDelete(l);

    // checking values 
    if (l->curr->value != NULL || l->first->value != NULL || l->last->value != NULL) {

        status = 1;
    }
    // checking pointers 
    if(l->curr->next != NULL || l->curr->prev != NULL){
        status = 1;
    }


    // creating the first node 
    DLListAfter(l,"ab");

    // test the list with one node

    DLListDelete(l);

    // checking values 
     if (l->curr->value != NULL || l->first->value != NULL || l->last->value != NULL) {

        status = 1;
    }
    // checking pointers 
    if(l->curr->next != NULL || l->curr->prev != NULL){
        status = 1;
    }

    // adding a second node to the list.
    DLListAfter(l,"ab");
    DLListBefore(l,"cd");
    DLListDelete(l);

    // test when first item is deleted. // DLListBefore places "cd" as the first value. It should be deleted. 

    if(l->curr->next != NULL || l->curr->prev != NULL){
        status = 1;
    }

    if(strcmp(l->first->value,"ab")!= 0 || strcmp(l->last->value,"ab") != 0 || strcmp(l->curr->value,"ab") != 0){
        status = 1; 
    }


    DLListAfter(l,"de");
    DLListDelete(l);
    // test when the last item is deleted. //DLListAfter places "de" as the last value. It should be deleted.

    if(l->curr->next != NULL || l->curr->prev != NULL){
        status = 1;
    }

    if(strcmp(l->first->value,"ab")!= 0 || strcmp(l->last->value,"ab") != 0){
        status = 1; 
    }
    if(strcmp(l->curr->value,"ab") != 0){
        status = 1; 
    }

    // Now we must test if its somewhere in the middle 
    DLListAfter(l,"hi");
    DLListBefore(l,"bye");
    DLListDelete(l);

    // testing null pointers 
    if( l->last->next != NULL || l-> first -> prev != NULL || l->curr->next != NULL){
        status = 1;
    }

    // testing values 
    if (strcmp(l->first->value,"ab") != 0 || strcmp(l->last->value,"hi") != 0 || strcmp(l->curr->value,"hi")!= 0){
        status = 1;
    }

    // testing pointer values 

    if(strcmp(l->first->next->value,"hi") != 0 || strcmp(l->last->prev->value, "ab") != 0){
        status = 1;
    }

    // testing pointer values 

    if ( strcmp(l->curr->prev->value, "ab") != 0){
        status = 1;
    }


    return status; 



}