//
//  searchTfIdf.c
//  Assignment 2 COMP1927
// 3 June 2016
//  Created by Winnie Zheng && Vivian Bakiris
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "searchTfIdf.h"
#include "prlist.h"
#include "searchPagerank.h"
#include "pagerank.h"
#include "sharedFunctions.h"
#include <math.h>
#include <sys/stat.h>
#include <errno.h>


//calculates tfIDF - needs to be called by main -  taking in argc and argv arguments.
void calculateTfIdf(int argc, char *argv[]){
    if(argc == 1) {
        printf("nothing in command line \n");
        return;
    }
    
    FILE *f = fopen("invertedIndex.txt", "r");
    DLList urlFormat = tFData(argv, argc, 1);
    
    if(DLListLength(urlFormat) == 0) { //empty list case.
       // printf("m8 none of these words share the same url ay\n");
        return;
    }
    
    else {
        
        //REMOVE .txt from LIST string urls.
        
        DLList urlList = pageRankL(argv, argc);
        DLListNode *temp = newDLListNode(urlFormat->first->data);
        temp = urlFormat->first;
        DLListNode *temp2 = newDLListNode(urlList->first->data);
        temp2 = urlList->first;
        while(temp != NULL && temp2 != NULL) {
            temp->data = temp2->data;
            temp = temp->next;
            temp2 = temp2->next;
        }
        fclose(f);
    }
    
    //calculate Tf: iterate through every URl and calculate their tf - frequency of word occuring in current doc= curr->wordFreq for each curr
    
    DLList tfD = tFData(argv, argc, 1);
    double * tfIdf = malloc(100000000* sizeof(double *)); //used to store tfidf values
    DLListNode *curr = newDLListNode(urlFormat->first->data);
    DLListNode *curr2 = newDLListNode(tfD->first->data);
    curr = urlFormat->first;
    curr2 = tfD->first;
    
    double N = (double)numUrls(); //get our TOTAL num Documents/urls in our colleciton
    int i = 1;
    double tf  = 0;
    double idf = 0;
    int x = 1;
    int n = 2;
    int duplicateRemover = argc-1;
    double totalF = 0;
    
 /** code below removes repated command line inputs into calculations **/
    char *checkRepeatedWords = calloc(argc-1, sizeof(char *));
    int y = 1;
    while(y < argc) {
        checkRepeatedWords[y] = 1;
        y++;
        }
       while(x < argc) {
           n = argc-1;
           while(n != 0) {
               if(x != n && n != argc-1 && strcmp(argv[x],argv[n])== 0) {
                   if(checkRepeatedWords[n] == 1) {
                   checkRepeatedWords[x] +=i;
                   }
               }
               n--;
               
           }
           if(checkRepeatedWords[x] != 1) {
               duplicateRemover--;
           }
           x++;
       }
    
    
    x = 1;
    i = 0;
    printf("duplicate %d\n", duplicateRemover);
    //urls first -> break it down to EACH word by calling tfData function (incrementing x) -> for each word, store TF value
    while(curr != NULL) { // we want to traverse through ALL urls that contain our query term
        x = 1;
        while(x < argc) { //where x++ will iterate through to the next word - must start at 1 because of argv
            if(checkRepeatedWords[x] == 1) { //we don't want to calculate repeated words on command line
            tfD = tFData(argv, argc, x);
            tf = (double)curr2->wordFreq; //store tF value of current URL.
            if(totalFreqWord(argv[x],1) == 0) {
                break;
            }
            totalF = totalFreqWord(argv[x],1);
            idf =log10(N/totalF);
            tfIdf[i] += idf *tf; //each ith URL
          //  printf("%s %lf %lf %lf %lf\n", curr->data, tfIdf[i], idf, totalF, tf);
             //iterate through to the next word.
            
            }
           
            x++;
        }
        //print out our TFIDF RANK for each url to stdout
        printf("%s %lf\n", curr->data, tfIdf[i]);
        curr = curr->next; //iterate through to the next URL
        
        i++;
    }
}


//this function takes in argv and argc files - which will find its values when called in totalFreq
DLList findUrlsForfreq (char *argv[], int argc) {


    if(argc == 0) {
        printf("nothing in command line ...\n");
        return 0;
    }
    if(argc != 1) {
        argc = argc-1;
    }
  
    DLList matchedUrls = newDLList();
    FILE* f=fopen("invertedIndex.txt", "r");
   //counter variables
    int count = 0;
    int j = 1;
    int k = 0;
    int x = 1;
    
    char * urls = malloc(fsize("invertedIndex.txt")); //array used to scan through file

    int test[argc];
    
    //checks for existence of words entered in command line//
      while(count < argc) {
        k = 0;
        while (fscanf(f,"%s", &urls[k]) != EOF) { //read through the file till the END of file
            removegrammar(*argv);
            normalize(*argv);
            if((strcmp(*argv, &urls[k]) == 0)) { //if we've found our search word
                test[j] = 0;
                break;
            }
            else {
                test[j] = 1;
            }
            k++;
        }
        count++;
        j++;
        
        fclose(f);
    }
    
    j = 0;
    
    while(j < argc) {
        if(test[j] == 1) {
            printf("no urls matching all search words\n");
            return 0;
        }
        j++;
    }
    
    
    //if all our words entered on command line exist... proceed:
    count = 0;
    
    x = 1;
    fclose(f); //after test scan is done! close file..
    

    int c = 0;
    int done = 0;
       while(count < argc) { //loop to go through each search word in the search
        f = fopen("invertedIndex.txt", "r");
       //rest counters
        k = 0;
        c = 0;
        //delete all elements from old tempUrl list to replace by new word url list
        
        DLList tempUrls = newDLList();
       
        done = 0;
        
        while (fscanf(f,"%s", &urls[k]) != EOF && done == 0) { //read through the file till the END of file
            
            normalize(*argv);
            removegrammar(*argv);
            
            if((strcmp(*argv, &urls[k]) == 0)) { //if we've found our search word
                
                while(fgets(&urls[k], 100, f) != NULL && done == 0) {//keep scaning through the urls to add in the list UNTIL we
                    char * cpy = strchr(&urls[k], ' '); //take the line of urls corresponding our word
                    char *ptr = cpy;
                    char *splitS;
               
                    while(ptr != NULL && done == 0) { //split our string to store all urls associated with our word
                        splitS= strsep(&ptr, " ");
                        
                        if(splitS[strlen(splitS)-1] == '\n') {
                            splitS[strlen(splitS)-1] = '\0';
                            
                        }
                        
                        if(count == 0 && c != 0) { //for single query word cases
                            DLListAfter(matchedUrls, splitS);
          
                        }
                        else if(count > 0 && c!= 0) { //more than one query word entered
                            DLListAfter(tempUrls, splitS);
                      
                        }
                        c++;
                        if(ptr == NULL ) {
                            
                            done = 1;
                            break;
                        }
                        
                    }
                    
                }
            }
            k++;
            
        }
        //compare and match for more than one query term
        if(count > 0) {
             matchedUrls = compareMatch(matchedUrls, tempUrls); //call matchedUrls -> a function which compares and matches common urls shared by all query terms
        }

        x++;
        count++;

        fclose(f);
        free(urls);
    }
    
 //empty list case
    if(DLListLength(matchedUrls) == 0) {
        printf("no matching urls for ya search words m8\n");
        return NULL;
    }
 
    
    return matchedUrls; //return our matching url list
}

//iterates through ALL files assocaited with EACH query word and returns the total frequency of this
int totalFreqWord (char *word, int numQueryTerms) { 
    
    if(numQueryTerms == 0) {
        printf("nothing in command line lel\n");
        return 0;
    }

    DLList tfD = newDLList();
    
    
  
    char *txt = ".txt"; //to append at the end of matchingUrl list
   
    //counter variables;
    int j = 0;
    int k = 0;
    int i = 1;
    int y = 0;
    int count = 0;
    int open = 0;
    int totalCounter = 0;
    int empty = 0; //once we've found our total freq, set empty to 1
    while(j < 1 && empty == 0) { //we need to go through EVERY query term
        //for each query term, we need to find the urls which contain this query term. - we will reset this this for every word
        if(findUrlsForfreq(&word, numQueryTerms) == NULL){ //find all URLS that contain our current query word
            empty = 1;
            break;
        }
        tfD = findUrlsForfreq(&word, numQueryTerms);// matchingUrlPages(inv, argv[i]);
        DLListNode * curr =  tfD->first;
        curr->numDocs = DLListLength(tfD); //store the total number  of URLS found
        DLListNode *tempUrl = newDLListNode(tfD->first->data);

        y = 0;
        while(DLListLength(tfD) > y) { //open ALL existing urls.
            tempUrl->data = curr->data;
            strcat(tempUrl->data, txt);
            FILE *f = fopen(tempUrl->data, "r"); //open each txt file
            open = 1;
            char * urls = malloc(fsize("invertedIndex.txt"));
            k = 0;
             totalCounter = 0;
            while(fscanf(f,"%s", &urls[k]) != EOF && open == 1) { //loop through each text file to look and count the frequency for each query term
                normalize(&urls[k]);
                removegrammar(&urls[k]);
                if(strcmp(word, &urls[k]) == 0) { //once we've found our word... increase our totalCounter :)
             
                    totalCounter = 1;
                    
                }
               
                k++;
            }
            
            fclose(f);
            y++;
            i++;
            curr = curr->next;
            open = 0;
            if(totalCounter == 1) {
                tfD->first->totalFreq = count+1;
                count++;
               
            }
        }
      
        
        
        j++;
    }
    if(empty == 1) {
        return 0;
    }
    
    return tfD->first->totalFreq;
}

//this function takes in all the urls associated with all query terms(urls in common) and counts the individual frequency of each query term per file - all
DLList tFData (char *argv[], int numQueryTerms, int p) { //p is used as a counter for iterating through single words and finding their frequency in a particular file
    
    if(numQueryTerms == 0) {
        printf("nothing in command line lel\n");
        return 0;
    }
    numQueryTerms = numQueryTerms-1; //argc values - 1

    DLList tfD = newDLList();
   
    char *txt = ".txt";
    
    //counter variables;
    int j = 0;
    int k = 0;
    int i = 1;
    int y = 0;
    int count = 0;
    int open = 0;
    int x = 1;
    
    int empty = 0;
    while(j < p && empty == 0) { //we need to go through EVERY query term
        //for each query term, we need to find the urls which contain this query term. - we will reset this this for every word
        if(pageRankL(argv, numQueryTerms+1) == NULL){ //find all URLS that contain our current query word
            empty = 1;
            break;
        }
     
        tfD = pageRankL(argv,numQueryTerms+1);
         DLListNode * curr =  tfD->first;
        curr->numDocs = DLListLength(tfD); //store the total number  of URLS found
        
        DLListNode *tempUrl = newDLListNode(tfD->first->data);
     
        y = 0;
      
        while(DLListLength(tfD) > y) { //open ALL existing urls.
            tempUrl->data = curr->data;
            strcat(tempUrl->data, txt);
            FILE * f = fopen(tempUrl->data, "r"); //open each txt file
            open = 1;
            char * urls = malloc(fsize("invertedIndex.txt"));
            k = 0;
                while(fscanf(f,"%s", &urls[k]) != EOF && open == 1) { //loop through each text file to look and count the frequency for each query term
                    normalize(&urls[k]);
                    removegrammar(&urls[k]);
                    if(strcmp(argv[x], &urls[k]) == 0) { //if we've found our matching word..
                        curr->wordFreq = curr->wordFreq+1; //increase the word freq counter
                        count++;
                    }
                    k++;
                }
            
            fclose(f);
            y++;
            i++;
     
            curr = curr->next; //iterate to the next FILE
            open = 0;
        }

        j++;
      x++;
    }

    return tfD;
}




