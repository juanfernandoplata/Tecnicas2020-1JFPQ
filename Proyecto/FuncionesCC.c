#include "FuncionesCC.h"

local_t ** reservarEspacioMemoria( int * localesxPiso, int * pisos ){
   int i;
   local_t ** centroComercial = malloc( * pisos * sizeof( local_t * ) );
   for( i = 0; i < * pisos; i++ ){
      centroComercial[ i ] = malloc( * localesxPiso * sizeof( local_t ) );
   }
   return centroComercial;
}

void guardarCC( FILE * archivoBinario, local_t ** centroComercial, int * localesxPiso, int * pisos ){
   int i;
   fwrite( localesxPiso, sizeof( int ), 1, archivoBinario );
   fwrite( pisos, sizeof( int ), 1, archivoBinario );
   for( i = 0; i < * pisos; i++ ){
      fwrite( centroComercial[ i ], sizeof( local_t ), * localesxPiso, archivoBinario );
   }
}

local_t ** cargarCC( FILE * archivoBinario, int * localesxPiso, int * pisos ){
   local_t ** centroComercial;
   int i;
   fread( localesxPiso, sizeof( int ), 1, archivoBinario );
   fread( pisos, sizeof( int ), 1, archivoBinario );
   centroComercial = reservarEspacioMemoria( localesxPiso, pisos );
   for( i = 0; i < * pisos; i++ ){
      fread( centroComercial[ i ], sizeof( local_t ), * localesxPiso, archivoBinario );
   }
   return centroComercial;
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

void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   int pisoLocal, numeroLocal, validar = 1;
   do{
      printf( "Ingrese el piso donde desea ubicar el local: " );
      scanf( " %d", &pisoLocal );
      printf( "Ingrese el numero del local en el piso: " );
      scanf( " %d", &numeroLocal );
      if( pisoLocal >= 1 && pisoLocal <= pisos && numeroLocal >= 1 && numeroLocal <= localesxPiso ){
         if( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal == -1 ){
            printf( "Ingrese el nombre del local: " );
            fflush( stdin );
            fgets( centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].nombreLocal, 35, stdin );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].pisoLocal = pisoLocal;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].numLocalxPiso = numeroLocal;
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].idLocal = pisoLocal * multiplicadorDecimal( localesxPiso ) + numeroLocal;
            printf( "Ingrese el numero de metros cuadrados del local: " );
            scanf( "%d", &centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].metrosCuadradosLocal );
            centroComercial[ pisoLocal - 1 ][ numeroLocal - 1 ].estadoPago = AL_DIA;
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

void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso ){
   int i, j;
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            printf( "Nombre: %s", centroComercial[ i ][ j ].nombreLocal );
            printf( "ID: %d\n", centroComercial[ i ][ j ].idLocal );
            printf( "Piso: %d\n", centroComercial[ i ][ j ].pisoLocal );
            printf( "Numero local: %d\n", centroComercial[ i ][ j ].numLocalxPiso );
            printf( "Metros cuadrados: %d\n", centroComercial[ i ][ j ].metrosCuadradosLocal );
            if( centroComercial[ i ][ j ].estadoPago == AL_DIA ){
               printf( "Estado de pago: Al dia\n" );
            }
            else{
               printf( "Estado de pago: En mora\n" );
            }
            printf( "===========================\n" );
         }
      }
   }
}

void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso ){
   enum ruta{
      NOMBRE = 1,
      UBICACION = 2,
      ID = 3,
   };
   int a, b, i, j, id, opcion, pisoLocal, numeroLocal, repetido = 0, idEncontrado = 0;;
   char nombreLocalTemp[ 35 ];
   listarLocales( centroComercial, pisos, localesxPiso );
   do{
      printf( "Ingrese el ID del local que desea modificar: " );
      scanf( "%d", &id );
      for( i = 0; i < pisos; i++ ){
         for( j = 0; j < localesxPiso; j++ ){
            if( centroComercial[ i ][ j ].idLocal == id ){
               idEncontrado = 1;
               printf( "1. Modificar nombre del local\n" );
               printf( "2. Modificar ubicacion del local\n" );
               printf( "3. Modificar ID del local\n" );
               scanf( "%d", &opcion );
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
                  case ID: printf( "Tenga en cuenta que cambiar el ID puede generar ID's duplicados a futuro. No le recomendamos modificar el ID\n" );
                           printf( "Esta seguro de que desea cambiar el ID?\n" );
                           printf( "1. Si\n" );
                           printf( "2. No\n" );
                           scanf( "%d", &opcion );
                           if( opcion == 2 ){
                              break;
                           }
                           printf( "Ingrese el nuevo ID: " );
                           scanf( "%d", &id );
                           for( a = 0; a < pisos; a++ ){
                              for( b = 0; b < localesxPiso; b++ ){
                                 if( centroComercial[ a ][ b ].idLocal == id ){
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
                              centroComercial[ i ][ j ].idLocal = id;
                              printf( "El ID en el registro se ha modificado con exito\n" );
                           }
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
         centroComercial[ i ][ j ].estadoPago = EN_MORA;
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
            centroComercial[ i ][ j ].estadoPago = AL_DIA;
            printf( "El pago de la renta del local se ha registrado con exito\n" );
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
   float costoMetroCuadrado;
   registro = fopen( "registro.txt", "w" );
   printf( "Ingrese el costo del metro cuadrado a la fecha: " );
   scanf( "%f", &costoMetroCuadrado );
   for( i = 0; i < pisos; i++ ){
      for( j = 0; j < localesxPiso; j++ ){
         if( centroComercial[ i ][ j ].idLocal != -1 ){
            fprintf( registro, "Nombre: %s", centroComercial[ i ][ j ].nombreLocal );
            fprintf( registro, "ID: %d\n", centroComercial[ i ][ j ].idLocal );
            fprintf( registro, "Costo de la renta: %d\n", centroComercial[ i ][ j ].metrosCuadradosLocal * costoMetroCuadrado );
            if( centroComercial[ i ][ j ].estadoPago == AL_DIA ){
               fprintf( registro, "Estado de pago: Al dia\n" );
            }
            else{
               fprintf( registro, "Estado de pago: En mora\n" );
            }
            fprintf( registro, "===========================\n" );
         }
      }
   }
   fclose( registro );
}