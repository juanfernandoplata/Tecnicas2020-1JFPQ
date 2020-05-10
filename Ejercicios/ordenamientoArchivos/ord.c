#include "ord.h"

double evaluarOrdenamiento( int arreglo[ ], int size ){
   int i;
   for( i = 0; i < size - 1; i++ ){
      if( arreglo[ i ] > arreglo[ i + 1 ] ){
         break;
      }
   }
   if( i == size - 1 ){
      i++;
   }
   return ( ( double )i / ( double )(size) ) * ( double ) 100;
}

void intercambiar( int arreglo[ ], int posicion1, int posicion2 ){
   double temp = arreglo[ posicion1 ];
   arreglo[ posicion1 ] = arreglo[ posicion2 ];
   arreglo[ posicion2 ] = temp;
}

reporteAlgoritmo ordenarBurbujaBasico( int arreglo[ ], int size, time_t * tiempoLimite ){
   time_t tiempoNatural = time( NULL );
   struct tm horaInicio = * localtime( &tiempoNatural ), horaFinalizacion;
   int i, j;
   long long int numComparacionesAnterior;
   long long int numComparaciones = 0;
   long long int numIntercambios = 0;
   clock_t tiempoInicio = clock( );
   for( i = 1; i <= size; i++ ){
      for( j = 0; j < size - 1; j++ ){
         numComparaciones++;
         if( arreglo[ j + 1 ] < arreglo[ j ] ){
            intercambiar( arreglo, j + 1, j );
            numIntercambios++;
         }
         if( tiempoLimite != NULL ){
            if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
               break;
            }
         }
      }
      if( tiempoLimite != NULL ){
         if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
            break;
         }
      }
   }
   double tiempoEjecucion = ( clock( ) - tiempoInicio ) / CLOCKS_PER_SEC;
   tiempoNatural = time( NULL );
   horaFinalizacion = * localtime( &tiempoNatural );
   double porcentajeOrdenamiento = evaluarOrdenamiento( arreglo, size );
   reporteAlgoritmo reporte = (reporteAlgoritmo){ horaInicio, horaFinalizacion, tiempoEjecucion, numIntercambios, numComparaciones, porcentajeOrdenamiento };
   return reporte;
}

// Algoritmo Burbuja Mejorado
reporteAlgoritmo ordenarBurbujaBandera( int arreglo[ ], int size, time_t * tiempoLimite ){
   time_t tiempoNatural = time( NULL );
   struct tm horaInicio = * localtime( &tiempoNatural ), horaFinalizacion;
   int i, j, ordenado = 0;
   long long int numComparaciones = 0;
   long long int numIntercambios = 0;
   i = 1;
   clock_t tiempoInicio = clock( );
   while( i <= size && ordenado == 0 ){
      ordenado = 1;
      for( j = 0; j < size - 1; j++ ){
         numComparaciones++;
         if( arreglo[ j + 1 ] < arreglo[ j ] ){
            intercambiar( arreglo, j + 1, j );
            numIntercambios++;
            ordenado = 0;
         }
         if( tiempoLimite != NULL ){
            if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
               break;
            }
         }
      }
      if( tiempoLimite != NULL ){
         if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
            break;
         }
      }
      i++;
   }
   double tiempoEjecucion = ( clock( ) - tiempoInicio ) / CLOCKS_PER_SEC;
   tiempoNatural = time( NULL );
   horaFinalizacion = * localtime( &tiempoNatural );
   double porcentajeOrdenamiento = evaluarOrdenamiento( arreglo, size );
   reporteAlgoritmo reporte = (reporteAlgoritmo){ horaInicio, horaFinalizacion, tiempoEjecucion, numIntercambios, numComparaciones, porcentajeOrdenamiento };
   return reporte;
}

reporteAlgoritmo ordenarSeleccion( int arreglo[ ], int size, time_t * tiempoLimite ){
   time_t tiempoNatural = time( NULL );
   struct tm horaInicio = * localtime( &tiempoNatural ), horaFinalizacion;
   int i, j, posMinima;
   long long int numComparaciones = 0;
   long long int numIntercambios = 0;
   clock_t tiempoInicio = clock( );
   for( i = 0; i < size - 1; i++ ){
      posMinima = i;
      for( j = i + 1; j < size; j++ ){
         numComparaciones++;
         if( arreglo[ j ] < arreglo[ posMinima] ){
            posMinima = j;
         }
         if( tiempoLimite != NULL ){
            if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
               break;
            }
         }	
      }
      if( tiempoLimite != NULL ){
         if( time( NULL ) - tiempoNatural >= * tiempoLimite ){
            break;
         }
      }
      numComparaciones++;
      if( i != posMinima ){
         intercambiar( arreglo, i, posMinima );
         numIntercambios++;
      }		
   }
   double tiempoEjecucion = ( clock( ) - tiempoInicio ) / CLOCKS_PER_SEC;
   tiempoNatural = time( NULL );
   horaFinalizacion = * localtime( &tiempoNatural );
   double porcentajeOrdenamiento = evaluarOrdenamiento( arreglo, size );
   reporteAlgoritmo reporte = (reporteAlgoritmo){ horaInicio, horaFinalizacion, tiempoEjecucion, numIntercambios, numComparaciones, porcentajeOrdenamiento };
   return reporte;
}

void merge( int arreglo[ ], int posInicial, int posMitad, int posFinal, reporteAlgoritmo * reporte ){
   int tamArrayTemp = (posFinal - posInicial) + 1;
   int arregloParcial[tamArrayTemp];
   int indexMitadUno = posInicial;
   int indexMitadDos = posMitad + 1;
   int indexArregloParcial = 0;
   int indexArregloFinal;
   while(indexMitadUno <= posMitad && indexMitadDos <= posFinal){
      reporte->numComparaciones++;
      if(arreglo[indexMitadUno] <= arreglo[indexMitadDos]){
         arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
         reporte->numIntercambios++;
         indexMitadUno++;
      }
      else{
         arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
         indexMitadDos++;
         reporte->numIntercambios++;
      }
      indexArregloParcial++;
   }
   while(indexMitadUno <= posMitad){
      arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
      reporte->numIntercambios++;
      indexArregloParcial++;
      indexMitadUno++;
   }
   while(indexMitadDos <= posFinal){
      arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
      reporte->numIntercambios++;
      indexArregloParcial++;
      indexMitadDos++;
   }
   for( indexArregloParcial = 0; indexArregloParcial < tamArrayTemp; indexArregloParcial++ ){
      indexArregloFinal = posInicial + indexArregloParcial;
      arreglo[indexArregloFinal] = arregloParcial[indexArregloParcial];
      reporte->numIntercambios++;
   }
}

void mergeSort( int arreglo[], int posInicial, int posFinal, reporteAlgoritmo * reporte ){
   reporte->numComparaciones++;
   if(posInicial < posFinal){
      int posMitad = (posInicial + posFinal) / 2;
      mergeSort( arreglo, posInicial, posMitad, reporte );
      mergeSort( arreglo, posMitad + 1, posFinal, reporte );
      merge( arreglo, posInicial, posMitad, posFinal, reporte );
   }
}