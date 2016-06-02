//scaledFootrule.c




// The following function calculates the cardinality of the union of 
// T1 and T2 
int cardinalityofS (DLList x, DLList y){
	int xLength = Length(x);
	int yLength = Length(y);

	if ( x>y){
		return xLength;
	}
	else if(y>x){
		return yLength;
	}
	else{
		return yLength; 
	}

}
// The following functino calculates the cardinality of one set 
int cardinality(DLList v){
	int vLength = Length(v);
	return vLength;

}


// The following function takes in two lists and returns the 
//minimum value
// This is useful because when iterating through lists in for loops
//One list will be longer than the other, and you may encounter seg faults
// If you iterate through the cardinality of the sets because one list
// will finish while the other list still has elements to iterate 
int minLength(DLList x, DLList y){

	int xLength = Length(x);
	int yLength = Length(y);
	if (x<y){
		return xLength;
	}
	else if(y<x){
		return yLength; 
	}
	else{
		return yLength;
	}

}
// Pretty self explanatory, i've labled it p because this 
// function will be used to calculate the permuations of a rank.
int factorial(int p){

	if(p!=1)
		return p*factorial(p-1);
}
//The following function takes in a DLList and a URL and 
// Tells you the rank of that url in the list. 
int FindPosition(DLList L, char * url){
	DLListNode *curr; 
	curr = L->first; 

	while(curr->next != NULL){
		if strcmp(url,curr->value){
			return(curr->rank);
		}
		else{
			// Keep iterating 
		}

		curr = curr->next;
	}

	return 0;

}
// This function takes in a file from the command line 
//and stores it as a char that can be opened later.  
char * ObtainFile(char * argv[]){
	char* fileName = argv[1]; 
	return fileName;

}


// create an DLList by reading items from a file
// assume one item per line, line < 999 chars
// Rank should be added for each url that is added
// Because text file is in order ranks should be inserted in order accordingly 
// 1,2,3.. etc
DLList getDLList(char* ranktext)
{
	DLList L;
	DLListNode *new;
	char line[1000];


	FILE *in =fopen(ranktext, "r";)

	L = newDLList();
	int rank = 0;
	while (fgets(line,1000,in) != NULL) {
		char *value = strdup(trim(line));
		new = newDLListNode(value);
		if (L->last == NULL) {
			L->first = L->last = new;
		}
		else {
			L->last->next = new;
			new->prev = L->last;
			L->last = new;
		}
		L->nitems++;
		L->last->rank = rank + 1;
	}	
	L->curr = L->first;
	return L;
}

//Need to modification of DLListNode to include rank 
typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer prev node in list
	struct DLListNode *next;
	               // pointer to next node in list
	int rank;
} DLListNode;


