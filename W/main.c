

#include <stdio.h>
#include <stdlib.h>
#include "pagerank.h"
#include "DLList.h"
#include "prlist.h"
#include "graph.h"
#include "searchPagerank.h"
#include "string.h"
#include "searchTfIdf.h"
#include <math.h>

int main(int argc, char *argv[]) {
    

 

    ///testing pagerank: ///
    
 //  Graph g = getGraph();
    
    
    //PageRank(0.85, 0.00001, 1000);
    
   // DLListPR n = getCollection();
 //   showDLListPR(n);
    
   
    //testing searchpagerank ///
    
  
 //   FILE *inv = fopen("invertedIndex.txt", "r");
 

   // DLList invert = findUrls(inv, argv, argc);
   // showDLList(invert);
  
   
   //printf("DLLIst inver %d\n",DLListLength(invert));
    findPagerank (argv, argc);
    //calculateTfIdf(argc,argv);
    
   
    //testing Search TfIdf:

    //DLList tf =  newDLList();
    //showDLList(tf);
    //calculateTfIdf(tf, argc, argv);
  //  showDLList(t);

   //showDLList(invert);
    
  //  showGraph(g,1);
   // printf("dlistlenght %d\n", DLListLength

   // getGraph(l, DLListLength(l));
  //  showGraph(g,1);
    
    return 0;
}