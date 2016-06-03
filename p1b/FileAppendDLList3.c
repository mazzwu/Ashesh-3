DLList FileAppendDLList3(FILE *in, DLList L, DLList D){
    //DLList L;
    DLListNode *new;
    char word[1000];

    if(L == NULL){
        L = newDLList();
    }
    

    while (fscanf(in,"%s",word) != EOF) {

        char *value = strdup(trim(word));
        new = newDLListNode(value);

        if (elementExists(L,value) != 0) continue;
        if (elementIsUrl(D, value) != 0) continue;


        if (L->first == NULL) {
            L->first = L->last = new;
            // If thats the case you don't have to worry about order
        }
        else {
            if(strcmp(new,L->last->value)>0){
            L->last->next = new;
            new->prev = L->last;
            L->last = new;
            }

            else if (strcmp(new,L->last->value)<0){
                DllistNode *curr = L->last; 
                while(strcmp(new,curr)<0){
                    curr = curr->prev; 
                }
                new->next = curr ->next; 
                new->prev = curr; 
                curr->next->prev = new; 
                curr->next = new; 
              
            }
        }
        L->nitems++;
    }   
    L->curr = L->first;
    return L;
}
