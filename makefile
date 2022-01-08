CC = gcc
FLAGS = -Wall -g
AR= ar
all: graph
graph: main.o graph.o
	$(CC) main.o graph.o -o graph

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

.PHONY: clean all

 clean:
	rm -f graph *.o