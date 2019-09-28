# My first makefile
 
all: out
 
out: main.o sum.o difference.o
	gcc -o out main.o sum.o difference.o
 
main.o: main.c sum.h difference.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic
 
sum.o: sum.c sum.h
	gcc -o sum.o sum.c -c -W -Wall -ansi -pedantic
 
difference.o: difference.c difference.h
	gcc -o difference.o difference.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ printy
