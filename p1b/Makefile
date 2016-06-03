CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=bst.o BSTree.o Queue.o DLList.o Inverted.o
BINS=bst

all : $(BINS)

bst : $(OBJS)
	$(CC) -o bst $(OBJS)

bst.o : bst.c BSTree.h
BSTree.o : BSTree.c BSTree.h Queue.h
Queue.o : Queue.c Queue.h
DLList.o : DLList.c DLList.h
Inverted.o : Inverted.c Inverted.o

tests : bst
	cd tests ; make

clean :
	rm -fr $(BINS) $(OBJS) core *.dSYM tests/*.observed
