all: Program

Program: Funcs Main
	gcc -o exe Main.o FuncionesCC.o

Funcs: FuncionesCC.c FuncionesCC.h
	gcc -c FuncionesCC.c

Main: Main.c FuncionesCC.h
	gcc -c Main.c
  