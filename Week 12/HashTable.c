// HashTable.c ... implementation of HashTable ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "HashTable.h"
#include "List.h"

// Types and functions local to HashTable ADT

typedef struct HashTabRep {
    List *lists;  // either use this
    int   nslots; // # elements in array
    int   nitems; // # items stored in HashTable
} HashTabRep;

// convert key into index (from Sedgewick)
unsigned int hash(Key k, int tableSize)
{
    unsigned int h = 0;
    int a = 31415, b = 27183;
    for (; *k != '\0'; k++) {
        a = a*b % (tableSize-1);
        h = (a*h + *k) % tableSize;
    }
    return (h % tableSize);
}


// Interface functions for HashTable ADT

// create an empty HashTable
HashTable newHashTable(int N)
{
    HashTabRep *new = malloc(sizeof(HashTabRep));
    assert(new != NULL);
    new->lists = malloc(N*sizeof(List));
    assert(new->lists != NULL);
    int i;
    for (i = 0; i < N; i++)
        new->lists[i] = newList();
    new->nslots = N; new->nitems = 0;
    return new;
}

// free memory associated with HashTable
void dropHashTable(HashTable ht)
{
    assert(ht != NULL);
    int i;
    for (i = 0; i < ht->nslots; i++)
        dropList(ht->lists[i]);
    free(ht);
}

// display HashTable stats
void HashTableStats(HashTable ht)
{
    assert(ht != NULL);
    
    printf("Hash Table Stats:\n");
    printf("Number of slots = %d\n",ht->nslots);  // TODO
    printf("Number of items = %d\n",ht->nitems);  // TODO
    printf("Chain length distribution\n");
    printf("%7s %7s\n","Length","#Chains");
    
    //create a new list of list array
    int *lists = malloc(ht->nslots *sizeof(HashTabRep));
    int i;
    //traverse through each slot of the hash table and count the number of chains(list) within each slot
    //length values of each list is stored in lists array
    for(i = 0; i < ht->nslots; i++) {
        lists[i] = ListLength(ht->lists[i]);
    }
    //using bubble sort, sort each slots in ascending order of each slot's list length
    int j, nswaps;
    for (i = 0; i < ht->nslots; i++) {
        nswaps = 0;
        for (j = ht->nslots; j > i; j--) {
            if(lists[j] < lists[j-1]) {
                int tmp = lists[j];
                lists[j] = lists[j-1];
                lists[j-1] = tmp;
                nswaps++;
            }
        }
        if (nswaps == 0) break;
    }
    //chain length = largest list length found - which is the last element of lists array now that it is sorted
    int maxChainLength = lists[ht->nslots];
    //create a new array which will hold the frequency of chains for each length (up to max chain length)
    //initialize all values to 0
    int *chains = (int *)calloc(maxChainLength, sizeof(HashTabRep));
    
    int k = 0;
    i = 0;
    j = 0;
    //this loop will count the #chains for each list length
    while (k < ht->nslots) {
        if(lists[k]!= i) {
            j++;
            i++;
        }
        if(lists[k] == i) {
            chains[j] = chains[j]+1;
        }
        k++;
        
    }
    //display the results
    i = 0;
    while(i < maxChainLength+1) {
        if(chains[i] != 0) {
            printf("%7d %7d\n",i, chains[i]);
        }
        i++;
    }
    free(chains);
    free(lists);
}


// insert a new value into a HashTable
void HashTableInsert(HashTable ht, Item it)
{
    assert(ht != NULL);
    int i = hash(key(it), ht->nslots);
    if (ListSearch(ht->lists[i], key(it)) == NULL) {
        ListInsert(ht->lists[i], it);
        ht->nitems++;
    }
}

// delete a value from a HashTable
void HashTableDelete(HashTable ht, Key k)
{
    assert(ht != NULL);
    int h = hash(k, ht->nslots);
    ListDelete(ht->lists[h], k);
}

// get Item from HashTable using Key
Item *HashTableSearch(HashTable ht, Key k)
{
    assert(ht != NULL);
    int i = hash(k, ht->nslots);
    return ListSearch(ht->lists[i], k);
}

