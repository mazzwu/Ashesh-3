//  searchPagerank.h//  Assignment 2 COMP1927//  3 June 2016//  Created by Winnie Zheng && Vivian Bakiris#include <stdio.h>#ifndef SEARCHPAGERANK_H#define SEARCHPAGERANK_H#include <stdio.h>#include <stdlib.h>#include "DLList.h"//function to feed in values from main - argv and argcvoid findPagerank (char *argv[], int argc);//functions called within findPagerank function DLList pageRankL (char *argv[], int argc);off_t fsize(const char *filename);void findPagerank ();char **convert(char *argv[], int argc);DLList compareMatch(DLList a, DLList b);char * removegrammar (char * str);char * normalize(char *line);#endif