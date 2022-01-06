CC = gcc
FLAGS = -Wall -g
AR= ar
all: algo
graph: main.o algo.o
	$(CC) main.o algo.o -o algo

main.o: main.c algo.h
	$(CC) $(FLAGS) -c main.c

graph.o: algo.c algo.h
	$(CC) $(FLAGS) -c algo.c

.PHONY: clean all

 clean:
	rm -f algo *.o