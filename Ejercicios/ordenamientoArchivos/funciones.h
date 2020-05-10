#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ord.h"

void crearDirectorios( );
void generarReporteUserLists( reporteAlgoritmo * reporteMaxLists, int opcionAlgoritmo, int dimensionLista );
void generarReporteIterativos( reporteAlgoritmo * reporteMaxLists, int dimensionLista );
void generarReporte( reporteAlgoritmo * reporteGeneral );
void transferirValores( int listaDinamica[ ], int listasEstatica[ ], int size );
int generarNumeroAleatorioEnRango( int min, int max );
int generarAleatorioMaxLists( );
void generarListaDesordenada( int lista[ ], int size );
void generarListaOrdenada( int lista[ ], int size );
void imprimirListaArchivo( FILE * archivo, int lista[ ], int dimensionListas );
void imprimirLista( int lista[ ], int size );
void menuAlgoritmos( );
void menu( );
int validarOpcion( int min, int max );

#endif