FLAGS= -Wall -g

all: my_mat.a connections 

my_mat.a: my_mat.o
	ar -rcs my_mat.a my_mat.o
connections:main.o my_mat.o
	gcc $(FLAGS) -o connections main.o my_mat.o
main.o:main.c my_mat.h
	gcc $(FLAGS) -c main.c

my_mat.o: my_mat.c my_mat.h
	gcc $(FLAGS) -c my_mat.c

.PHONY: clean all
clean:
	rm -f *.o *.a connections 

