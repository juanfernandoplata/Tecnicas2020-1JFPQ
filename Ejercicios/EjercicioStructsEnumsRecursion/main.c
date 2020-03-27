#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define FILAS 12

typedef struct datosPersona{
   char nombre[ 10 ];
   int dia, mes, anio;
} datosPersona;

int main(){
   datosPersona ** matriz = crearMatrizDinamica();
   datosPersona datos;
   int limitesFilas[ FILAS ] = {0}, opcion, mes, anio;
   char nombre[ 10 ];
   do{
      fflush( stdin );
      opcion = menu();
      switch( opcion ){
         case 1: crearAgregarDatosPersona( matriz, limitesFilas );
                 break;
         case 2: mes = seleccionMes();
                 mostrarDatos( matriz, mes, limitesFilas[ mes - 1 ] );
                 break;
         case 3: printf( "Ingrese el nombre la persona\n" );
                 scanf( "%s", nombre );
                 anio = buscarAnioPersona( matriz, limitesFilas, nombre );
                 if( anio ){
                    if( esBisiesto( anio ) )
                       printf( "La persona si nacio en anio bisiesto\n" );
                    else
                       printf( "La persona no nacio en anio bisiesto\n" );
                 }
                 else
                    printf( "Lo sentimos. El nombre que ingreso no fue encontrado en el registro\n" );
                 break;
      }
   } while( opcion != 0 );
   free( matriz );
   printf( "El programa ha finalizado\n" );
   return 0;
}