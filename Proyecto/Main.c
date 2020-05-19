#include "FuncionesCC.h"
#include <stdio.h>
#include <stdlib.h>

void menu( int * opcion ){
   printf( "MENU\n" );
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
   scanf( "%d", opcion );
}

int main( ){
   local_t ** centroComercial;
   int opcion, pisos, localesxPiso, elementosListaIds;
   int * listaIdsModificados;
   FILE * archivoBinario = fopen( "./Data/Data.dat", "rb" );
   if( archivoBinario == NULL ){
      crearDirectorios( );
      centroComercial = crearCC( &pisos, &localesxPiso );
      generarListaIdsModificados( &listaIdsModificados, pisos, localesxPiso );
      elementosListaIds = 0;
   }
   else{
      cargarCC( archivoBinario, &centroComercial, &localesxPiso, &pisos, &listaIdsModificados, &elementosListaIds );
   }
   fclose( archivoBinario );
   do{
      menu( &opcion );
      switch( opcion ){
         case 1: agregarLocal( centroComercial, pisos, localesxPiso, listaIdsModificados, &elementosListaIds );
                 break;
         case 2: numeroLocalesEnUso( centroComercial, pisos, localesxPiso );
                 break;
         case 3: listarLocalesPorPiso( centroComercial, localesxPiso );
                 break;
         case 4: modificarInformacionLocal( centroComercial, pisos, localesxPiso, listaIdsModificados, &elementosListaIds );
                 break;
         case 5: listarLocales( centroComercial, pisos, localesxPiso );
                 break;
         case 6: eliminarLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 7: reiniciarEstadosDePago( centroComercial, pisos, localesxPiso );
                 break;
         case 8: registrarPagoRentaLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 9: generarRegistroDePagos( centroComercial, pisos, localesxPiso );
                 break;
      }
   } while( opcion != 10 );
   archivoBinario = fopen( "./Data/Data.dat", "wb" );
   guardarCC( archivoBinario, centroComercial, &localesxPiso, &pisos, listaIdsModificados, &elementosListaIds );
   fclose( archivoBinario );
   free( centroComercial ); // Completar
   return 0;
}
