
# COMP1927 Assignment 2
CC=gcc
CFLAGS=-Wall -Werror -g
OBJS= list.o pagerank.o graph.o main.o

page : $(OBJS)
$(CC) -o page $(OBJS)


list.o : list.c list.h
pagerank.o : pagerank.c pagerank.h
graph.o : graph.c graph.h
main.o : main.c 
clean :
rm -f  $(OBJS) core 