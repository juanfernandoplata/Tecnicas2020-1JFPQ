#ifndef FUNCIONES
#define FUNCIONES

typedef struct datosPersona datosPersona;
int esBisiesto( int anio );
int buscarAnioPersona( datosPersona ** matriz, int * limitesFilas, char nombre[ 10 ] );
void mostrarDatos( datosPersona ** matriz, int mes, int limite );
void crearAgregarDatosPersona( datosPersona ** matriz, int * limitesFilas );
int menu();
int seleccionAnio();
int seleccionMes();
int seleccionDia( int mes, int anio );
int validarAnio( int anio );
int validarMes( int mes );
int validarDia( int dia, int mes, int anio );
datosPersona ** crearMatrizDinamica();

#endif