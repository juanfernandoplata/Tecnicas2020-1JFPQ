#include "FuncionesCC.h"

void generarInventarios( local_t ** centroComercial, int pisos, int localesxPiso ){
   FILE * archivo;
   int i, j, k, a;
   char ruta[ 50 ] = "";
   mkdir( "./Inventarios" );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            strcpy( ruta, "./Inventarios/" );
            strcat( ruta, centroComercial[ i ][ j ].nombreLocal );
            for( a = 0; a < 50; a++ ){
               if( ruta[ a ] == '\n' ){
                  ruta[ a ] = '.';
                  break;
               }
            }
            strcat( ruta, "txt" );
            archivo = fopen( ruta, "w" );
            for( k = 0; k < centroComercial[ i ][ j ].inventario.numeroProductos; k++ ){
               fprintf( archivo, "Nombre del producto: %s", centroComercial[ i ][ j ].inventario.listaProductos[ k ] );
               fprintf( archivo, "Unidades: %d\n", centroComercial[ i ][ j ].inventario.listaCantidad[ k ] );
               fprintf( archivo, "Costo: %lf\n", centroComercial[ i ][ j ].inventario.listaCostos[ k ] );
               fprintf( archivo, "Precio: %lf\n", centroComercial[ i ][ j ].inventario.listaPrecios[ k ] );
               fprintf( archivo, "\n" );
            }
            fclose( archivo );
         }
      }
   }
}

void generarNominas( local_t ** centroComercial, int pisos, int localesxPiso ){
   FILE * archivo;
   int i, j, k, a;
   char ruta[ 50 ] = "";
   mkdir( "./Nominas" );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            strcpy( ruta, "./Nominas/" );
            strcat( ruta, centroComercial[ i ][ j ].nombreLocal );
            for( a = 0; a < 50; a++ ){
               if( ruta[ a ] == '\n' ){
                  ruta[ a ] = '.';
                  break;
               }
            }
            strcat( ruta, "txt" );
            archivo = fopen( ruta, "w" );
            for( k = 0; k < centroComercial[ i ][ j ].nomina.numeroEmpleados; k++ ){
               fprintf( archivo, "Nombre: %s", centroComercial[ i ][ j ].nomina.listaNombres[ k ] );
               fprintf( archivo, "Cargo: %s", centroComercial[ i ][ j ].nomina.listaCargos[ k ] );
               fprintf( archivo, "Salario: %lf\n", centroComercial[ i ][ j ].nomina.listaSalarios[ k ] );
               fprintf( archivo, "\n" );
            }
            fclose( archivo );
         }
      }
   }
}

void validarRangoValor( int minimo, int maximo, int * direccionVariable ){
   int i = 1;
   do{
      if( i > 1 ){
         printf( "El valor ingresado es invalido. Por favor intentelo nuevamente\n" );
      }
      scanf( "%d", direccionVariable );
      i++;
   } while( * direccionVariable < minimo || * direccionVariable > maximo );
}

int multiplicadorDecimal( int localesxPiso ){
   if( localesxPiso / 10 == 0 ){
      return 10;
   }
   return 10 * multiplicadorDecimal( localesxPiso / 10);
}

void imprimirLocalesOrdenados( local_t listaLocales[ ], int size, char mode ){
   int i;
   for( i = 0; i < size; i++ ){
      printf( "Nombre: %s", listaLocales[ i ].nombreLocal );
      printf( "ID: %d\n", listaLocales[ i ].idLocal );
      printf( "Piso: %d\n", listaLocales[ i ].pisoLocal );
      printf( "Numero local: %d\n", listaLocales[ i ].numLocalxPiso );
      if( mode == 'n' ){
         printf( "Numero de empleados: %d\n", listaLocales[ i ].nomina.numeroEmpleados );
      }
      else if( mode == 'i' ){
         printf( "Numero de productos: %d\n", listaLocales[ i ].inventario.numeroProductos );
      }
      else if( mode == 's' ){
         printf( "Ventas esta semana: %lf\n", listaLocales[ i ].indicadoresFinanzas.gananciasSemana );
      }
      else if( mode == 'm' ){
         printf( "Ventas este mes: %lf\n", listaLocales[ i ].indicadoresFinanzas.gananciasMes );
      }
      printf( "==============================\n" );
   }
   printf( "\n" );
}

void menuPrincipal( ){
   printf( "MENU PRINCIPAL\n" );
   printf( "1. Ingresar un nuevo local al sistema\n" );
   printf( "2. Registrar venta de un local\n" );
   printf( "3. Ver el numero de locales en uso\n" );
   printf( "4. Ver locales ubicados en un piso\n" );
   printf( "5. Modificar la informacion de un local\n" );
   printf( "6. Listar todos los locales\n" );
   printf( "7. Consultar informacion especifica de un local\n" );
   printf( "8. Eliminar un local del sistema\n" );
   printf( "9. Registrar pago de la renta de un local\n" );
   printf( "10. Generar registro de pagos\n" );
   printf( "11. Ordenar locales por numero de empleados\n" );
   printf( "12. Ordenar locales por tamanio de inventario\n" );
   printf( "13. Ordenar locales de un piso por numero de ventas esta semana\n" );
   printf( "14. Ordenar locales de un piso por numero de ventas este mes\n" );
   printf( "15. Salir\n" );
}

void * timer( void * arg ){
   type_threadData * threadData;
   threadData = ( type_threadData * )arg;
   local_t ** centroComercial = ( threadData->centroComercial );
   time_t timeDifIndSem, timeDifIndMes, timeDifIndAnio, timeDifRent;
   int i, j;
   while( !( * threadData->killThread ) ){
      for( i = 0; i < threadData->pisos; i++ ){
         for( j = 0; j < threadData->localesxPiso; j++ ){
            timeDifIndSem = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModSem ) / 604800;
            timeDifIndMes = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModMes ) / 2626560;
            timeDifIndAnio = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModAnio ) / 31536000;
            timeDifRent = ( time( NULL ) - centroComercial[ i ][ j ].renta.ultMod ) / 43776;
            if( timeDifRent > 0 ){
               centroComercial[ i ][ j ].renta.mesesMora++;
               centroComercial[ i ][ j ].renta.estadoPago = 1;
               centroComercial[ i ][ j ].renta.ultMod = time( NULL );
            }
            if( timeDifIndSem > 0 ){
               centroComercial[ i ][ j ].indicadoresFinanzas.gananciasSemana = 0;
               centroComercial[ i ][ j ].indicadoresFinanzas.ultModSem = time( NULL );
            }
            if( timeDifIndMes > 0 ){
               centroComercial[ i ][ j ].indicadoresFinanzas.gananciasMes = 0;
               centroComercial[ i ][ j ].indicadoresFinanzas.ultModMes = time( NULL );
            }
            if( timeDifIndAnio > 0 ){
               centroComercial[ i ][ j ].indicadoresFinanzas.gananciasAnio = 0;
               centroComercial[ i ][ j ].indicadoresFinanzas.ultModAnio = time( NULL );
            }
         }
      }
   }
   pthread_exit( 0 );
}

void evaluarRentas( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j;
   time_t timeDifIndSem, timeDifIndMes, timeDifIndAnio, timeDifRent;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         timeDifIndSem = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModSem ) / 604800;
         timeDifIndMes = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModMes ) / 2626560;
         timeDifIndAnio = ( time( NULL ) - centroComercial[ i ][ j ].indicadoresFinanzas.ultModAnio ) / 31536000;
         timeDifRent = ( time( NULL ) - centroComercial[ i ][ j ].renta.ultMod) / 2626560;
         if( timeDifRent > 0 ){
            centroComercial[ i ][ j ].renta.mesesMora += timeDifRent;
            centroComercial[ i ][ j ].renta.estadoPago = 1;
            centroComercial[ i ][ j ].renta.ultMod = time( NULL );
         }
         if( timeDifIndSem > 0 ){
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasSemana = 0;
            centroComercial[ i ][ j ].indicadoresFinanzas.ultModSem = time( NULL );
         }
         if( timeDifIndMes > 0 ){
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasMes = 0;
            centroComercial[ i ][ j ].indicadoresFinanzas.ultModMes = time( NULL );
         }
         if( timeDifIndAnio > 0 ){
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasAnio = 0;
            centroComercial[ i ][ j ].indicadoresFinanzas.ultModAnio = time( NULL );
         }
      }
   }
}

void generarListaIdsModificados( int ** listaIdsModificados, int pisos, int localesxPiso ){
   int i;
   * listaIdsModificados = malloc( pisos * localesxPiso * sizeof( int ) );
   for( i = 0; i <  pisos * localesxPiso; i++ ){
      ( * listaIdsModificados )[ i ] = -1;
   }
}

void reservarEspacioMemoria( local_t *** centroComercial, int localesxPiso, int pisos, int ** listaIdsModificados ){
   int i;
   * listaIdsModificados = malloc( pisos * localesxPiso * sizeof( int ) );
   * centroComercial = malloc( pisos * sizeof( local_t * ) );
   for( i = 0; i < pisos; i++ ){
      ( * centroComercial )[ i ] = malloc( localesxPiso * sizeof( local_t ) );
   }
}

void guardarCC( FILE * archivoBinario, local_t ** centroComercial, int * pisos, int * localesxPiso, int * listaIdsModificados, int * elementosListaIds ){
   int i;
   fwrite( localesxPiso, sizeof( int ), 1, archivoBinario );
   fwrite( pisos, sizeof( int ), 1, archivoBinario );
   fwrite( elementosListaIds, sizeof( int ), 1, archivoBinario );
   fwrite( listaIdsModificados, sizeof( int ), * elementosListaIds, archivoBinario );
   for( i = 0; i < * pisos; i++ ){
      fwrite( centroComercial[ i ], sizeof( local_t ), * localesxPiso, archivoBinario );
   }
}

void cargarCC( FILE * archivoBinario, local_t *** centroComercial, int * pisos, int * localesxPiso, int ** listaIdsModificados, int * elementosListaIds ){
   int i;
   fread( localesxPiso, sizeof( int ), 1, archivoBinario );
   fread( pisos, sizeof( int ), 1, archivoBinario );
   reservarEspacioMemoria( centroComercial, * localesxPiso, * pisos, listaIdsModificados );
   fread( elementosListaIds, sizeof( int ), 1, archivoBinario );
   fread( * listaIdsModificados, sizeof( int ), * elementosListaIds, archivoBinario );
   for( i = 0; i < * pisos; i++ ){
      fread( ( * centroComercial )[ i ], sizeof( local_t ), * localesxPiso, archivoBinario );
   }
}

void crearDirectorios( ){
   mkdir( "./Data" );
   mkdir( "./Pagos" );
//   mkdir( "./Inventarios Locales" );
}

local_t ** crearCC( int * pisos, int * localesxPiso ){
   local_t ** centroComercial;
   int i, j;
   printf( "Ingrese el numero de pisos del Centro Comercial: " );
   validarRangoValor( 1, INT_MAX, pisos );
   printf( "Ingrese el numero de locales por piso: " );
   validarRangoValor( 1, INT_MAX, localesxPiso );
   centroComercial = malloc( * pisos * sizeof( local_t * ) );
   for( i = 0; i < * pisos; i++ ){
      centroComercial[ i ] = malloc( * localesxPiso * sizeof( local_t ) );
   }
   for( i = 0; i < * pisos; i++ ){
      for( j = 0; j < * localesxPiso; j++ ){
         centroComercial[ i ][ j ].idLocal = -1;
      }
   }
   return centroComercial;
}

void listarNomina( type_nomina * nomina ){
   int i;
   for( i = 0; i < nomina->numeroEmpleados; i++ ){
      printf( "Nombre: %s", nomina->listaNombres[ i ] );
      printf( "Cargo: %s", nomina->listaCargos[ i ] );
      printf( "Salario: %lf\n", nomina->listaSalarios[ i ] );
      printf( "\n" );
   }
   printf( "\n" );
}

void listarInventario( type_inventario * inventario ){
   int i;
   for( i = 0; i < inventario->numeroProductos; i++ ){
      printf( "Nombre del producto: %s", inventario->listaProductos[ i ] );
      printf( "Disponibilidad: %d\n", inventario->listaCantidad[ i ] );
      printf( "Costo: %lf\n", inventario->listaCostos[ i ] );
      printf( "Precio: %lf\n", inventario->listaPrecios[ i ] );
      printf( "\n" );
   }
   printf( "Indicador de rentabilidad: %lf\n", inventario->indicadorRentabilidad );
   printf( "\n" );
}

int * imprimirInfoLocal( local_t ** centroComercial, int pisos, int localesxPiso, int id ){
   int i, j, validar = 0;
   int * indices = malloc( 2 * sizeof( int ) );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == id ){
            printf( "\n" );
            printf( "Nombre: %s", centroComercial[ i ][ j ].nombreLocal );
            printf( "ID: %d\n", centroComercial[ i ][ j ].idLocal );
            printf( "Piso: %d\n", centroComercial[ i ][ j ].pisoLocal );
            printf( "Numero local: %d\n", centroComercial[ i ][ j ].numLocalxPiso );
            printf( "===========================\n" );
            validar = 1;
            break;
         }
      }
      if( validar ){
         break;
      }
   }
   printf( "\n" );
   indices[ 0 ] = i;
   indices[ 1 ] = j;
   return indices;
}

int validarId( int * listaIdsModificados, int * dimensionLista, int id ){
   int i = 0, validar = 0;
   while( listaIdsModificados[ i ] != -1 && i < * dimensionLista && !validar ){
      if( listaIdsModificados[ i ] == id ){
         validar = 1;
         break;
      }
      i++;
   }
   if( validar == 0 ){
      i = -1;
   }
   return i;
}

void menuCategoria( ){
   printf( "Seleccione la categoria del local:\n" );
   printf( "1. Ropa\n" );
   printf( "2. Deporte\n" );
   printf( "3. Teconologia\n" );
   printf( "4. Entretenimiento\n" );
   printf( "5. Viveres\n" );
   printf( "6. Comida\n" );
   printf( "\n" );
}

void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds ){
   time_t tiempo;
   int opcion, numProductos, numEmpleados, a, indice, posibleId, nuevoId, pisoLocal, numeroLocal, validar = 1;
   int * indices;
   double indicadorRentabilidad;
   system( "cls" );
   do{
      printf( "Ingrese el piso donde desea ubicar el local: " );
      scanf( " %d", &pisoLocal );
      printf( "Ingrese el numero del local en el piso: " );
      scanf( " %d", &numeroLocal );
      if( pisoLocal >= 1 && pisoLocal <= pisos && numeroLocal >= 1 && numeroLocal <= localesxPiso ){
         if( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal == -1 ){
            posibleId = pisoLocal * multiplicadorDecimal( localesxPiso ) + numeroLocal;
            indice = validarId( listaIdsModificados, elementosListaIds, posibleId );
            if( indice == -1 ){
               centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal = posibleId;
            }
            else{
               printf( "Debido a un conflicto de ID's la informacion del local no podra ser almacenada hasta que se modifique el ID del siguiente local:\n" );
               indices = imprimirInfoLocal( centroComercial, pisos, localesxPiso, posibleId );
               printf( "Ingrese el nuevo ID del local: " );
               scanf( "%d", &nuevoId );
               centroComercial[ indices[ 0 ] ][ indices[ 1 ] ].idLocal = nuevoId;
               for( a = indice; a < * elementosListaIds - 1; a++ ){
                  listaIdsModificados[ a ] = listaIdsModificados[ a + 1 ];
               }
               (* elementosListaIds )--;
               centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal = posibleId;
               printf( "El ID del local se ha modificado con exito. Ya puede agregar el local\n" );
            }
            printf( "Ingrese el nombre del local: " );
            fflush( stdin );
            fgets( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nombreLocal, 35, stdin );
            printf( "Ingrese el numero de empleados que figuran en la nomina del local: " );
            scanf( "%d", &numEmpleados );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nomina.numeroEmpleados = numEmpleados;
            for( a = 0; a < numEmpleados; a++ ){
               printf( "Ingrese el nombre del empleado %d: ", a + 1 );
               fflush( stdin );
               fgets( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nomina.listaNombres[ a ], 30, stdin );
               printf( "Ingrese el cargo del empleado %d: ", a + 1 );
               fflush( stdin );
               fgets( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nomina.listaCargos[ a ], 30, stdin );
               printf( "Ingrese el salario del empleado %d: ", a + 1 );
               fflush( stdin );
               scanf( "%lf", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nomina.listaSalarios[ a ] );
            }
            printf( "\n" );
            menuCategoria( );
            validarRangoValor( 1, 6, &opcion );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].categoria = opcion - 1;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.historicoGanancias = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.gananciasSemana = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.ultModSem = time( NULL );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.gananciasMes = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.ultModMes = time( NULL );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.gananciasAnio = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].indicadoresFinanzas.ultModAnio = time( NULL );
            printf( "Ingrese el numero de productos en el inventario del local: " );
            scanf( "%d", &numProductos );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.numeroProductos = numProductos;
            for( a = 0; a < numProductos; a++ ){
               printf( "Ingrese el nombre del producto %d: ", a + 1 );
               fflush( stdin );
               fgets( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaProductos[ a ], 30, stdin );
               printf( "Ingrese la cantidad de unidades disponibles del producto %d: ", a + 1 );
               fflush( stdin );
               scanf( "%d", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaCantidad[ a ] );
               printf( "Ingrese el costo al que el local adquirio cada unidad del producto %d: ", a + 1 );
               scanf( "%lf", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaCostos[ a ] );
               printf( "Ingrese el precio de venta de cada unidad del producto %d: ", a + 1 );
               scanf( "%lf", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaPrecios[ a ] );
               indicadorRentabilidad += centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaPrecios[ a ] / centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.listaCostos[ a ];
            }
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].inventario.indicadorRentabilidad = indicadorRentabilidad / ( double )numProductos * 100.0;
            printf( "%lf\n", indicadorRentabilidad / ( double )numProductos * 100.0 );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].pisoLocal = pisoLocal;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].numLocalxPiso = numeroLocal;
            printf( "Ingrese el numero de metros cuadrados del local: " );
            scanf( "%d", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].metrosCuadradosLocal );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].renta.estadoPago = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].renta.mesesMora = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].renta.rentasPagas = 0;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].renta.ultMod = time( NULL );
            tiempo = time( NULL );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].fechaIngreso = * localtime( &tiempo );
            if( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].fechaIngreso.tm_mon == 1 && centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].fechaIngreso.tm_mday == 29 ){
               centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].fechaIngreso.tm_mday--;
            }
            break;
         }      
         else{
            printf( "El local solicitado ya se encuentra en uso. Por favor ingrese una ubicacion diferente para el local\n" );
         }
      }
      else{
         printf( "El local indicado no existe. Por favor ingrese una ubicacion diferente para el local\n" );
      }
   } while( 1 );
   printf( "\n" );
}

void numeroLocalesEnUso( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j, localesDisponibles = 0;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == -1){
            localesDisponibles++;
         }
      }
   }
   printf( "El numero de locales en uso es: %d\n", pisos * localesxPiso - localesDisponibles );
   printf( "\n" );
}

void listarLocalesPorPiso( local_t ** centroComercial, int localesxPiso ){
   int piso, i;
   printf( "Ingrese el numero del piso: " );
   scanf( "%d", &piso );
   for( i = 0; i < localesxPiso; i++ ){
      if( centroComercial[ piso - 1 ][ i ].idLocal != -1 ){
         printf( "%s", centroComercial[ piso - 1 ][ i ].nombreLocal );
         printf( "===========================\n" );
      }
   }
}

void imprimirCategoria( int opcion ){
   if( opcion == 0 ){
      printf( "Categoria: Ropa\n" );
   }
   else if( opcion == 1 ){
      printf( "Categoria: Deporte\n" );
   }
   else if( opcion == 2 ){
      printf( "Categoria: Tenologia\n" );
   }
   else if( opcion == 3 ){
      printf( "Categoria: Entretenimiento\n" );
   }
   else if( opcion == 4 ){
      printf( "Categoria: Viveres\n" );
   }
   else if( opcion == 5 ){
      printf( "Categoria: Comida\n" );
   }
}

void imprimirFechaIngreso( struct tm * fecha ){
   printf( "Fecha de ingreso al sistema: %d/%d/%d\n", fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900 );
}

void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            printf( "Nombre: %s", centroComercial[ i ][ j ].nombreLocal );
            printf( "ID: %d\n", centroComercial[ i ][ j ].idLocal );
            imprimirCategoria( centroComercial[ i ][ j ].categoria );
            printf( "Piso: %d\n", centroComercial[ i ][ j ].pisoLocal );
            printf( "Numero local: %d\n", centroComercial[ i ][ j ].numLocalxPiso );
            printf( "Metros cuadrados: %d\n", centroComercial[ i ][ j ].metrosCuadradosLocal );
            if( centroComercial[ i ][ j ].renta.estadoPago == 0 ){
               printf( "Estado de pago: Al dia\n" );
            }
            else{
               printf( "Estado de pago: En mora\n" );
            }
            imprimirFechaIngreso( &centroComercial[ i ][ j ].fechaIngreso );
            printf( "===========================\n" );
         }
      }
   }
}

void menuModificacion( ){
   printf( "Eliga el campo que desea modificar:\n" );
   printf( "1. Nombre\n" );
   printf( "2. Ubicacion\n" );
   printf( "3. ID\n" );
   printf( "4. Nomina\n" );
   printf( "5. Inventario\n" );
}

void menuNomina( ){
   printf( "Seleccione la accion que desea realizar:\n" );
   printf( "1. Agregar empleado\n" );
   printf( "2. Eliminar empleado\n" );
   printf( "3. Modificar empleado\n" );
}

void menuModEmp( ){
   printf( "Seleccione la accion que desea realizar:\n" );
   printf( "1. Modificar el cargo de un empleado\n" );
   printf( "2. Modificar el salario de un empleado\n" );
}

void listarNombresNomina( type_nomina * nomina ){
   int i;
   for( i = 0; i < nomina->numeroEmpleados; i++ ){
      printf( "%d. %s", i + 1, nomina->listaNombres[ i ] );
   }
   printf( "\n" );
}

modificarNomina( local_t * local ){
   int a, opcionMod, opcionEmp, numeroEmpleado;
   menuNomina( );
   validarRangoValor( 1, 3, &opcionMod );
   switch( opcionMod ){
      case 1: printf( "Ingrese el nombre del empleado: " );
              fflush( stdin );
              fgets( local->nomina.listaNombres[ local->nomina.numeroEmpleados ], 30, stdin );
              printf( "Ingrese el cargo del empleado: " );
              fflush( stdin );
              fgets( local->nomina.listaCargos[ local->nomina.numeroEmpleados ], 30, stdin );
              printf( "Ingrese el salario del empleado: " );
              fflush( stdin );
              scanf( "%lf", &local->nomina.listaSalarios[ local->nomina.numeroEmpleados ] );
              local->nomina.numeroEmpleados++;
              break;
      case 2: listarNombresNomina( &local->nomina );
              printf( "Seleccione el empleado que desea eliminar\n" );
              validarRangoValor( 1, local->nomina.numeroEmpleados, &numeroEmpleado );
              for( a = numeroEmpleado - 1; a < local->nomina.numeroEmpleados - 1; a++ ){
                 strcpy( local->nomina.listaNombres[ a ], local->nomina.listaNombres[ a + 1 ] );
                 strcpy( local->nomina.listaCargos[ a ], local->nomina.listaCargos[ a + 1 ] );
                 local->nomina.listaSalarios[ a ] = local->nomina.listaSalarios[ a + 1 ];
              }
              local->nomina.numeroEmpleados--;
              break;
      case 3: listarNombresNomina( &local->nomina );
              printf( "Seleccione el empleado que desea modificar\n" );
              validarRangoValor( 1, local->nomina.numeroEmpleados, &numeroEmpleado );
              menuModEmp( );
              validarRangoValor( 1, 2, &opcionEmp );
              switch( opcionEmp ){
                 case 1: printf( "Ingrese el nuevo cargo del empleado: " );
                         fflush( stdin );
                         fgets( local->nomina.listaCargos[ numeroEmpleado - 1 ], 30, stdin );
                         break;
                 case 2: printf( "Ingrese el nuevo salario del empleado: " );
                         fflush( stdin );
                         scanf( "%lf", &local->nomina.listaSalarios[ numeroEmpleado - 1 ] );
                         break;
              }
              break;
   }
}

void menuInventario( ){
   printf( "Seleccione la accion que desea realizar:\n" );
   printf( "1. Agregar producto\n" );
   printf( "2. Eliminar producto\n" );
   printf( "3. Modificar producto\n" );
}

void menuModProd( ){
   printf( "Seleccione la accion que desea realizar:\n" );
   printf( "1. Modificar el nombre de un producto\n" );
   printf( "2. Modificar la disponibilidad de un producto\n" );
   printf( "3. Modificar el costo de un producto\n" );
   printf( "4. Modificar el precio de un producto\n" );
}

void recalcularIndicador( type_inventario * inventario ){
   int i;
   double indicadorRentabilidad;
   for( i = 0; i < inventario->numeroProductos; i++ ){
      indicadorRentabilidad += inventario->listaPrecios[ i ] / inventario->listaCostos[ i ];
   }
   indicadorRentabilidad = indicadorRentabilidad / ( double )inventario->numeroProductos * 100.0;
}

void listarNombresInventario( type_inventario * inventario ){
   int i;
   for( i = 0; i < inventario->numeroProductos; i++ ){
      printf( "%d. %s", i + 1, inventario->listaProductos[ i ] );
   }
   printf( "\n" );
}

modificarInventario( local_t * local ){
   int a, opcionMod, opcionProd, numeroProducto;
   menuInventario( );
   validarRangoValor( 1, 3, &opcionMod );
   switch( opcionMod ){
      case 1: printf( "Ingrese el nombre del producto: " );
              fflush( stdin );
              fgets( local->inventario.listaProductos[ local->inventario.numeroProductos ], 30, stdin );
              printf( "Ingrese la disponibilidad del producto: " );
              fflush( stdin );
              scanf( "%d", &local->inventario.listaCantidad[ local->inventario.numeroProductos ] );
              printf( "Ingrese el costo del producto: " );
              scanf( "%lf", &local->inventario.listaCostos[ local->inventario.numeroProductos ] );
              printf( "Ingrese el precio del producto: " );
              scanf( "%lf", &local->inventario.listaPrecios[ local->inventario.numeroProductos ] );
              local->inventario.numeroProductos++;
              recalcularIndicador( &local->inventario );
              break;
      case 2: listarNombresInventario( &local->inventario );
              printf( "Seleccione el producto que desea eliminar\n" );
              validarRangoValor( 1, local->inventario.numeroProductos, &numeroProducto );
              for( a = numeroProducto - 1; a < local->inventario.numeroProductos - 1; a++ ){
                 strcpy( local->inventario.listaProductos[ a ], local->inventario.listaProductos[ a + 1 ] );
                 local->inventario.listaCantidad[ a ] = local->inventario.listaCantidad[ a + 1 ];
                 local->inventario.listaCostos[ a ] = local->inventario.listaCostos[ a + 1 ];
                 local->inventario.listaPrecios[ a ] = local->inventario.listaPrecios[ a + 1 ];
              }
              local->inventario.numeroProductos--;
              recalcularIndicador( &local->inventario );
              break;
      case 3: listarNombresInventario( &local->inventario );
              listarNombresInventario( &local->inventario );
              printf( "Seleccione el producto que desea modificar\n" );
              validarRangoValor( 1, local->inventario.numeroProductos, &numeroProducto );
              menuModProd( );
              validarRangoValor( 1, 4, &opcionProd );
              switch( opcionProd ){
                 case 1: printf( "Ingrese el nuevo nombre del producto: " );
                         fflush( stdin );
                         fgets( local->inventario.listaProductos[ numeroProducto - 1 ], 30, stdin );
                         break;
                 case 2: printf( "Ingrese la nueva disponibilidad del producto: " );
                         fflush( stdin );
                         scanf( "%d", &local->inventario.listaCantidad[ numeroProducto - 1 ] );
                         break;
                 case 3: printf( "Ingrese el nuevo costo del producto: " );
                         fflush( stdin );
                         scanf( "%lf", &local->inventario.listaCostos[ numeroProducto - 1 ] );
                         recalcularIndicador( &local->inventario );
                         break;
                 case 4: printf( "Ingrese el nuevo costo del producto: " );
                         fflush( stdin );
                         scanf( "%lf", &local->inventario.listaPrecios[ numeroProducto - 1 ] );
                         recalcularIndicador( &local->inventario );
                         break;
              }
              break;
   }
}

void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds ){
   enum ruta{
      NOMBRE = 1,
      UBICACION = 2,
      ID = 3,
      NOMINA = 4,
      INVENTARIO = 5
   };
   int a, b, i, j, id, idNuevo, opcion, pisoLocal, numeroLocal, repetido = 0, idEncontrado = 0;;
   char nombreLocalTemp[ 35 ];
   listarLocales( centroComercial, pisos, localesxPiso );
   do{
      printf( "Ingrese el ID del local que desea modificar: " );
      scanf( "%d", &id );
      for( i = 0; i < pisos; i++ ){
         for( j = 0; j < localesxPiso; j++ ){
            if( centroComercial[ i ][ j ].idLocal == id ){
               idEncontrado = 1;
               menuModificacion( );
               validarRangoValor( 1, 5, &opcion );
               switch( opcion ){
                  case NOMBRE: printf( "Ingrese el nuevo nombre del local: " );
                               fflush( stdin );
                               fgets( centroComercial[ i ][ j ].nombreLocal, 35, stdin );
                               break;
                  case UBICACION: printf( "Ingrese el piso al que desea mover el local: " );
                                  scanf( "%d", &pisoLocal );
                                  printf( "Ingrese el numero del local en el piso: " );
                                  scanf( "%d", &numeroLocal );
                                  if( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal == -1 ){
                                     strcpy( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nombreLocal, centroComercial[ i ][ j ].nombreLocal );
                                     centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].pisoLocal = pisoLocal;
                                     centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].numLocalxPiso = numeroLocal;
                                     centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal = pisoLocal * multiplicadorDecimal( localesxPiso ) + numeroLocal;
                                     centroComercial[ i ][ j ].idLocal = -1;                                     
                                     printf( "El nombre del local ha sido modificado con exito\n" );
                                  }
                                  else{
                                     printf( "El local solicitado ya esta en uso. Desea intercambiar las ubicaciones de los dos locales?\n" );
                                     printf( "1. Si\n" );
                                     printf( "2. No\n" );
                                     scanf( "%d", &opcion );
                                     if( opcion == 1 ){
                                        strcpy( nombreLocalTemp, centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nombreLocal );
                                        strcpy( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nombreLocal, centroComercial[ i ][ j ].nombreLocal );
                                        strcpy( centroComercial[ i ][ j ].nombreLocal, nombreLocalTemp );
                                        printf( "La ubicacion de los locales en el registro ha sido intercambiada con exito\n" );
                                     }
                                     else{
                                        printf( "No sera modificada ninguna informacion\n" );
                                     }
                                  }
                                  break;
                  case ID: printf( "Ingrese el nuevo ID: " );
                           validarRangoValor( 1, INT_MAX, &idNuevo );
                           if( validarId( listaIdsModificados, elementosListaIds, idNuevo ) != -1 ){
                              printf( "El ID solicitdo ya fue seleccionado anteriormente. No se realizaran cambios\n" );
                           }
                           else{
                              for( a = 0; a < pisos; a++ ){
                                 for( b = 0; b < localesxPiso; b++ ){
                                    if( centroComercial[ a ][ b ].idLocal == idNuevo ){
                                       printf( "El ID solicitado ya existe. No se realizaran cambios\n" );
                                       repetido = 1;
                                       break;
                                    }
                                  }
                                  if( repetido ){
                                    break;
                                  }
                              }
                              if( !repetido ){
                                 centroComercial[ i ][ j ].idLocal = idNuevo;
                                 printf( "El ID en el registro se ha modificado con exito\n" );
                                 int indice = validarId( listaIdsModificados, elementosListaIds, id );
                                 if( indice != -1 ){
                                    for( a = indice; a < * elementosListaIds - 1; a++ ){
                                       listaIdsModificados[ a ] = listaIdsModificados[ a + 1 ];
                                    }
                                    listaIdsModificados[ * elementosListaIds - 1 ] = idNuevo;
                                 }
                                 else{
                                    listaIdsModificados[ ( * elementosListaIds )++ ] = idNuevo;
                                 }
                              }
                           }
                           break;
                  case NOMINA: modificarNomina( &centroComercial[ i ][ j ] );
                               break;
                  case INVENTARIO: modificarInventario( &centroComercial[ i ][ j ] );
                               break;
               }
            }
         }
      }
      if( !idEncontrado ){
         printf( "El ID solicitado no fue encontrado en el registro. Por favor intentelo nuevamente\n" );
      }
   } while( !idEncontrado );
}

void registrarVentaLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   int unidades, opcion, numeroProducto, i, j, id, idEncontrado = 0;
   listarLocales( centroComercial, pisos, localesxPiso );
   printf( "Ingrese el ID del local que desea consultar: " );
   scanf( "%d", &id );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == id ){
            listarNombresInventario( &centroComercial[ i ][ j ].inventario );
            printf( "Ingrese el producto vendido: " );
            scanf( "%d", &numeroProducto );
            printf( "Ingrese el numero de unidades vendidas segun la disponibilidad: " );
            validarRangoValor( 1, centroComercial[ i ][ j ].inventario.listaCantidad[ numeroProducto - 1 ], &unidades );
            centroComercial[ i ][ j ].inventario.listaCantidad[ numeroProducto - 1 ] -= unidades;
            centroComercial[ i ][ j ].indicadoresFinanzas.historicoGanancias += ( centroComercial[ i ][ j ].inventario.listaPrecios[ numeroProducto - 1 ] - centroComercial[ i ][ j ].inventario.listaCostos[ numeroProducto - 1 ] ) * unidades;
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasSemana += ( centroComercial[ i ][ j ].inventario.listaPrecios[ numeroProducto - 1 ] - centroComercial[ i ][ j ].inventario.listaCostos[ numeroProducto - 1 ] ) * unidades;
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasMes += ( centroComercial[ i ][ j ].inventario.listaPrecios[ numeroProducto - 1 ] - centroComercial[ i ][ j ].inventario.listaCostos[ numeroProducto - 1 ] ) * unidades;
            centroComercial[ i ][ j ].indicadoresFinanzas.gananciasAnio += ( centroComercial[ i ][ j ].inventario.listaPrecios[ numeroProducto - 1 ] - centroComercial[ i ][ j ].inventario.listaCostos[ numeroProducto - 1 ] ) * unidades;
            idEncontrado = 1;
            break;
         }
      }
      if( idEncontrado ){
         break;
      }
   }
}

menuInfoLocal( ){
   printf( "Seleccione la informacion que desea consultar:\n" );
   printf( "1. Consultar nomina\n" );
   printf( "2. Consultar inventario\n" );
}

void consultarInfoLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   int opcion, i, j, id, idEncontrado = 0;
   listarLocales( centroComercial, pisos, localesxPiso );
   printf( "Ingrese el ID del local que desea consultar: " );
   scanf( "%d", &id );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == id ){
            menuInfoLocal( );
            validarRangoValor( 1, 2, &opcion );
            switch( opcion ){
              case 1: listarNomina( &centroComercial[ i ][ j ].nomina );
                      break;
              case 2: listarInventario( &centroComercial[ i ][ j ].inventario );
                      break;
            }
            idEncontrado = 1;
            break;
         }
      }
      if( idEncontrado ){
         break;
      }
   }
}

void eliminarLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j, id, salida = 0;
   listarLocales( centroComercial, pisos, localesxPiso );
   printf( "Ingrese el ID del local que desea eliminar: " );
   scanf( "%d", &id );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == id ){
            centroComercial[ i ][ j ].idLocal = -1;
            salida = 1;
         }
         if( salida ){
            break;
         }
      }
      if( salida ){
         break;
      }
   }
   if( salida ){
      printf( "El local ha sido eliminado exitosamente del registro\n" );
   }
   else{
      printf( "El ID solicitado no fue encontrado en el registro. No se elimino ningun local del registro\n" );
   }
}

void registrarPagoRentaLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j, id, idEncontrado = 0;
   listarLocales( centroComercial, pisos, localesxPiso );
   printf( "Ingrese el ID del local que realizo el pago: " );
   scanf( "%d", &id );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal == id ){
            if( centroComercial[ i ][ j ].renta.mesesMora > - 1 ){
               centroComercial[ i ][ j ].renta.mesesMora--;
               if( centroComercial[ i ][ j ].renta.mesesMora < 1 ){
                  centroComercial[ i ][ j ].renta.estadoPago = 0;
               }
               printf( "El pago de la renta del local se ha registrado con exito\n" );
            }
            else{
               printf( "El local solicitado ya realizo el pago de la renta de este mes. No se registraran pagos\n" );
            }
            idEncontrado = 1;
            break;
         }
      }
      if( idEncontrado ){
         break;
      }
   }
   if( !idEncontrado ){
      printf( "El ID solicitado no fue encontrado en el registro. No se registraran pagos\n" );
   }
}

void generarRegistroDePagos( local_t ** centroComercial, int pisos, int localesxPiso ){
   FILE * registro;
   int i, j;
   double costoMetroCuadrado;
   registro = fopen( "./Pagos/Registro De Pagos.txt", "w" );
   printf( "Ingrese el costo del metro cuadrado a la fecha: " );
   scanf( "%lf", &costoMetroCuadrado );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            fprintf( registro, "Nombre: %s", centroComercial[ i ][ j ].nombreLocal );
            fprintf( registro, "ID: %d\n", centroComercial[ i ][ j ].idLocal );
            fprintf( registro, "Costo de la renta: %lf\n", ( double )centroComercial[ i ][ j ].metrosCuadradosLocal * costoMetroCuadrado );
            if( centroComercial[ i ][ j ].renta.estadoPago == 0 ){
               fprintf( registro, "Estado de pago: Al dia\n" );
            }
            else{
               fprintf( registro, "Estado de pago: En mora\n" );
               fprintf( registro, "Meses de mora: %d\n", centroComercial[ i ][ j ].renta.mesesMora );
            }
            fprintf( registro, "===========================\n" );
         }
      }
   }
   fclose( registro );
}

void intercambiar( local_t arreglo[ ], int posicion1, int posicion2 ){
   local_t temp = arreglo[ posicion1 ];
   arreglo[ posicion1 ] = arreglo[ posicion2 ];
   arreglo[ posicion2 ] = temp;
}

void ordenarSeleccion( local_t arreglo[ ], int size ){
   int i, j, posMinima;
   for( i = 0; i < size - 1; i++ ){
      posMinima = i;
      for( j = i + 1; j < size; j++ ){
         if( arreglo[ j ].nomina.numeroEmpleados < arreglo[ posMinima].nomina.numeroEmpleados ){
            posMinima = j;
         }	
      }
      if( i != posMinima ){
         intercambiar( arreglo, i, posMinima );
      }	
   }
}

void ordenarInsercion( local_t arreglo[ ], int size ){
   int i, j;
   local_t temp;
   for (i = 1; i < size; i++) {
      temp = arreglo[i];
      j = i;
      while( temp.inventario.numeroProductos < arreglo[j - 1].inventario.numeroProductos && j > 0 ){
         arreglo[j] = arreglo[j - 1];
         j--;
      }
      arreglo[j] = temp;
   }
}

int partirYOrdenarPivoteInicial(local_t arreglo[], int posPrimerElem, int posUltimoElem){
   int valorPivote = arreglo[posPrimerElem].indicadoresFinanzas.gananciasMes;
   int posIzquierda = posPrimerElem + 1;
   int posDerecha = posUltimoElem;
   do{
      while(posIzquierda <= posDerecha && arreglo[posIzquierda].indicadoresFinanzas.gananciasMes <= valorPivote){
         posIzquierda++;
      }
      while(posIzquierda <= posDerecha && arreglo[posDerecha].indicadoresFinanzas.gananciasMes > valorPivote){
         posDerecha--;
      }
      if(posIzquierda < posDerecha){
         intercambiar(arreglo, posIzquierda, posDerecha);
         posIzquierda++;
         posDerecha--;
      }
   } while (posIzquierda <= posDerecha);
   if(arreglo[posDerecha].indicadoresFinanzas.gananciasMes != valorPivote){
      intercambiar(arreglo, posPrimerElem, posDerecha);
   }
   return posDerecha;
}

void quickSort( local_t arreglo[ ], int posIzquierda, int posDerecha ){
   int posPivote;
   if( posIzquierda < posDerecha ){
      posPivote = partirYOrdenarPivoteInicial(arreglo, posIzquierda, posDerecha);
      quickSort(arreglo, posIzquierda, posPivote - 1);
      quickSort(arreglo, posPivote + 1, posDerecha);
   }
}

void merge( local_t arreglo[ ], int posInicial, int posMitad, int posFinal ){
   int tamArrayTemp = (posFinal - posInicial) + 1;
   local_t arregloParcial[tamArrayTemp];
   int indexMitadUno = posInicial;
   int indexMitadDos = posMitad + 1;
   int indexArregloParcial = 0;
   int indexArregloFinal;
   while(indexMitadUno <= posMitad && indexMitadDos <= posFinal){
      if(arreglo[indexMitadUno].indicadoresFinanzas.gananciasSemana <= arreglo[indexMitadDos].indicadoresFinanzas.gananciasSemana){
         arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
         indexMitadUno++;
      }
      else{
         arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
         indexMitadDos++;
      }
      indexArregloParcial++;
   }
   while(indexMitadUno <= posMitad){
      arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
      indexArregloParcial++;
      indexMitadUno++;
   }
   while(indexMitadDos <= posFinal){
      arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
      indexArregloParcial++;
      indexMitadDos++;
   }
   for( indexArregloParcial = 0; indexArregloParcial < tamArrayTemp; indexArregloParcial++ ){
      indexArregloFinal = posInicial + indexArregloParcial;
      arreglo[indexArregloFinal] = arregloParcial[indexArregloParcial];
   }
}

void mergeSort( local_t arreglo[], int posInicial, int posFinal ){
   if(posInicial < posFinal){
      int posMitad = (posInicial + posFinal) / 2;
      mergeSort( arreglo, posInicial, posMitad );
      mergeSort( arreglo, posMitad + 1, posFinal );
      merge( arreglo, posInicial, posMitad, posFinal );
   }
}

void ordenarPorVentasSemana( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, pisoOrdenar, numeroLocales = 0;
   local_t listaLocales[ pisos * localesxPiso ];
   printf( "Ingrese el numero del piso que desea ordenar: " );
   validarRangoValor( 1, pisos, &pisoOrdenar );
   for( i = 0; i < localesxPiso; i++ ){
       if( centroComercial[ pisoOrdenar - 1 ][ i ].idLocal != -1  ){
         listaLocales[ numeroLocales ] = centroComercial[ pisoOrdenar - 1 ][ i ];
         numeroLocales++;
      }
   }
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 's' );
   mergeSort( listaLocales, 0, numeroLocales );
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 's' );
}

void ordenarPorVentasMes( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, pisoOrdenar, numeroLocales = 0;
   local_t listaLocales[ pisos * localesxPiso ];
   printf( "Ingrese el numero del piso que desea ordenar: " );
   validarRangoValor( 1, pisos, &pisoOrdenar );
   for( i = 0; i < localesxPiso; i++ ){
       if( centroComercial[ pisoOrdenar - 1 ][ i ].idLocal != -1  ){
         listaLocales[ numeroLocales ] = centroComercial[ pisoOrdenar - 1 ][ i ];
         numeroLocales++;
      }
   }
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 'm' );
   quickSort( listaLocales, 0, numeroLocales );
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 'm' );
}

void ordenarPorNumeroEmpleados( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j, k, numeroLocales = 0;
   local_t listaLocales[ pisos * localesxPiso ];
   k = 0;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1  ){
            listaLocales[ k ] = centroComercial[ i ][ j ];
            k++;
            numeroLocales++;
         }
      }
   }
   ordenarSeleccion( listaLocales, numeroLocales );
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 'n' );
}

void ordenarPorTamanioInventario( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j, k, numeroLocales = 0;
   local_t listaLocales[ pisos * localesxPiso ];
   k = 0;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1  ){
            listaLocales[ k ] = centroComercial[ i ][ j ];
            k++;
            numeroLocales++;
         }
      }
   }
   ordenarInsercion( listaLocales, numeroLocales );
   imprimirLocalesOrdenados( listaLocales, numeroLocales, 'i' );
}

