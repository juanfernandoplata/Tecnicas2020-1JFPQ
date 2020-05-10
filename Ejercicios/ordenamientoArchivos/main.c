#include <stdio.h>
#include <stdlib.h>
#include "ord.h"
#include "funciones.h"

int main( ){
   crearDirectorios( );
   reporteAlgoritmo reporte, reporteGeneral[ 32 ], reporteListasUser[ 6 ], reporteAlgoritmoUnico[ 2 ];
   time_t tiempoNatural, limiteTiempo;
   struct tm horaFinalizacion;
   double tiempoEjecucion;
   clock_t tiempoInicio;
   int i, j, k, l, numElementos;
   int LOE_10[ 10 ], LOE_100[ 100 ], LOE_1000[ 1000 ], LOE_10000[ 10000 ];
   int LDE_10[ 10 ], LDE_100[ 100 ], LDE_1000[ 1000 ], LDE_10000[ 10000 ];
   int * listasNumerosEstaticas[ 8 ] = { LOE_10, LOE_100, LOE_1000, LOE_10000, LDE_10, LDE_100, LDE_1000, LDE_10000 };
   int dimensionListas[ 8 ] = { 10, 100, 1000, 10000, 10, 100, 1000, 10000 };
   int LOD_10[ 10 ], LOD_100[ 100 ], LOD_1000[ 1000 ], LOD_10000[ 10000 ];
   int LDD_10[ 10 ], LDD_100[ 100 ], LDD_1000[ 1000 ], LDD_10000[ 10000 ];
   int * listasNumerosDinamicas[ 8 ] = { LOD_10, LOD_100, LOD_1000, LOD_10000, LDD_10, LDD_100, LDD_1000, LDD_10000 };
   int * listasUserEstaticas[ 2 ];
   int * listasUserDinamicas[ 2 ];
   int * listasUser[ 2 ];
   FILE * datosPrueba;
   FILE * listasEntradaOrdenadas;
   FILE * listasEntradaDesordenadas;
   FILE * listasSalida;
   datosPrueba = fopen( "./Data/listas.dat", "rb" );
   if( datosPrueba != NULL ){
      for( i = 0; i < 8; i++ ){
         fread( listasNumerosEstaticas[ i ], dimensionListas[ i ], sizeof( int ), datosPrueba );
      }
   }
   fclose( datosPrueba );
   int opcion;
   do{
      menu();
      opcion = validarOpcion( 0, 5 );
      switch( opcion ){
         case 1: for( i = 0; i < 8; i++ ){
                    if( i < 4 ){
                       generarListaOrdenada( listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    }
                    else{
                       generarListaDesordenada( listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    }
                 }
                 datosPrueba = fopen( "./Data/listas.dat", "wb" );
                 for( i = 0; i < 8; i++ ){
                    fwrite( listasNumerosEstaticas[ i ], dimensionListas[ i ], sizeof( int ), datosPrueba );
                 }
                 fclose( datosPrueba );
                 break;
         case 2: for( i = 0, j = 8, k = 16, l = 24; i < 8; i++, j++, k++, l++ ){
                    reestablecerValores( listasNumerosDinamicas[ i ], listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    reporte = ordenarBurbujaBasico( listasNumerosDinamicas[ i ], dimensionListas[ i ], NULL );
                    reporteGeneral[ i ] = reporte;
                    reestablecerValores( listasNumerosDinamicas[ i ], listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    reporte = ordenarBurbujaBandera( listasNumerosDinamicas[ i ], dimensionListas[ i ], NULL );
                    reporteGeneral[ j ] = reporte;
                    reestablecerValores( listasNumerosDinamicas[ i ], listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    reporte = ordenarSeleccion( listasNumerosDinamicas[ i ], dimensionListas[ i ], NULL );
                    reporteGeneral[ k ] = reporte;
                    reestablecerValores( listasNumerosDinamicas[ i ], listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                    tiempoNatural = time( NULL );
                    reporte = ( reporteAlgoritmo ){ * localtime( &tiempoNatural ), horaFinalizacion, tiempoEjecucion, 0, 0, 0 };
                    tiempoInicio = clock( );
                    mergeSort( listasNumerosDinamicas[ i ], 0, dimensionListas[ i ] - 1, &reporte );
                    double tiempoEjecucion = ( clock( ) - tiempoInicio ) / CLOCKS_PER_SEC;
                    tiempoNatural = time( NULL );
                    reporte.horaFinalizacion = * localtime( &tiempoNatural );
                    reporte.tiempoDeEjecucion = tiempoEjecucion;
                    reporte.porcentajeOrdenamiento = evaluarOrdenamiento( listasNumerosDinamicas[ i ], dimensionListas[ i ] );
                    reporteGeneral[ l ] = reporte;
                 }
                 generarReporte( reporteGeneral );
                 listasEntradaOrdenadas = fopen( "./Listas/Entrada/Ordenadas/Listas.txt", "w" );
                 fprintf( listasEntradaOrdenadas, "LISTAS DE ENTRADA ORDENADAS DE LOS ALGORITMOS DE ORNAMIENTO\n" );
                 fprintf( listasEntradaOrdenadas, "\n" );
                 fprintf( listasEntradaOrdenadas, "\n" );
                 for( i = 0; i < 4; i++ ){
                    imprimirListaArchivo( listasEntradaOrdenadas, listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                 }
                 fclose( listasEntradaOrdenadas );
                 listasEntradaDesordenadas = fopen( "./Listas/Entrada/Desordenadas/Listas.txt", "w" );
                 fprintf( listasEntradaDesordenadas, "LISTAS DE ENTRADA DESORDENADAS DE LOS ALGORITMOS DE ORNAMIENTO\n" );
                 fprintf( listasEntradaDesordenadas, "\n" );
                 fprintf( listasEntradaDesordenadas, "\n" );
                 for( i = 4; i < 8; i++ ){
                    imprimirListaArchivo( listasEntradaDesordenadas, listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                 }
                 fclose( listasEntradaDesordenadas );
                 listasSalida = fopen( "./Listas/Salida/Ejecucion en Grupo/Listas.txt", "w" );
                 fprintf( listasSalida, "LISTAS DE SALIDA DE LOS ALGORITMOS DE ORNAMIENTO\n" );
                 fprintf( listasSalida, "\n" );
                 fprintf( listasSalida, "\n" );
                 for( i = 4; i < 8; i++ ){
                    imprimirListaArchivo( listasSalida, listasNumerosEstaticas[ i ], dimensionListas[ i ] );
                 }
                 fclose( listasSalida );
                 fclose( listasSalida );
                 break;
         case 3: printf( "Ingrese el numero de elementos con el que desea generar las listas: " );
                 scanf( "%d", &numElementos );
                 for( i = 0; i < 2; i++ ){
                    int * lista = malloc( numElementos * sizeof( int ) );
                    listasUserEstaticas[ i ] = lista;
                 }
                 for( i = 0; i < 2; i++ ){
                    int * lista = malloc( numElementos * sizeof( int ) );
                    listasUserDinamicas[ i ] = lista;
                 }
                 generarListaOrdenada( listasUserEstaticas[ 0 ], numElementos );
                 generarListaDesordenada( listasUserEstaticas[ 1 ], numElementos );
                 printf( "Ingrese el limite de tiempo en minutos: " );
                 scanf( "%d", &limiteTiempo );
                 limiteTiempo *= 60;
                 for( i = 0, j = 2, k = 4; i < 2; i++, j++, k++ ){
                    reestablecerValores( listasUserDinamicas[ i ], listasUserEstaticas[ i ], numElementos );
                    printf( "INICIO DE LA EJECUCION DEL ALGORITMO BURBUJA\n" );
                    reporte = ordenarBurbujaBasico( listasUserDinamicas[ i ], numElementos, &limiteTiempo );
                    printf( "FINALIZACION DE LA EJECUCION DEL ALGORITMO BURBUJA\n" );
                    reporteListasUser[ i ] = reporte;
                    reestablecerValores( listasUserDinamicas[ i ], listasUserEstaticas[ i ], numElementos );
                    printf( "INICIO DE LA EJECUCION DEL ALGORITMO BURBUJA MEJORADO\n" );
                    reporte = ordenarBurbujaBandera( listasUserDinamicas[ i ], numElementos, &limiteTiempo );
                    printf( "FINALIZACION DE LA EJECUCION DEL ALGORITMO BURBUJA MEJORADO\n" );
                    reporteListasUser[ j ] = reporte;
                    reestablecerValores( listasUserDinamicas[ i ], listasUserEstaticas[ i ], numElementos );
                    printf( "INICIO DE LA EJECUCION DEL ALGORITMO DE SELECCION\n" );
                    reporte = ordenarSeleccion( listasUserDinamicas[ i ], numElementos, &limiteTiempo );
                    printf( "FINALIZACION DE LA EJECUCION DEL ALGORITMO DE SELECCION\n" );
                    reporteListasUser[ k ] = reporte;
                 }
                 generarReporteIterativos( reporteListasUser, numElementos );
                 break;
         case 4: printf( "Ingrese el numero de elementos con el que desea generar las listas: " );
                 scanf( "%d", &numElementos );
                 for( i = 0; i < 2; i++ ){
                    int * lista = malloc( numElementos * sizeof( int ) );
                    listasUser[ i ] = lista;
                 }
                 generarListaOrdenada( listasUser[ 0 ], numElementos );
                 generarListaDesordenada( listasUser[ 1 ], numElementos );
                 menuAlgoritmos( );
                 opcion = validarOpcion( 1, 3 );
                 switch( opcion ){
                    case 1: reporte = ordenarBurbujaBasico( listasUser[ 0 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 0 ] = reporte;
                            reporte = ordenarBurbujaBasico( listasUser[ 1 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 1 ] = reporte;
                            generarReporteAlgoritmoUnico( reporteAlgoritmoUnico, opcion, numElementos );
                            break;
                    case 2: reporte = ordenarBurbujaBandera( listasUser[ 0 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 0 ] = reporte;
                            reporte = ordenarBurbujaBandera( listasUser[ 1 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 1 ] = reporte;
                            generarReporteAlgoritmoUnico( reporteAlgoritmoUnico, opcion, numElementos );
                            break;
                    case 3: reporte = ordenarSeleccion( listasUser[ 0 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 0 ] = reporte;
                            reporte = ordenarSeleccion( listasUser[ 1 ], numElementos, NULL );
                            reporteAlgoritmoUnico[ 1 ] = reporte;
                            generarReporteAlgoritmoUnico( reporteAlgoritmoUnico, opcion, numElementos );
                            break;
                 }
                 break;
         case 5: printf( "Ingrese el numero de elementos con el que desea generar las listas: " );
                 scanf( "%d", &numElementos );
                 for( i = 0; i < 2; i++ ){
                    int * lista = malloc( numElementos * sizeof( int ) );
                    listasUser[ i ] = lista;
                 }
                 generarListaOrdenada( listasUser[ 0 ], numElementos );
                 generarListaDesordenada( listasUser[ 1 ], numElementos );
                 for( i = 0; i < 2; i++ ){
                    tiempoNatural = time( NULL );
                    reporte = ( reporteAlgoritmo ){ * localtime( &tiempoNatural ), horaFinalizacion, tiempoEjecucion, 0, 0, 0 };
                    tiempoInicio = clock( );
                    mergeSort( listasUser[ i ], 0, numElementos - 1, &reporte );
                    double tiempoEjecucion = ( clock( ) - tiempoInicio ) / CLOCKS_PER_SEC;
                    tiempoNatural = time( NULL );
                    reporte.horaFinalizacion = * localtime( &tiempoNatural );
                    reporte.tiempoDeEjecucion = tiempoEjecucion;
                    reporte.porcentajeOrdenamiento = evaluarOrdenamiento( listasUser[ i ], numElementos );
                    reporteAlgoritmoUnico[ i ] = reporte;
                 }
                 generarReporteAlgoritmoUnico( reporteAlgoritmoUnico, 4, numElementos );
      }
   }while( opcion != 0 );
   printf( "El programa ha finalizado\n" );
   
   return 0;
}