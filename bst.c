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


DLList CollectionToList(void);
int LengthOfCollection(DLList);
DLList AllWordsToList(int,DLList, DLList);

int main(int argc, char *argv[])
{

	BSTree Q; 
	DLList listOfCollection; 
	DLList AllWords;
	BSTree *ptr;
	//FILE *God;
	DLList WithoutTxt;
	ptr = malloc(sizeof(BSTree) * 1000);

	char * txt = ".txt";
	FILE *f;
	char* urltx = NULL; 
	char * url = NULL; 
	char * URLname;
	//char * Jesus = NULL;
	int N;

	// Open Each URL in the collection and store it in 
	// a linked list, Also find N of URLS in collection. 
	//D =newDLList();
	//FILE *collection = fopen("collection.txt", "r");
	//D= FileAppendDLList(collection,D); 
	//printf(BROWN"Printing the list of the collection\n"RESET);
	//int N = Length(D);
	//fclose(collection);
	//printf("Is it doing anything?\n");
	//printf("Testing if function works");
	
	listOfCollection = CollectionToList(); 
	N = Length(listOfCollection);
	//printList(listOfCollection);




	// Returns all the URLS in the linked list
	// Adds .txt - opens it 
	// and creates an array of BSTS of all the word. 
	for(int i = 0; i < N; i++) {
	url = valueReturn(listOfCollection,i);
	urltx = strcat(url,txt);
	f = fopen(urltx, "r");
	Q = getBSTree(f);
	ptr[i]= Q; 
	fclose(f);
	}

	//printf("Showing bst \n");

	// This function prints all the bsts. 
	/*
	for( int bst = 0; bst < N; bst ++ ){
		showBSTree(ptr[bst]);
		//printf("new tree\n");
	} */

	

	// This is a comparison linked list so that you don't add urls to your 
	// all list 
	// Create a second Linked list of all the URLS in the collection
	// That don't have the .txt 
	// This is the same function as above
	
	WithoutTxt = CollectionToList();
	//WithoutTxt=newDLList();
	//FILE *collection2 = fopen("collection.txt", "r");
	//WithoutTxt= FileAppendDLList(collection2,WithoutTxt); 
	//printf(BROWN"Printing the list of the collection\n"RESET);
	//printList(WithoutTxt);
	//fclose(collection2);
	//printList(listOfCollection);
	//printList(WithoutTxt);

	

	//The following returns all the
	//words in all the urls
	// Creates a linked list of all the words
	
	// Takes in linked list D,
	//printf(BROWN"Just checking this\n"RESET);
	//printList(listOfCollection);


	AllWords = AllWordsToList(N,listOfCollection,WithoutTxt);
	//AllWords = newDLList();
	//for (int hope = 0; hope < N; hope++){
		//Jesus = valueReturn(listOfCollection,hope);
		//God = fopen(Jesus, "r");	
		//AllWords = AlphaAppend(God,AllWords,WithoutTxt);
		
	//}  

	// The following does the same as above just with a better function 

	//DLList testList;
	//testList = newDLList();
	//char *returntext = NULL;
	//FILE *urlOpen;

	//for (int jk = 0; jk < N; jk++){
		//printf("Does it do this?\n");
		//returntext = valueReturn(listOfCollection,jk);
		//urlOpen = fopen(returntext, "r");	
		//testList = PureAppend(urlOpen,testList,WithoutTxt);
		
//	}  

	//printf(GREEN"PRINTING NEW APPEND\n"RESET);
	//printList(testList);





	 
	//printList(All);

	// This is where you get the inverted index 
	
	char * searchTerm; 
	searchTerm = (char *)malloc(3);
	int found;
	int numberofWords = Length(AllWords); 
	//printf("The number of words is %d\n",numberofWords);
	FILE *Inverted = fopen("Inverted.txt","w");

	
	for (int test = 0; test <= numberofWords; test++){

		searchTerm= valueReturn(AllWords, test);
		fprintf(Inverted, "%s",searchTerm);

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
   
   		fprintf(Inverted,"\n");

 	}


	return EXIT_SUCCESS;
}




DLList CollectionToList(void){
	DLList D;
	D =newDLList();
	FILE *collection = fopen("collection.txt", "r");
	D= FileAppendDLList(collection,D);
	fclose(collection);
	return D;
}

int LengthOfCollection(DLList D){
	int N = Length(D);
	return N;
}

DLList AllWordsToList(int N,DLList listOfCollection, DLList WithoutTxt){
	DLList AllWords;
	AllWords = newDLList();
	for (int hope = 0; hope < N; hope++){
		char *UrlWithT = valueReturn(listOfCollection,hope);
		FILE *urlFile = fopen(UrlWithT, "r");	
		AllWords = PureAppend(urlFile,AllWords,WithoutTxt);	
	}  

	return AllWords;
}
