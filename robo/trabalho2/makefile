# My first makefile
 
all: out
 
out: main.o matrix.o
	gcc -o out main.o matrix.o 

main.o: main.c matrix.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic
 
matrix.o: matrix.c matrix.h
	gcc -o matrix.o matrix.c -c -W -Wall -ansi -pedantic
 
clean:
	rm -rf *.o *~ printy