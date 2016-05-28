// checking scanf

#include <stdio.h> 
#include <stdlib.h>
#include <strings.h>
#include <assert.h>


int main(int argc, char *argv[]){

	//char word [100000]; 
	//int n = 50;
	//int v = 0;
	/* int i = 0;

	char **strings = (char**)malloc(n*sizeof(char*));

	for(i = 0; i < n; i++){
		strings[i]="hey";
	}

	for(int k = 0; k<n; k++){
		printf("%s", strings[k]);
	}

*/ 

/* 
	printf("Opening URL 11 \n");

	FILE *urlFILE = fopen("url11.txt", "r");
	
	while (fscanf(urlFILE, "%s", word)!= EOF){
		char * value = word; 
		printf("The word is %s \n", value);
	}
	*/ 
	

	// Lets try combining 
	//char **please = (char**)malloc(n*sizeof(char*));
	//char **work = (char**)malloc(n*sizeof(char*));

	char *sobs[1000];

	FILE *urlFILE = fopen("url11.txt", "r");
	//int i = 0;

	for(int i= 0; i<1000; i++){
		sobs[i] = malloc(1000*sizeof(char));
		fscanf(urlFILE, "%s", sobs[i]);
	}

	/* while(fscanf(urlFILE, "%s", word)!=EOF){
		
		printf("The word is %s \n", word);
		please[i]= word;
		printf("The array says %s \n ", please[v]);
		
		 		 i++;
	    
	}

*/  
	for(int i=0; i<50; i++){
		printf("The %dth word is %s \n",i, sobs[i]);
	}

	fclose(urlFILE);
	




	return EXIT_SUCCESS; 
}