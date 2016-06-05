//  inverted.c 
//  Assignment 2 COMP1927
//  June 2016
//  Created by Winnie Zheng && Vivian Bakiris
//Inverted.c

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "BSTree.h"
#include "List.h"
#include "Inverted.h"

BSTree Q;
BSTree *ptr;
List listOfCollection;
List AllWords;
List WithoutTxt;
FILE *f;
FILE *sizefile;

int found = 0;
int N = 0;
int size = 0;
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
    int i = 0;
    for(i = 0; i < N; i++) {
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
    
    
    FILE *Inverted = fopen("invertedIndex.txt","w");
    
    int test = 0;
    int iterator = 0;
    for (test = 0; test <= numberofWords; test++){
        
        searchTerm= valueReturn(AllWords, test);
        fprintf(Inverted, "%s",searchTerm);
        
        for(iterator = 0; iterator <= N; iterator++){
            // Set the search term as the term returned by ALL
            found = BSTreeFind(ptr[iterator],searchTerm);
            
            if(found == 1){
                URLname = valueReturn(WithoutTxt, iterator);
                fprintf(Inverted," %s", URLname);
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
    int x = 0;
    for (x = 0; x < N; x++){
        char *UrlWithT = valueReturn(listOfCollection,x);
        FILE *urlFile = fopen(UrlWithT, "r");	
        AllWords = PureAppend(urlFile,AllWords,WithoutTxt);	
    }  
    
    return AllWords;
}




