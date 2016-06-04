//
//  searchTfIdf.h
//  Assignment 2 COMP1927
// 3 June 2016
//  Created by Winnie Zheng && Vivian Bakiris
#ifndef searchTfIdf_h
#define searchTfIdf_h

#include <stdio.h>
#include "DLList.h"
#include "searchPagerank.h"


//needs to be called by MAIN - takes in argc and argv values
void calculateTfIdf(int argc, char *argv[]);

//all functions below are called within searchtiFiDc
DLList findUrlsForfreq (char *argv[], int argc);
int totalFreqWord (char *word, int numQueryTerms);
DLList tFData (char *argv[], int numQueryTerms, int p); 


#endif /* searchTfIdf_h */
