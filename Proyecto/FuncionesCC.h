#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef struct Local local_t;
typedef struct type_inventario type_inventario;
typedef struct type_nomina type_nomina;
typedef struct type_indicadoresFinanzas type_indicadoresFinanzas;
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

struct type_indicadoresFinanzas{
   double ventasSemana;
   double ventasMes;
   double ventasAnio;
};

struct type_nomina{
   int numeroEmpleados;
   char * listaNombres[ 100 ];
   char * listaCargos[ 100 ];
   double listaSalarios[ 100 ];
};

struct type_inventario{
   int items;
   char * listaProductos[ 1000 ];
   double listaPrecios[ 1000 ];
   double indicadorRentabilidad;
};

struct Local{
   char nombreLocal[ 35 ];
   type_nomina nomina;
   type_categoria categoria;
   type_indicadoresFinanzas indicadoresFinanzas;
   type_inventario inventario;
   type_estadoPago estadoPago;
   int idLocal;
   int pisoLocal;
   int numLocalxPiso;
   int metrosCuadradosLocal;   
};

void generarListaIdsModificados( int ** listaIdsModificados, int pisos, int localesxPiso );
void guardarCC( FILE * archivoBinario, local_t ** centroComercial, int * localesxPiso, int * pisos, int * listaIdsModificados, int * elementosListaIds );
void cargarCC( FILE * archivoBinario, local_t *** centroComercial, int * localesxPiso, int * pisos, int ** listaIdsModificados, int * elementosListaIds );
void crearDirectorios( );
void validarRangoValor( int minimo, int maximo, int * direccionvariable );
local_t ** crearCC( int * pisos, int * localesxPiso );
int multiplicadorDecimal( int localesxPiso );
void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds );
void numeroLocalesEnUso( local_t ** centroComercial, int pisos, int localesxPiso );
void listarLocalesPorPiso( local_t ** centroComercial, int localesxPiso );
void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso );
void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds );
void eliminarLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void reiniciarEstadosDePago( local_t ** centroComercial, int pisos, int localesxPiso );
void registrarPagoRentaLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void generarRegistroDePagos( local_t ** centroComercial, int pisos, int localesxPiso );

#endif