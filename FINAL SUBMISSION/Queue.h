//  Queue.h
//  Assignment 2 COMP1927
//  June 2016
//  Created by John Shepherd
//  Modified by Winnie Zheng && Vivian Bakiris
#ifndef searchTfIdf_h
#ifndef QUEUE_H
#define QUEUE_H

#include "BSTree.h"
typedef struct BSTNode *Item;
#define showItem showBSTreeNode

typedef struct QueueRep *Queue;

Queue newQueue(); // create new empty queue
void dropQueue(Queue); // free memory used by queue
void QueueJoin(Queue,Item); // add item on queue
Item QueueLeave(Queue); // remove item from queue
int QueueIsEmpty(Queue); // check for no items

#endif
