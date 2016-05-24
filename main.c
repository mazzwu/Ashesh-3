//
//  main.c
//  Assignment 2
//
//  Created by Winnie Zheng on 24/05/2016.
//  Copyright © 2016 Winnie Z. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "pagerank.h"
#include "list.h"
#include "graph.h"

int main(int argc, char *argv[]) {
    
    List l = newList();
    FILE *f = fopen("collection.txt", "r");
    getCollection(l, f);
    showList(l);
    
    getGraph(l, ListLength(l));
    
    return 0;
}