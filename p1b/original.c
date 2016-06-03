// InvertedIndex.c

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include "BSTree.h"
#include "DLList.h"
#include "Inverted.h"


#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"



int main(int argc, char *argv[])
{

	BSTree Q; 
	DLList D; 
	DLList All;
	BSTree *ptr;
	FILE *God;
	DLList WithoutTxt;
	ptr = malloc(sizeof(BSTree) * 1000);

	char * txt = ".txt";
	FILE *f;
	char* url = NULL; 
	char * helplease = NULL; 
	char * URLname;
	char * Jesus = NULL;

	// Open Each URL in the collection and store it in 
	// a linked list, Also find N of URLS in collection. 
	D =newDLList();
	FILE *collection = fopen("collection.txt", "r");
	D= FileAppendDLList(collection,D); 
	//printf(BROWN"Printing the list of the collection\n"RESET);
	int N = Length(D);
	fclose(collection);



	// Returns all the URLS in the linked list
	// Adds .txt - opens it 
	// and creates an array of BSTS of all the word. 
	for(int i = 0; i < N; i++) {
	helplease = valueReturn(D,i);
	url = strcat(helplease,txt);
	f = fopen(url, "r");
	Q = getBSTree(f);
	ptr[i]= Q; 
	fclose(f);
	}

	//printf("Showing bst \n");

	// This function prints all the bsts. 
	
	for( int bst = 0; bst < N; bst ++ ){
		showBSTree(ptr[bst]);
		//printf("new tree\n");
	}

	

	// This is a comparison linked list so that you don't add urls to your 
	// all list 
	// Create a second Linked list of all the URLS in the collection
	// That don't have the .txt 
	// This is the same function as above
	WithoutTxt=newDLList();
	FILE *collection2 = fopen("collection.txt", "r");
	WithoutTxt= FileAppendDLList(collection2,WithoutTxt); 
	//printf(BROWN"Printing the list of the collection\n"RESET);
	//printList(WithoutTxt);
	fclose(collection);

	

	//The following returns all the
	//words in all the urls
	// Creates a linked list of all the words
	All = newDLList();
	// Takes in linked list D,
	//printf(BROWN"Just checking this\n"RESET);
	printList(D);
	for (int hope = 0; hope < N; hope++){
		Jesus = valueReturn(D,hope);
		God = fopen(Jesus, "r");	
		All = AlphaAppend(God,All,WithoutTxt);
		
	}  

	// The following does the same as above just with a better function 

	DLList testList;
	testList = newDLList();
	char *returntext = NULL;
	FILE *urlOpen;

	for (int jk = 0; jk < N; jk++){
		//printf("Does it do this?\n");
		returntext = valueReturn(D,jk);
		urlOpen = fopen(returntext, "r");	
		testList = what(urlOpen,testList,WithoutTxt);
		
	}  

	printf(GREEN"PRINTING NEW APPEND\n"RESET);
	printList(testList);





	 
	printList(All);

	// This is where you get the inverted index 
	
	char * searchTerm; 
	searchTerm = (char *)malloc(3);
	int found;
	int numberofWords = Length(All); 
	//printf("The number of words is %d\n",numberofWords);
	FILE *Inverted = fopen("In.txt","w");

	
	for (int test = 0; test <= numberofWords; test++){

		searchTerm= valueReturn(All, test);
		fprintf(Inverted, "\n %d: %s",test,searchTerm);

		for(int iterator = 0; iterator <= N; iterator++){	
		// Set the search term as the term returned by ALL	
		found = BSTreeFind(ptr[iterator],searchTerm);

		if(found == 1){
			URLname = valueReturn(WithoutTxt, iterator);
			fprintf(Inverted," %s", URLname);
		}
		else{
		//printf("%s was not found in the BST in arrayIndex[%d]\n", searchTerm, iterator);
		}
	
   		}
   
   		printf("\n");

 	}


	return EXIT_SUCCESS;
}

