#ifndef FUNCIONESCC_H_
#define FUNCIONESCC_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Local{
   char nombreLocal[35];
   int idLocal;
   int pisoLocal;
   int numLocalxPiso;
   int metrosCuadradosLocal;
   enum{
      AL_DIA,
      EN_MORA,
   } estadoPago;
} local_t;

local_t ** crearCC( int * pisos, int * localesxPiso );
int multiplicadorDecimal( int localesxPiso );
void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void numeroLocalesEnUso( local_t ** centroComercial, int pisos, int localesxPiso );
void listarLocalesPorPiso( local_t ** centroComercial, int localesxPiso );
void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso );
void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void eliminarLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void reiniciarEstadosDePago( local_t ** centroComercial, int pisos, int localesxPiso );
void registrarPagoRentaLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void generarRegistroDePagos( local_t ** centroComercial, int pisos, int localesxPiso );

#endif