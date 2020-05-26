#include "FuncionesCC.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main( ){
   int i, killThread = 0;
   local_t ** centroComercial;
   int opcion, pisos, localesxPiso, elementosListaIds;
   int * listaIdsModificados;
   pthread_t tid;
   pthread_attr_t attr;
   pthread_attr_init( &attr );
   FILE * archivoBinario = fopen( "./Data/Data.dat", "rb" );
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
   evaluarRentas( centroComercial, pisos, localesxPiso );
   type_threadData threadData = ( type_threadData ){ centroComercial, pisos, localesxPiso, &killThread };
   pthread_create( &tid, &attr, timer, &threadData );
   do{
      menuPrincipal( );
      validarRangoValor( 1, 15, &opcion );
      switch( opcion ){
         case 1: agregarLocal( centroComercial, pisos, localesxPiso, listaIdsModificados, &elementosListaIds );
                 break;
         case 2: registrarVentaLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 3: numeroLocalesEnUso( centroComercial, pisos, localesxPiso );
                 break;
         case 4: listarLocalesPorPiso( centroComercial, localesxPiso );
                 break;
         case 5: modificarInformacionLocal( centroComercial, pisos, localesxPiso, listaIdsModificados, &elementosListaIds );
                 break;
         case 6: listarLocales( centroComercial, pisos, localesxPiso );
                 break;
         case 7: consultarInfoLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 8: eliminarLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 9: registrarPagoRentaLocal( centroComercial, pisos, localesxPiso );
                 break;
         case 10: generarRegistroDePagos( centroComercial, pisos, localesxPiso );
                  break;
         case 11: ordenarPorNumeroEmpleados( centroComercial, pisos, localesxPiso );
                  break;
         case 12: ordenarPorTamanioInventario( centroComercial, pisos, localesxPiso );
                  break;
         case 13: ordenarPorVentasSemana( centroComercial, pisos, localesxPiso );
                  break;
         case 14: ordenarPorVentasMes( centroComercial, pisos, localesxPiso );
                  break;
      }
   } while( opcion != 15 );
   archivoBinario = fopen( "./Data/Data.dat", "wb" );
   guardarCC( archivoBinario, centroComercial, &pisos, &localesxPiso, listaIdsModificados, &elementosListaIds );
   fclose( archivoBinario );
   killThread = 1;
   pthread_join( tid, NULL );
   for( i = 0; i < pisos; i++ ){
      free( centroComercial[ i ] );
   }
   free( centroComercial );
   return 0;
}
