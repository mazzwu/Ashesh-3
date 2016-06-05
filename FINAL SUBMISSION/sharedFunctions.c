//
//  sharedFunctions.c
//  Assignment 2
//
//  Created by Winnie Zheng on 5/06/2016.
//  Copyright © 2016 Winnie Z. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "sharedFunctions.h"
//retrieves the size of a file in bytes
off_t fsize(const char *filename) {
    struct stat st;
    
    if (stat(filename, &st) == 0)
        return st.st_size;
    
    return -1;
}
//upper case to lowercase
char * normalize(char *line) {
    
    int i;
    for(i=0;i<=strlen(line);i++){
        if(line[i]>=65&&line[i]<=90) {
            line[i]=line[i]+32;
        }
    }
    
    return line;
}
//remove grammar function - used to normalize in txt files
char * removegrammar (char * str){
    
    int p = 0;
    for(p = 0; p<=(strlen(str));p++){
        if(str[p]=='.' || str[p]==','){
            str[p]='\0';
        }
        
    }
    
    return str;
    
}
