#include "FuncionesCC.h"
#include <stdio.h>
#include <stdlib.h>

int main( ){
   int i;
   local_t ** centroComercial;
   int opcion, pisos, localesxPiso, elementosListaIds;
   int * listaIdsModificados;
   FILE * archivoBinario = fopen( "./Data/Data.dat", "rb" );
   time_t tiempoActual;
   tiempoActual = time( NULL );
   if( archivoBinario == NULL ){
      crearDirectorios( );
      centroComercial = crearCC( &pisos, &localesxPiso );
      generarListaIdsModificados( &listaIdsModificados, pisos, localesxPiso );
      elementosListaIds = 0;
   }
   else{
      cargarCC( archivoBinario, &centroComercial, &pisos, &localesxPiso, &listaIdsModificados, &elementosListaIds );
   }
   fclose( archivoBinario );
   evaluarRentas( centroComercial, pisos, localesxPiso, localtime( &tiempoActual ) );
   do{
      menuPrincipal( );
      validarRangoValor( 1, 10, &opcion );
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
   guardarCC( archivoBinario, centroComercial, &pisos, &localesxPiso, listaIdsModificados, &elementosListaIds );
   fclose( archivoBinario );
   for( i = 0; i < pisos; i++ ){
      free( centroComercial[ i ] );
   }
   free( centroComercial );
   return 0;
}
