#include "FuncionesCC.h"

void evaluarRentas( local_t ** centroComercial, int pisos, int localesxPiso, struct tm * tiempoActualizado ){
   int i, j, difAnios, difMeses, disDias, difFinal;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         difAnios = tiempoActualizado->tm_year - centroComercial[ i ][ j ].fechaIngreso.tm_year;
         difFinal = difAnios * 12;
         if( tiempoActualizado->tm_mon >= centroComercial[ i ][ j ].fechaIngreso.tm_mon ){
            difMeses = tiempoActualizado->tm_mon - centroComercial[ i ][ j ].fechaIngreso.tm_mon;
            difFinal += difMeses;
         }
         else{
            difFinal += tiempoActualizado->tm_mon;
         }
         if( tiempoActualizado->tm_mday < centroComercial[ i ][ j ].fechaIngreso.tm_mday ){
            difFinal--;
         }
         centroComercial[ i ][ j ].renta.mesesMora += difFinal;
         if( difFinal > 0 ){
            centroComercial[ i ][ j ].renta.estadoPago = 1;
         }
      }
   }
}

void menuPrincipal( ){
   printf( "MENU PRINCIPAL\n" );
   printf( "1. Ingresar un nuevo local al sistema\n" );
   printf( "2. Ver el numero de locales en uso\n" );
   printf( "3. Ver locales ubicados en un piso\n" );
   printf( "4. Modificar la informacion de un local\n" );
   printf( "5. Listar todos los locales\n" );
   printf( "6. Eliminar un local del sistema\n" );
   printf( "7. Reiniciar estados de pago\n" );
   printf( "8. Registrar pago de la renta de un local\n" );
   printf( "9. Generar registro de pagos\n" );
   printf( "10. Salir\n" );
}

void imprimirLista( int lista[ ], int size ){
   int i;
   for( i = 0; i < size; i++ ){
      printf( "%d ", lista[ i ] );
   }
   printf( "\n" );
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

void generarListaIdsModificados( int ** listaIdsModificados, int pisos, int localesxPiso ){
   int i;
   * listaIdsModificados = malloc( pisos * localesxPiso * sizeof( int ) );
   for( i = 0; i <  pisos * localesxPiso; i++ ){
      ( * listaIdsModificados )[ i ] = -1;
   }
   imprimirLista( * listaIdsModificados, pisos * localesxPiso );
}

void reservarEspacioMemoria( local_t *** centroComercial, int localesxPiso, int pisos, int ** listaIdsModificados ){
   int i;
   * listaIdsModificados = malloc( pisos * localesxPiso * sizeof( int ) );
   * centroComercial = malloc( pisos * sizeof( local_t * ) );
   for( i = 0; i < pisos; i++ ){
      ( * centroComercial )[ i ] = malloc( localesxPiso * sizeof( local_t ) );
   }
   printf( "%d\n", localesxPiso * pisos );
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
   printf( "%d\n", * elementosListaIds );
}

void cargarCC( FILE * archivoBinario, local_t *** centroComercial, int * pisos, int * localesxPiso, int ** listaIdsModificados, int * elementosListaIds ){
   int i;
   fread( localesxPiso, sizeof( int ), 1, archivoBinario );
   fread( pisos, sizeof( int ), 1, archivoBinario );
   reservarEspacioMemoria( centroComercial, * localesxPiso, * pisos, listaIdsModificados );
   fread( elementosListaIds, sizeof( int ), 1, archivoBinario );
   printf( "%d\n", * elementosListaIds );
   fread( * listaIdsModificados, sizeof( int ), * elementosListaIds, archivoBinario );
   for( i = 0; i < * pisos; i++ ){
      fread( ( * centroComercial )[ i ], sizeof( local_t ), * localesxPiso, archivoBinario );
   }
}

void crearDirectorios( ){
   mkdir( "./Data" );
   mkdir( "./Reportes" );
   mkdir( "./Inventarios Locales" );
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

int multiplicadorDecimal( int localesxPiso ){
   if( localesxPiso / 10 == 0 ){
      return 10;
   }
   return 10 * multiplicadorDecimal( localesxPiso / 10);
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
   indices[ 0 ] = i;
   indices[ 1 ] = j;
   return indices;
}

void menuCategoria( ){
   printf( "Seleccione la categoria del local:\n" );
   printf( "1. Ropa\n" );
   printf( "2. Deporte\n" );
   printf( "3. Teconologia\n" );
   printf( "4. Entretenimiento\n" );
   printf( "5. Viveres\n" );
   printf( "6. Comida\n" );
}

void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds ){
   time_t tiempo;
   int opcion, numProductos, numEmpleados, a, indice, posibleId, nuevoId, pisoLocal, numeroLocal, validar = 1;
   int * indices;
   double indicadorRentabilidad;
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
   imprimirLista( listaIdsModificados, * elementosListaIds );
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
      case 3: listarNomina( &local->nomina );
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
      case 2: listarInventario( &local->inventario );
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
      case 3: listarInventario( &local->inventario );
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
listarInventario( &local->inventario );
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
                                 imprimirLista( listaIdsModificados, * elementosListaIds );
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

void reiniciarEstadosDePago( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         centroComercial[ i ][ j ].renta.estadoPago = 1;
      }
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
   registro = fopen( "registro.txt", "w" );
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