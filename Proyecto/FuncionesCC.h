#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef struct Local local_t;
typedef enum categoria type_categoria;
typedef enum estadoPago type_estadoPago;

enum categoria{
   ROPA,
   DEPORTE,
   TECNOLOGIA,
   ENTRETENIMIENTO,
   VIVERES,
   COMIDA,
};

enum estadoPago{
   AL_DIA,
   EN_MORA,
};

struct Local{
   char nombreLocal[35];
   type_categoria categoria;
   double ingresosMensuales;
   int idLocal;
   int pisoLocal;
   int numLocalxPiso;
   type_estadoPago estadoPago;
   int metrosCuadradosLocal;   
};

void guardarCC( FILE * archivoBinario, local_t ** centroComercial, int * localesxPiso, int * pisos );
local_t ** cargarCC( FILE * archivoBinario, int * localesxPiso, int * pisos );
void crearDirectorios( );
void validarRangoValor( int minimo, int maximo, int * direccionvariable );
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