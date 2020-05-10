#include "funciones.h"

void crearDirectorios( ){
   mkdir( "Data" );
   mkdir( "Reportes Algoritmos" );
   mkdir( "./Reportes Algoritmos/Ejecucion en Grupo" );
   mkdir( "./Reportes Algoritmos/Ejecucion Individual" );
   mkdir( "./Reportes Algoritmos/Ejecucion Individual/Burbuja Basico" );
   mkdir( "./Reportes Algoritmos/Ejecucion Individual/Burbuja Mejorado" );
   mkdir( "./Reportes Algoritmos/Ejecucion Individual/Seleccion" );
   mkdir( "./Reportes Algoritmos/Ejecucion Individual/Merge Sort" );
   mkdir( "Listas" );
   mkdir( "./Listas/Entrada" );
   mkdir( "./Listas/Entrada/Ordenadas" );
   mkdir( "./Listas/Entrada/Desordenadas" );
   mkdir( "./Listas/Salida" );
   mkdir( "./Listas/Salida/Ejecucion En grupo" );
   mkdir( "./Listas/Salida/Ejecucion Individual" );
   mkdir( "./Listas/Salida/Ejecucion Individual/Burbuja Basico" );
   mkdir( "./Listas/Salida/Ejecucion Individual/Burbuja Mejorado" );
   mkdir( "./Listas/Salida/Ejecucion Individual/Seleccion" );
   mkdir( "./Listas/Salida/Ejecucion Individual/Merge Sort" );
}

void generarReporteAlgoritmoUnico( reporteAlgoritmo * reporteMaxLists, int opcionAlgoritmo, int dimensionLista ){
   FILE * reporte;
   char rutaBase[ 50 ] = "./Reportes Algoritmos/Ejecucion Individual/";
   char rutaEspecifica[ 100 ] = "";
   char numElementos[ 20 ];
   itoa( dimensionLista, numElementos, 10 );
   int i;
   if( opcionAlgoritmo == 1 ){
      strcat( rutaEspecifica, rutaBase );
      strcat( rutaEspecifica, "Burbuja Basico/" );
      strcat( rutaEspecifica, numElementos );
      strcat( rutaEspecifica, "_Elementos.txt" );
      reporte = fopen( rutaEspecifica, "w" );
      fprintf( reporte, "=======================\n" );
      fprintf( reporte, "|  ALGORITMO BURBUJA  |\n" );
      fprintf( reporte, "=======================\n" );
      fprintf( reporte, "\n" );
   }
   else if( opcionAlgoritmo == 2 ){
      strcat( rutaEspecifica, rutaBase );
      strcat( rutaEspecifica, "Burbuja Mejorado/" );
      strcat( rutaEspecifica, numElementos );
      strcat( rutaEspecifica, "_Elementos.txt" );
      reporte = fopen( rutaEspecifica, "w" );
      fprintf( reporte, "================================\n" );
      fprintf( reporte, "|  ALGORITMO BURBUJA MEJORADO  |\n" );
      fprintf( reporte, "================================\n" );
      fprintf( reporte, "\n" );
   }
   else if( opcionAlgoritmo == 3 ){
      strcat( rutaEspecifica, rutaBase );
      strcat( rutaEspecifica, "Seleccion/" );
      strcat( rutaEspecifica, numElementos );
      strcat( rutaEspecifica, "_Elementos.txt" );
      reporte = fopen( rutaEspecifica, "w" );
      fprintf( reporte, "============================\n" );
      fprintf( reporte, "|  ALGORITMO DE SELECCION  |\n" );
      fprintf( reporte, "============================\n" );
      fprintf( reporte, "\n" );
   }
   else if( opcionAlgoritmo == 4 ){
      strcat( rutaEspecifica, rutaBase );
      strcat( rutaEspecifica, "Merge Sort/" );
      strcat( rutaEspecifica, numElementos );
      strcat( rutaEspecifica, "_Elementos.txt" );
      reporte = fopen( rutaEspecifica, "w" );
      fprintf( reporte, "==========================\n" );
      fprintf( reporte, "|  ALGORITMO MERGE SORT  |\n" );
      fprintf( reporte, "==========================\n" );
      fprintf( reporte, "\n" );
   }
   for( i = 0; i < 2; i++ ){
      if( i == 0 ){
         fprintf( reporte, "==================================\n" );
         fprintf( reporte, "LISTA ORDENADA\n" );
         fprintf( reporte, "DIMENSION DE LA LISTA: %d\n", dimensionLista );
         fprintf( reporte, "==================================\n" );
         fprintf( reporte, "\n" );
      }
      else{
         fprintf( reporte, "==================================\n" );
         fprintf( reporte, "LISTA DESORDENADA\n" );
         fprintf( reporte, "DIMENSION DE LA LISTA: %d\n", dimensionLista );
         fprintf( reporte, "==================================\n" );
         fprintf( reporte, "\n" );
      }
      fprintf( reporte, "INICIO DE LA EJECUCION\n" );
      fprintf( reporte, "======================\n" );
      fprintf( reporte, "\n" );
      fprintf( reporte, "ANIO: %d\n", reporteMaxLists[ i ].horaInicio.tm_year + 1900 );
      fprintf( reporte, "MES: %d\n", reporteMaxLists[ i ].horaInicio.tm_mon + 1 );
      fprintf( reporte, "DIA: %d\n", reporteMaxLists[ i ].horaInicio.tm_mday );
      fprintf( reporte, "HORA: %d\n", reporteMaxLists[ i ].horaInicio.tm_hour );
      fprintf( reporte, "MINUTO: %d\n", reporteMaxLists[ i ].horaInicio.tm_min );
      fprintf( reporte, "SEGUNDO: %d\n", reporteMaxLists[ i ].horaInicio.tm_sec );
      fprintf( reporte, "\n" );
      fprintf( reporte, "\n" );
      fprintf( reporte, "FINALIZACION DE LA EJECUCION\n" );
      fprintf( reporte, "============================\n" );
      fprintf( reporte, "\n" );
      fprintf( reporte, "ANIO: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_year + 1900 );
      fprintf( reporte, "MES: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_mon + 1 );
      fprintf( reporte, "DIA: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_mday );
      fprintf( reporte, "HORA: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_hour );
      fprintf( reporte, "MINUTO: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_min );
      fprintf( reporte, "SEGUNDO: %d\n", reporteMaxLists[ i ].horaFinalizacion.tm_sec );
      fprintf( reporte, "\n" );
      fprintf( reporte, "TIEMPO DE EJECUCCION EN SEGUNDOS: %lf\n", reporteMaxLists[ i ].tiempoDeEjecucion );
      fprintf( reporte, "TIEMPO DE EJECUCCION EN MINUTOS: %lf\n", reporteMaxLists[ i ].tiempoDeEjecucion / 60 );
      fprintf( reporte, "\n" );
      fprintf( reporte, "NUMERO DE INTERCAMBIOS DE ELEMENTOS: %lld\n", reporteMaxLists[ i ].numIntercambios );
      fprintf( reporte, "NUMERO DE COMPARACIONES ENTRE ELEMENTOS: %lld\n", reporteMaxLists[ i ].numComparaciones );
      fprintf( reporte, "\n" );
      fprintf( reporte, "PORCENTAJE DEL ARREGLO ORDENADO: %lf%%\n", reporteMaxLists[ i ].porcentajeOrdenamiento );
      fprintf( reporte, "\n" );
      fprintf( reporte, "=================================================\n" );
      fprintf( reporte, "\n" );
   }
   fclose( reporte );
}

void generarReporteIterativos( reporteAlgoritmo * reporteMaxLists, int dimensionLista ){
   FILE * reporte = fopen( "./Reportes Algoritmos/Ejecucion en Grupo/Reporte_Algoritmos_Iterativos_Con_Tiempo_Limite_De_Ejecucion.txt", "w" );
   int i, j, k;
   for( i = 0; i < 3; i++ ){
      if( i == 0 ){
         fprintf( reporte, "=======================\n" );
         fprintf( reporte, "|  ALGORITMO BURBUJA  |\n" );
         fprintf( reporte, "=======================\n" );
         fprintf( reporte, "\n" );
      }
      else if( i == 1 ){
         fprintf( reporte, "================================\n" );
         fprintf( reporte, "|  ALGORITMO BURBUJA MEJORADO  |\n" );
         fprintf( reporte, "================================\n" );
         fprintf( reporte, "\n" );
      }
      else{
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "|  ALGORITMO DE SELECCION  |\n" );
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "\n" );
      }
      for( j = 0; j < 2; j++ ){
         if( j == 0 ){
            fprintf( reporte, "==================================\n" );
            fprintf( reporte, "LISTA ORDENADA\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: %d\n", dimensionLista );
            fprintf( reporte, "==================================\n" );
            fprintf( reporte, "\n" );
         }
         else{
            fprintf( reporte, "==================================\n" );
            fprintf( reporte, "LISTA DESORDENADA\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: %d\n", dimensionLista );
            fprintf( reporte, "==================================\n" );
            fprintf( reporte, "\n" );
         }
         fprintf( reporte, "INICIO DE LA EJECUCION\n" );
         fprintf( reporte, "======================\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "ANIO: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_year + 1900 );
         fprintf( reporte, "MES: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_mon + 1 );
         fprintf( reporte, "DIA: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_mday );
         fprintf( reporte, "HORA: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_hour );
         fprintf( reporte, "MINUTO: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_min );
         fprintf( reporte, "SEGUNDO: %d\n", reporteMaxLists[ i * 2 + j ].horaInicio.tm_sec );
         fprintf( reporte, "\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "FINALIZACION DE LA EJECUCION\n" );
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "ANIO: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_year + 1900 );
         fprintf( reporte, "MES: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_mon + 1 );
         fprintf( reporte, "DIA: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_mday );
         fprintf( reporte, "HORA: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_hour );
         fprintf( reporte, "MINUTO: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_min );
         fprintf( reporte, "SEGUNDO: %d\n", reporteMaxLists[ i * 2 + j ].horaFinalizacion.tm_sec );
         fprintf( reporte, "\n" );
         fprintf( reporte, "TIEMPO DE EJECUCCION EN SEGUNDOS: %lf\n", reporteMaxLists[ i * 2 + j ].tiempoDeEjecucion );
         fprintf( reporte, "TIEMPO DE EJECUCCION EN MINUTOS: %lf\n", reporteMaxLists[ i * 2 + j ].tiempoDeEjecucion / 60 );
         fprintf( reporte, "\n" );
         fprintf( reporte, "NUMERO DE INTERCAMBIOS DE ELEMENTOS: %lld\n", reporteMaxLists[ i * 2 + j ].numIntercambios );
         fprintf( reporte, "NUMERO DE COMPARACIONES ENTRE ELEMENTOS: %lld\n", reporteMaxLists[ i * 2 + j ].numComparaciones );
         fprintf( reporte, "\n" );
         fprintf( reporte, "PORCENTAJE DEL ARREGLO ORDENADO: %lf%%\n", reporteMaxLists[ i * 2 + j ].porcentajeOrdenamiento );
         fprintf( reporte, "\n" );
         fprintf( reporte, "=================================================\n" );
         fprintf( reporte, "\n" );
      }
   }
   fclose( reporte );
}

void generarReporte( reporteAlgoritmo * reporteGeneral ){
   FILE * reporte = fopen( "./Reportes Algoritmos/Ejecucion en Grupo/Reporte_Algoritmos_Listas_10_100_1000_10000.txt", "w" );
   int i, j, k;
   for( i = 0; i < 4; i++ ){
      if( i == 0 ){
         fprintf( reporte, "=======================\n" );
         fprintf( reporte, "|  ALGORITMO BURBUJA  |\n" );
         fprintf( reporte, "=======================\n" );
         fprintf( reporte, "\n" );
      }
      else if( i == 1 ){
         fprintf( reporte, "================================\n" );
         fprintf( reporte, "|  ALGORITMO BURBUJA MEJORADO  |\n" );
         fprintf( reporte, "================================\n" );
         fprintf( reporte, "\n" );
      }
      else if( i == 2 ){
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "|  ALGORITMO DE SELECCION  |\n" );
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "\n" );
      }
      else{
         fprintf( reporte, "==========================\n" );
         fprintf( reporte, "|  ALGORITMO MERGE SORT  |\n" );
         fprintf( reporte, "==========================\n" );
         fprintf( reporte, "\n" );
      }
      for( j = 0; j < 8; j++ ){
         if( j == 0 ){
            fprintf( reporte, "============================\n" );
            fprintf( reporte, "LISTA ORDENADA 1           |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 10  |\n" );
            fprintf( reporte, "============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 1 ){
            fprintf( reporte, "=============================\n" );
            fprintf( reporte, "LISTA ORDENADA 2            |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 100  |\n" );
            fprintf( reporte, "=============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 2 ){
            fprintf( reporte, "==============================\n" );
            fprintf( reporte, "LISTA ORDENADA 3             |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 1000  |\n" );
            fprintf( reporte, "==============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 3 ){
            fprintf( reporte, "===============================\n" );
            fprintf( reporte, "LISTA ORDENADA 4              |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 10000  |\n" );
            fprintf( reporte, "===============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 4 ){
            fprintf( reporte, "============================\n" );
            fprintf( reporte, "LISTA DESORDENADA 1        |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 10  |\n" );
            fprintf( reporte, "============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 5 ){
            fprintf( reporte, "=============================\n" );
            fprintf( reporte, "LISTA DESORDENADA 2         |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 100  |\n" );
            fprintf( reporte, "=============================\n" );
            fprintf( reporte, "\n" );
         }
         else if( j == 6 ){
            fprintf( reporte, "==============================\n" );
            fprintf( reporte, "LISTA DESORDENADA 3          |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 1000  |\n" );
            fprintf( reporte, "==============================\n" );
            fprintf( reporte, "\n" );
         }
         else{
            fprintf( reporte, "===============================\n" );
            fprintf( reporte, "LISTA DESORDENADA 4           |\n" );
            fprintf( reporte, "DIMENSION DE LA LISTA: 10000  |\n" );
            fprintf( reporte, "===============================\n" );
            fprintf( reporte, "\n" );
         }
         fprintf( reporte, "INICIO DE LA EJECUCION\n" );
         fprintf( reporte, "======================\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "ANIO: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_year + 1900 );
         fprintf( reporte, "MES: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_mon + 1 );
         fprintf( reporte, "DIA: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_mday );
         fprintf( reporte, "HORA: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_hour );
         fprintf( reporte, "MINUTO: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_min );
         fprintf( reporte, "SEGUNDO: %d\n", reporteGeneral[ i * 8 + j ].horaInicio.tm_sec );
         fprintf( reporte, "\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "FINALIZACION DE LA EJECUCION\n" );
         fprintf( reporte, "============================\n" );
         fprintf( reporte, "\n" );
         fprintf( reporte, "ANIO: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_year + 1900 );
         fprintf( reporte, "MES: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_mon + 1 );
         fprintf( reporte, "DIA: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_mday );
         fprintf( reporte, "HORA: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_hour );
         fprintf( reporte, "MINUTO: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_min );
         fprintf( reporte, "SEGUNDO: %d\n", reporteGeneral[ i * 8 + j ].horaFinalizacion.tm_sec );
         fprintf( reporte, "\n" );
         fprintf( reporte, "TIEMPO DE EJECUCCION EN SEGUNDOS: %lf\n", reporteGeneral[ i * 8 + j ].tiempoDeEjecucion );
         fprintf( reporte, "TIEMPO DE EJECUCCION EN MINUTOS: %lf\n", reporteGeneral[ i * 8 + j ].tiempoDeEjecucion / 60 );
         fprintf( reporte, "\n" );
         fprintf( reporte, "NUMERO DE INTERCAMBIOS DE ELEMENTOS: %lld\n", reporteGeneral[ i * 8 + j ].numIntercambios );
         fprintf( reporte, "NUMERO DE COMPARACIONES ENTRE ELEMENTOS: %lld\n", reporteGeneral[ i * 8 + j ].numComparaciones );
         fprintf( reporte, "\n" );
         fprintf( reporte, "PORCENTAJE DEL ARREGLO ORDENADO: %lf%%\n", reporteGeneral[ i * 8 + j ].porcentajeOrdenamiento );
         fprintf( reporte, "\n" );
         fprintf( reporte, "=================================================\n" );
         fprintf( reporte, "\n" );
      }
   }
   fclose( reporte );
}

void reestablecerValores( int listaDinamica[ ], int listaEstatica[ ], int size ){
   int i;
   for( i = 0; i < size; i++ ){
         listaDinamica[ i ] = listaEstatica[ i ];
   }
}

int generarNumeroAleatorioEnRango( int min, int max ){
   int numero = ( rand( ) % ( max - min + 1 ) ) + min;
   return numero;
}

int validarNumeroCifras( int numero ){
   int cifras = 0;
   while( numero != 0 ){
      numero /= 10;
      cifras++;
   }
   return cifras;
}

int generarAleatorioUserList( int size ){
   int cifrasSize = validarNumeroCifras( size );
   int numero = 0, dimensionNumero, aleatorio, i;
   dimensionNumero = generarNumeroAleatorioEnRango( 1, cifrasSize - 1 );
   for( i = 1; i < pow( 10, dimensionNumero ); i *= 10  ){
      aleatorio = generarNumeroAleatorioEnRango( 0, 9 );
      numero += aleatorio * i;
   }
   return numero;
}

void generarListaOrdenada( int lista[ ], int size ){
   int i;
   for( i = 0; i < size; i++ ){
      lista[ i ] = i;
   }
}

void generarListaDesordenada( int lista[ ], int size ){
   int i;
   generarListaOrdenada( lista, size );
   if( size > RAND_MAX ){
      for( i = 1; i <= size * 2; i++ ){
         intercambiar( lista, generarAleatorioUserList( size ), generarAleatorioUserList( size ) );
      }
   }
   else{
      for( i = 1; i <= size * 2; i++ ){
         intercambiar( lista, generarNumeroAleatorioEnRango( 0, size - 1 ), generarNumeroAleatorioEnRango( 0, size - 1 ) );
      }
   }
}

void imprimirListaArchivo( FILE * archivo, int lista[ ], int dimensionLista ){
   int i, j;
   fprintf( archivo, "NUMERO DE ELEMENTOS DE LA LISTA: %d\n", dimensionLista );
   fprintf( archivo, "\n" );
   for( i = 0; i < dimensionLista; i++ ){
      fprintf( archivo, "%d ", lista[ i ] );
   }
   fprintf( archivo, "\n" );
   fprintf( archivo, "\n" );
   fprintf( archivo, "\n" );
}

void imprimirLista( int lista[ ], int size ){
   int i;
   for( i = 0; i < size; i++ ){
      printf( "%d ", lista[ i ] );
   }
   printf( "\n" );
}

void menuAlgoritmos( ){
   printf( "SELECCIONE EL ALGORITMO QUE DESEA UTILIZAR\n" );
   printf( "1. Algoritmo Burbuja Basico\n" );
   printf( "2. Algoritmo Burbuja Mejorado\n" );
   printf( "3. Algoritmo de Seleccion\n" );
}

void menu( ){
   printf( "MENU PRINCIPAL\n" );
   printf( "1. Generar nuevos archivos con datos de prueba\n" );
   printf( "2. Probar rendimiento de los algoritmos con arreglos de 10, 100, 1000 y 10000 elementos, y generar reporte de estadisticas\n" );
   printf( "3. Probar rendimiento de los algoritmos iterativos de ordenamiento defininiendo el tamanio de los arreglos y el tiempo limite de ejecucion\n" );
   printf( "4. Probar un solo algoritmo iterativo de ordenamiento defininiendo el tamanio de los arreglos\n" );
   printf( "5. Probar el algoritmo Merge Sort defininiendo el tamanio de los arreglos\n" );
   printf( "0. Salir\n" );
}

int validarOpcion( int min, int max ){
   int i = 1, opcion;
   do{
      if( i > 1 ){
         printf( "El valor ingresado es invalido. Por favor intentelo nuevamente.\n" );
      }
      scanf( "%d", &opcion );
      i++;
   }while( opcion < min || opcion > max );
   return opcion;
}

/*
   char rutaBase[ 50 ] = "./Reportes Algoritmos/Ejecucion Individual/";
   char rutaEspecifica[ 100 ] = "";
   char numElementos[ 20 ];
   itoa( dimensionLista, numElementos, 10 );

      strcat( rutaEspecifica, rutaBase );
      strcat( rutaEspecifica, "Burbuja Basico/" );
      strcat( rutaEspecifica, numElementos );
      strcat( rutaEspecifica, "_Elementos.txt" );
      printf( "%s\n", rutaEspecifica );

*/