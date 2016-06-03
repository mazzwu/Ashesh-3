//Inverted.c 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "BSTree.h"
#include "DLList.h"
#include "Inverted.h"

#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"



void InvertedIndex(void){
	BSTree Q; 
	DLList listOfCollection; 
	DLList AllWords;
	BSTree *ptr;
	DLList WithoutTxt;
	

	char * txt = ".txt";
	FILE *f;
	char* urltx = NULL; 
	char * url = NULL; 
	char * URLname;
	int N;
	char * searchTerm; 
	searchTerm = (char *)malloc(3);
	int found;

    listOfCollection = CollectionToList(); 
	N = Length(listOfCollection);
	int L = LengthForMalloc(listOfCollection);

	ptr = malloc(sizeof(BSTree) * L);

	for(int i = 0; i < N; i++) {
	url = valueReturn(listOfCollection,i);
	urltx = strcat(url,txt);
	f = fopen(urltx, "r");
	Q = getBSTree(f);
	ptr[i]= Q; 
	fclose(f);
	}

	WithoutTxt = CollectionToList();

	AllWords = AllWordsToList(N,listOfCollection,WithoutTxt);

	int numberofWords = Length(AllWords); 


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
		// Do nothing 
		}
	
   		}
   
   		fprintf(Inverted,"\n");

 	}

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

	

	
	