// bst.c ... client for BSTree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include "BSTree.h"
#include "DLList.h"

//#define MAXVALS 1000

#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"

//char * makearray(FILE *f, int N, char * alan[]);

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
	// a linked list, Also fine\d N of URLS in collection. 
	D =newDLList();
	FILE *collection = fopen("collection.txt", "r");
	D= FileAppendDLList(collection,D); 
	printf(BROWN"Printing the list of the collection\n"RESET);
	//printList(D);
	int N = Length(D);
	//printList(D);
	fclose(collection);


	// Returns all the URLS in the linked list
	// Adds .txt - opens it 
	// and creates an array of BSTS of all the word. 
	for(int i = 0; i < N; i++) {
	helplease = help(D,i);
	url = strcat(helplease,txt);
	f = fopen(url, "r");
	Q = getBSTree(f);
	ptr[i]= Q; 
	fclose(f);
	}

	// Create a second Linked list of all the URLS in the collection
	// That don't have the .txt 
	WithoutTxt=newDLList();
	FILE *collection2 = fopen("collection.txt", "r");
	WithoutTxt= FileAppendDLList(collection2,WithoutTxt); 
	printf(BROWN"Printing the list of the collection\n"RESET);
	printList(WithoutTxt);
	fclose(collection);

	

	//The following returns all the
	//words in all the urls
	// Creates a linked list of all the words
	// 
	All = newDLList();
	//Alpha = newDLList();
	// Takes in linked list D,
	printf(BROWN"Just checking this\n"RESET);
	printList(D);
	for (int hope = 0; hope < N; hope++){
		Jesus = help(D,hope);
		//printf("The value of Jesus is %s\n", Jesus);
		God = fopen(Jesus, "r");
		//printList(D);
		All = AlphaAppend(God,All,WithoutTxt);
		
		//Alpha =AlphaAppend(God,Alpha,WithoutTxt);;

	}  

	printf("Finishes All\n");
	
	//Alpha=FileAppendDLList3(God,All,WithoutTxt);;
	//printf("Testing if it works\n");
	printf("PRINTING ORIGINAL\n");
	//printList(All);

	printf("Try sorting now\n");
	/*char *urlname;

	for (int iteration = 0; iteration < N; iteration++){
		urlname = help(D,iteration);
		printf("The value of the urlname is %s\n", Jesus);
		God = fopen(urlname, "r");
		Alpha =AlphaAppend(God,Alpha,WithoutTxt);;
		printf("Is it running there?\n");
	}  
	printf("Supposed to be sorted\n");
	printList(Alpha);
	*/ 

	// Then we need to take in each as a search term


	
	
	char * searchTerm; 
	searchTerm = (char *)malloc(3);
	int found;
	int numberofWords = Length(All)- 5; 
	FILE *Inverted = fopen("In.txt","w");

	
	for (int test = 0; test <= numberofWords; test++){

		searchTerm= help(All, test);
		fprintf(Inverted, "\n%s",searchTerm);

		for(int iterator = 0; iterator <= N; iterator++){	
		// Set the search term as the term returned by ALL	
		found = BSTreeFind(ptr[iterator],searchTerm);

		if(found == 1){
			URLname = help(WithoutTxt, iterator);
			fprintf(Inverted," %s", URLname);
		}
		else{
		//printf("%s was not found in the BST in arrayIndex[%d]\n", searchTerm, iterator);
		}
	
   		}
   
   		printf("\n");

 	}



	//while(fscanf(f,"%s", string) !=EOF){
	//	printf("%s \n", string);
	//} 
	 /* for (int i = 1; i<N; i++){
		// Maybe make a get l->current data function 
		// you need to open each URL file one at a time 
	 	printf("why\n");
	 	strcpy(fuckyou, help(D,i));
	 	printf(" the string is %s\n", fuckyou);
	 	printf("i hate you \n");
		urlTxt = strcat(fuckyou, txt); 
		printf("this is weird");
		f = fopen(urlTxt, "r");
		T = getBSTree(f);
	} 

*/ 




	//FILE *urlFILE = fopen("url11.txt", "r");
	//T = getBSTree(urlFILE);
	//showBSTree(T);
	//treeTraverse(T);
	

	//fclose(urlFILE);

	/* 

	f = fopen("url11.txt", "r");
	
    char * alan[N];
    //char * lols = NULL;
  
    alan[N]=makearray(f,N,alan);


    for (int q = 0; q<= N; q++){
    	printf("The value in the array is %s\n",alan[q]);
    }
	*/

	/* printf("Please type maybe?\n");
	int yo;
	scanf("%d", &yo);
	printf("Thanks! for typing in %d \n", yo); */ 
	return EXIT_SUCCESS;
}
/* 
char * makearray(FILE *f, int N, char * alan[]){

	
	char lols[12323];
	for (int i = 0; i<N; i++){
		alan[i]= malloc(1000*sizeof(char));
		fscanf(f, "%s", lols);
		printf("%s\n", lols);
		//printf(" in d function %s\n", lols);

	}

	return *(alan);
}

*/ 
