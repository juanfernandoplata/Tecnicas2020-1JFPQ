#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
// #include <stdexcept>

typedef struct Local local_t;
typedef struct type_inventario type_inventario;
typedef struct type_nomina type_nomina;
typedef struct type_indicadoresFinanzas type_indicadoresFinanzas;
typedef struct type_renta type_renta;
typedef struct type_threadData type_threadData;
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
   double historicoGanancias;
   double gananciasSemana;
   time_t ultModSem;
   double gananciasMes;
   time_t ultModMes;
   double gananciasAnio;
   time_t ultModAnio;
};

struct type_nomina{
   int numeroEmpleados;
   char listaNombres[ 100 ][ 31 ];
   char listaCargos[ 100 ][ 31 ];
   double listaSalarios[ 100 ];
};

struct type_inventario{
   int numeroProductos;
   char listaProductos[ 1000 ][ 31 ];
   int listaCantidad[ 1000 ];
   double listaCostos[ 1000 ];
   double listaPrecios[ 1000 ];
   double indicadorRentabilidad;
};

struct type_renta{
   type_estadoPago estadoPago;
   int mesesMora;
   int rentasPagas;
   time_t ultMod;
};

struct type_threadData{
   local_t ** centroComercial;
   int pisos;
   int localesxPiso;
   int * killThread;
};

struct Local{
   char nombreLocal[ 35 ];
   type_nomina nomina;
   type_categoria categoria;
   type_indicadoresFinanzas indicadoresFinanzas;
   type_inventario inventario;
   type_renta renta;
   int idLocal;
   int pisoLocal;
   int numLocalxPiso;
   int metrosCuadradosLocal;
   struct tm fechaIngreso;
};

void generarNominas( local_t ** centroComercial, int pisos, int localesxPiso );
void generarInventarios( local_t ** centroComercial, int pisos, int localesxPiso );

void crearDirectorios( );
local_t ** crearCC( int * pisos, int * localesxPiso );
void generarListaIdsModificados( int ** listaIdsModificados, int pisos, int localesxPiso );

void guardarCC( FILE * archivoBinario, local_t ** centroComercial, int * pisos, int * localesxPiso, int * listaIdsModificados, int * elementosListaIds );
void cargarCC( FILE * archivoBinario, local_t *** centroComercial, int * pisos, int * localesxPiso, int ** listaIdsModificados, int * elementosListaIds );

void * timer( void * arg );

void validarRangoValor( int minimo, int maximo, int * direccionVariable );
int multiplicadorDecimal( int localesxPiso );

void evaluarRentas( local_t ** centroComercial, int pisos, int localesxPiso );
void consultarInfoLocal( local_t ** centroComercial, int pisos, int localesxPiso );

void numeroLocalesEnUso( local_t ** centroComercial, int pisos, int localesxPiso );
void listarLocalesPorPiso( local_t ** centroComercial, int localesxPiso );
void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso );

void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds );
void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso, int * listaIdsModificados, int * elementosListaIds );
void eliminarLocal( local_t ** centroComercial, int pisos, int localesxPiso );

void registrarPagoRentaLocal( local_t ** centroComercial, int pisos, int localesxPiso );
void generarRegistroDePagos( local_t ** centroComercial, int pisos, int localesxPiso );

void ordenarSeleccion( local_t arreglo[], int size );
void ordenarInsercion( local_t arreglo[], int size );
void quickSort( local_t arreglo[], int posInicial, int posFinal );
void mergeSort( local_t arreglo[], int posInicial, int posFinal );

void menuPrincipal( );

#endif