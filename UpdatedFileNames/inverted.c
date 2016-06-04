//Inverted.c 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "BSTree.h"
#include "List.h"
#include "Inverted.h"

#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"

	BSTree Q; 
	BSTree *ptr;
	List listOfCollection; 
	List AllWords;
	List WithoutTxt;
	FILE *f;
	FILE *sizefile;

	int found;
	int N;
	int size;
	char * txt = ".txt";
	char * urltx = NULL; 
	char * url = NULL; 
	char * URLname = NULL;
	char * searchTerm = NULL; 
	


void InvertedIndex(void){

    listOfCollection = CollectionToList(); 
	N = Length(listOfCollection);
	int L = LengthForMalloc(listOfCollection);

	ptr = malloc(sizeof(BSTree) * L);

	for(int i = 0; i < N; i++) {
	url = valueReturn(listOfCollection,i);
	urltx = strcat(url,txt);
	f = fopen(urltx, "r");
	sizefile = fopen(urltx, "r");
	size = sizeOfFile(sizefile);
	Q = getBSTree(f,size);
	ptr[i]= Q; 
	fclose(f);
	fclose(sizefile);
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

List CollectionToList(void){
	List D;
	D =newList();
	FILE *collection = fopen("collection.txt", "r");
	D= FileAppendList(collection,D);
	fclose(collection);
	return D;
}

int LengthOfCollection(List D){
	int N = Length(D);
	return N;
}

List AllWordsToList(int N,List listOfCollection, List WithoutTxt){
	List AllWords;
	AllWords = newList();
	for (int hope = 0; hope < N; hope++){
		char *UrlWithT = valueReturn(listOfCollection,hope);
		FILE *urlFile = fopen(UrlWithT, "r");	
		AllWords = PureAppend(urlFile,AllWords,WithoutTxt);	
	}  

	return AllWords;
}

	

	
	