all: Program

Program: Func Main
	gcc -o exe Main.o FuncionesCC.o

Func: FuncionesCC.c FuncionesCC.h
	gcc -c FuncionesCC.c

Main: Main.c FuncionesCC.h
	gcc -c Main.c