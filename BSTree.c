// BSTree.c ... implementation of binary search tree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "Queue.h"
#include "DLList.h"

#define GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define RESET "\x1b[0m"

#define BUF 1280 /* can change the buffer size as well */
#define TOT 1000 /* change to accomodate other sizes, change ONCE here */


typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	char * value;
	BSTLink left, right;
} BSTNode;

// make a new node containing a value
static
BSTLink newBSTNode(char * v)
{
	printf("can it not do this?\n");
	BSTLink new = malloc(sizeof(BSTNode));
	printf("does it get here?\n");
	assert(new != NULL);
	new->value = v;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{

	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

// display a BSTree
void showBSTree(BSTree t)
{
	printf("Does it come here? \n");
	void doShowBSTree(BSTree); // see later
	printf("What about here? \n");

	doShowBSTree(t);
}

// display BSTree root node
void showBSTreeNode(BSTree t)
{
	if (t == NULL) return;
	printf("%s ", t->value);
}

// print values in infix order
void BSTreeInfix(BSTree t)
{
	if (t == NULL) return;
	BSTreeInfix(t->left);
	showBSTreeNode(t);
	BSTreeInfix(t->right);
}

// print values in prefix order
void BSTreePrefix(BSTree t)
{
	if (t == NULL) return;
	showBSTreeNode(t);
	BSTreePrefix(t->left);
	BSTreePrefix(t->right);
}

// print values in postfix order
void BSTreePostfix(BSTree t)
{
	if (t == NULL) return;
	BSTreePostfix(t->left);
	BSTreePostfix(t->right);
	showBSTreeNode(t);
}

// print values in level-order
void BSTreeLevelOrder(BSTree t)
{
	if (t == NULL) {
        return;
    }
    
    Queue q = newQueue();
    QueueJoin(q, t); //add root node
    
    while (!QueueIsEmpty(q)) { //traverse tree
        t = QueueLeave(q);
        printf("%s ",t->value);
        if(t->left != NULL) { //ensure left of root is not empty
            QueueJoin(q, t->left); //add
        }
        if(t->right != NULL) { //ensure right of root not empty
            QueueJoin(q, t->right);//add
        }
    }
    dropQueue(q);
    return; 
}

// count #nodes in BSTree
int BSTreeNumNodes(BSTree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes(t->left)
	             + BSTreeNumNodes(t->right);
}

// count #leaves in BSTree
int BSTreeNumLeaves(BSTree t)
{
	 if (t == NULL) { //empty tree
        return 0;
    }
   //use recursion to traverse tree
    int l = BSTreeNumLeaves(t->left);
    int r = BSTreeNumLeaves(t->right);
    
    if ((t->left == NULL) && (t->right == NULL)) {
        return 1; //if no leaves on right and left
    } else {
        return (l+r); //return num of leaves on left and right of tree
    }

}

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, char * v)
{
	printf("Does it enter this function \n");
	if (t == NULL){
		
		return newBSTNode(v);
		printf("what\n");
	}

	//printf("does it ignore this?\n");

	else if (strcmp(v,t->value) < 0){
		
		printf("hmm\n");

		t->left = BSTreeInsert(t->left, v);
	}
	else if (strcmp(v,t->value) > 0)
		t->right = BSTreeInsert(t->right, v);
	else // (v == t->value)
		/* don't insert duplicates */;
	return t;
}

// check whether a value is in a BSTree
int BSTreeFind(BSTree t, char * v)
{
	if (t == NULL)
		return 0;
	else if (strcmp(v,t->value) < 0)
		return BSTreeFind(t->left, v);
	else if (strcmp (v,t->value) > 0)
		return BSTreeFind(t->right, v);
	else // (v == t->value)
		return 1;
}

/*
// delete root of tree
static
BSTree deleteRoot(BSTree t)
{
	// if no subtrees, tree empty after delete
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	// if only right subtree, make it the new root
	else if (t->left == NULL && t->right != NULL) {
		free(t);
		return t->right;
	}
	// if only left subtree, make it the new root
	else if (t->left != NULL && t->right == NULL) {
		free(t);
		return t->left;
	}
	// else (t->left != NULL && t->right != NULL)
	// so has two subtrees
	// - find inorder successor
	// - move its value to root
	// - delete inorder successor node
	BSTLink parent = t;
	BSTLink succ = t->right; // not null!
	while (succ->left != NULL) {
		parent = succ;
		succ = succ->left;
	}
	t->value = succ->value;
	free(succ);
	if (parent == t)
		parent->right = NULL;
	else
		parent->left = NULL;
	return t;
}

// delete a value from a BSTree
BSTree BSTreeDelete(BSTree t, int v)
{
	if (t == NULL)
		return NULL;
	else if (v < t->value)
		t->left = BSTreeDelete(t->left, v);
	else if (v > t->value)
		t->right = BSTreeDelete(t->right, v);
	else // (v == t->value)
		t = deleteRoot(t);
	return t;
}

*/ 

BSTree getBSTree(){
	
	
char *sobs[1000];
BSTree T;

	FILE *urlFILE = fopen("url11.txt", "r");
	//int i = 0;
	printf("hate life\n");

	for(int i= 0; i<1000; i++){
		printf("it shouldnt though\n");
		sobs[i] = malloc(1000*sizeof(char));
		printf("As suspected\n");
		fscanf(urlFILE, "%s", sobs[i]);
		printf("lol123\n");

		T = BSTreeInsert(T,sobs[i]);
		printf("jus checkn \n");
	}
	fclose(urlFILE);
	return T;


	/* 
	BSTree T;
	char line[TOT][BUF];
	int i = 0;
	int total = 0; 
 
	
	
	T = newBSTree();

	while(fgets(line[i], BUF, in)) {
         get rid of ending \n from fgets 
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    printf("Does it make it here? \n");

    total = i; 

    for( i =0; i < total; i++){
    	T=BSTreeInsert(T,line[i]);
    }

    return T; */ 
	

/*
	while (fscanf(in, "%s", word)!= EOF){
		//char * value = strings[i];
		
		printf("The word is %s \n", word);
		T = BSTreeInsert(T,word);
	} */ 
/*
	while (fscanf(in, "%s", strings[i])!= EOF){
		i++;
		printf("hakuna\n");
	}
	*/
	/*
	for(int k = 0; k< i; k ++){
		printf("%s\n",strings[k]);
	}

	for(int v=0; v<i; v++){
		T = BSTreeInsert(T, strings[i]); 
	}
	
*/
	


}


// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

// data structures
typedef struct asciinode_struct asciinode;
struct asciinode_struct
{
	asciinode * left, * right;
	//length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	//-1=I am left, 0=I am root, 1=I am right
	int parent_dir;
	//max supported unit32 in dec, 10 digits max
	char label[11];
};

// functions
void print_level(asciinode *node, int x, int level);
void compute_edge_lengths(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
asciinode *build_ascii_tree(BSTree t);
void free_ascii_tree(asciinode *node);

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

#define MIN(X,Y)  (((X) < (Y)) ? (X) : (Y))
#define MAX(X,Y)  (((X) > (Y)) ? (X) : (Y))

int gap = 3;  // gap between left and right nodes

//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;    

//prints ascii tree for given Tree structure
void doShowBSTree(BSTree t)
{
	asciinode *proot;
	int xmin, i;
	printf("help\n");
	if (t == NULL) return;
	printf("here?\n");
	proot = build_ascii_tree(t);
	printf("here???\n");
	compute_edge_lengths(proot);
	printf("lol line by line \n");
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		lprofile[i] = INFINITY;
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	printf("why why why delilah");
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = MIN(xmin, lprofile[i]);
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	printf("long shot \n");
	if (proot->height >= MAX_HEIGHT) {
		printf("(Tree is taller than %d; may be drawn incorrectly.)\n",
			MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++)
			printf(" ");
		print_next += i;
		printf(GREEN"%s"RESET, node->label);
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
		  for (i=0; i<(x-print_next-(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf(BROWN"/"RESET);
		  print_next++;
		}
		if (node->right != NULL)
		{
		  for (i=0; i<(x-print_next+(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf(BROWN"\\"RESET);
		  print_next++;
		}
	}
	else
	{
		print_level(node->left,
			    x-node->edge_length-1,
			    level-node->edge_length-1);
		print_level(node->right,
			    x+node->edge_length+1,
			    level-node->edge_length-1);
	}
}


//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);

	/* first fill in the edge_length of node */
	if (node->right == NULL && node->left == NULL)
		node->edge_length = 0;
	else
	{
		if (node->left == NULL)
			hmin = 0;
		else {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
				rprofile[i] = -INFINITY;
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		if (node->right == NULL)
			hmin = 0;
		else {
			for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
		    		lprofile[i] = INFINITY;
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		delta = 4;
		for (i=0; i<hmin; i++) {
			int w = gap+1+rprofile[i]-lprofile[i];
			delta = (delta > w) ? delta : w;
		}

		//If the node has two children of height 1, then we allow the
		//two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
		      (node->right != NULL && node->right->height == 1))
				&& delta > 4)
			delta--;
		node->edge_length = ((delta+1)/2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (node->left != NULL)
		h = MAX(node->left->height + node->edge_length + 1, h);
	if (node->right != NULL)
		h = MAX(node->right->height + node->edge_length + 1, h);
	node->height = h;
}

asciinode *build_ascii_tree_recursive(BSTree t)
{
	asciinode * node;

	if (t == NULL) return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	if (node->left != NULL) node->left->parent_dir = -1;
	if (node->right != NULL) node->right->parent_dir = 1;
	sprintf(node->label, "%s", t->value);
	node->lablen = strlen(node->label);;
	return node;
}


//Copy the tree into the ascii node structre
asciinode *build_ascii_tree(BSTree t)
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
	if (node == NULL) return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
	if (node->left != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
			lprofile[y+i] = MIN(lprofile[y+i], x-i);
	}
	compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
	if (node->right != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
	  		rprofile[y+i] = MAX(rprofile[y+i], x+i);
	}
	compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}