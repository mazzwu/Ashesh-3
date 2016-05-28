#include <stdio.h>
#include <stdlib.h>


int initial1, initial2;
int higher;
int lower;

int maxBound (int);
int minBound (int); 


int main(int argc, char *argv[]){

initial1 = 50;
initial2 = 50;
printf("%d\n", initial1);

while (initial2 != 0){
	maxBound(initial1);
	initial1++;
	minBound(initial2);
	initial2--;
}

return EXIT_SUCCESS;
} 

int maxBound (int initial1){
	
	higher = initial1 + 1; 

	printf("%d\n", higher); 

	initial1 = higher; 
	return initial1; 

}

int minBound(int initial2){
	lower = initial2 - 1; 
	printf("%d\n", lower);
	initial2 = lower; 
	return initial2;


}

