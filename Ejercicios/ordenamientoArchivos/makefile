all: programa

programa: main funciones ord
	gcc -o exe main.o funciones.o ord.o

main: main.c ord.h
	gcc -c main.c

funciones: funciones.c funciones.h ord.h
	gcc -c funciones.c

ord: ord.c ord.h
	gcc -c ord.c