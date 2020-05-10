#ifndef ORD
#define ORD

#include <stdio.h>
#include <time.h>

typedef struct reporteAlgoritmo{
   struct tm horaInicio;
   struct tm horaFinalizacion;
   double tiempoDeEjecucion;
   long long int numIntercambios;
   long long int numComparaciones;
   double porcentajeOrdenamiento;
}reporteAlgoritmo;

double evaluarOrdenamiento( int arreglo[ ], int size );
reporteAlgoritmo ordenarBurbujaBasico( int arreglo[], int size, time_t * tiempoLimite );
reporteAlgoritmo ordenarBurbujaBandera( int arreglo[], int size, time_t * tiempoLimite );
reporteAlgoritmo ordenarSeleccion( int arreglo[], int size, time_t * tiempoLimite );
void mergeSort( int arreglo[], int posInicial, int posFinal, reporteAlgoritmo * reporte );

#endif