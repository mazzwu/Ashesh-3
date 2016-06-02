//scaledFootrule.c


// Modify function to take in commandline arguments 
// Modify DLList to have rank store. 
// Get collection for argv[1] 
DLList CollectionToList(void);

// Get collection for argv[2]
DLList CollectionToList(void); 

// Calculate whether each list has any common ranks 
// you're going to want to iterate until the loop isnt at the end 


for(int i = 0; i< listlength; i++){

}
}


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

int cardinality(DLList v){
	int vLength = Length(v);

}


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

int factorial(int p){

	if(p!=1)
		return p*factorial(p-1);
}

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

