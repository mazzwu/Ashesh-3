#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  FILE *col = fopen("collection.txt", "r")
	 
	
  FILE *url= fopen("url11.txt", "r");
  char string[10000];


    while(fscanf(url, "%s", string) !=EOF && strcmp(string,"#end")!= 0){
    	if((strcmp(string,"#start")!=0) && (strcmp(string,"Section-1") !=0)){

    		 printf("%s\n",string);
    	}
    
    }
    
  fclose(col);
    
    return 0; 

}
