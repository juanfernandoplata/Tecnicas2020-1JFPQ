#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILAS 12
#define COLUMNAS 5

/* Esta bn estructurado y ordenado tu codigo, buen trabajo :) 
Ojo el makefile no debe tener extensión .txt*/

typedef struct datosPersona{
   char nombre[ 10 ];
   int dia, mes, anio;
} datosPersona;

int esBisiesto( int anio ){
   if( anio -4 > 0 )
      return esBisiesto( anio - 4 );
   else
      return anio - 4 == 0;
}

int buscarAnioPersona( datosPersona ** matriz, int * limitesFilas, char nombre[ 10 ] ){
   int i, j;
   for( i = 0; i < FILAS; i++ )
      for( j = 0; j < limitesFilas[ i ]; j++ )
         if( !strcmp( matriz[ i ][ j ].nombre, nombre ) )
            return matriz[ i ][ j ].anio;
   return 0;
}

void mostrarDatos( datosPersona ** matriz, int mes, int limite ){
   int i;
   for( i = 0; i < limite; i++ ){
      printf( "Nombre: %s\n", matriz[ mes - 1 ][ i ].nombre );
      printf( "Dia de nacimiento: %d\n", matriz[ mes - 1 ][ i ].dia );
      printf( "Mes de nacimiento: %d\n", matriz[ mes - 1 ][ i ].mes );
      printf( "Anio de nacimiento: %d\n", matriz[ mes - 1 ][ i ].anio );
      printf( "=======================\n" );
   }
   return;
}

void crearAgregarDatosPersona( datosPersona ** matriz, int * limitesFilas ){
   datosPersona datos;
   int dia, mes, anio;
   anio = seleccionAnio();
   mes = seleccionMes();
   dia = seleccionDia( mes, anio );
   if( limitesFilas[ mes - 1] < COLUMNAS ){
      datos.dia = dia;
      datos.mes = mes;
      datos.anio = anio;
      printf( "Ingrese el nombre de la persona\n" );
      scanf( "%s", datos.nombre );
      matriz[ mes - 1 ][ limitesFilas[ mes - 1 ] ] = datos;
      limitesFilas[ mes - 1 ]++;
   }
   else
      printf( "Lo sentimos. No se puede agregar la informacion por falta de espacio de memoria\n" );
   return;
}

int menu(){
   int opcion;
   printf( "Seleccione una opcion\n" );
   printf( "1. Agregar datos de una nueva persona\n" );
   printf( "2. Consultar datos de personas por mes de nacimiento\n" );
   printf( "3. Ver si una persona nacio en anio bisiesto\n" );
   printf( "Ingrese 0 para salir\n" );
   scanf( "%d", &opcion );
   return opcion;
}

int seleccionAnio(){
   int anio;
   do{
      printf( "Ingrese el anio de nacimiento\n" );
      scanf( "%d", &anio );
   } while( validarAnio( anio ) );
   return anio;
}

int seleccionMes(){
   int mes;
   do{
      printf( "Ingrese el mes de nacimiento\n" );
      printf( "1. Enero\n" );
      printf( "2. Febrero\n" );
      printf( "3. Marzo\n" );
      printf( "4. Abril\n" );
      printf( "5. Mayo\n" );
      printf( "6. Junio\n" );
      printf( "7. Julio\n" );
      printf( "8. Agosto\n" );
      printf( "9. Septiembre\n" );
      printf( "10. Octubre\n" );
      printf( "11. Nomviembre\n" );
      printf( "12. Diciembre\n" );
      scanf( "%d", &mes );
   } while( validarMes( mes ) );
   return mes;
}

int seleccionDia( int mes, int anio ){
   int dia;
   do{
      printf( "Ingrese el dia de nacimiento\n" );
      scanf( "%d", &dia );
   } while( validarDia( dia, mes, anio ) );
   return dia;
}

int validarAnio( int anio ){
   if( anio >= 1900 && anio <= 2020)
      return 0;
   else{
      printf( "Por favor ingrese una valor valido\n" );
      return 1;
   }
}

int validarMes( int mes ){
   if( mes >= 1 && mes <= 12 )
      return 0;
   else{
      printf( "Por favor ingrese un valor valido\n" );
   }
}

int validarDia( int dia, int mes, int anio ){
   // LUISA: te quedaría más chevere en el .h el enum
   enum meses{
      ENERO = 1, FEBRERO = 2, MARZO = 3, ABRIL = 4, MAYO = 5, JUNIO = 6,
      JULIO = 7, AGOSTO = 8, SEPTIEMBRE = 9, OCTUBRE = 10, NOVIEMBRE = 11, DICIEMBRE = 12
   };
   int bandera = 1;
   if( esBisiesto( anio ) ){
      if( mes == FEBRERO ){
         if( dia >= 1 && dia <= 29 )
            bandera = 0;
      }
      else if( mes == ENERO || mes == MARZO || mes == MAYO || mes == JULIO || mes == SEPTIEMBRE || mes == OCTUBRE || mes == DICIEMBRE ){
         if( dia >= 1 && dia <= 31 )
            bandera = 0;
      }
      else if( mes == ABRIL || mes == JUNIO || mes == AGOSTO || mes == NOVIEMBRE ){
         if( dia >= 1 && dia <= 30 )
            bandera = 0;
      }
   }
   else{
      if( mes == 2 ){
         if( dia >= 1 && dia <= 28 )
            bandera = 0;
      }
      else if( mes == ENERO || mes == MARZO || mes == MAYO || mes == JULIO || mes == SEPTIEMBRE || mes == OCTUBRE || mes == DICIEMBRE ){
         if( dia >= 1 && dia <= 31 )
            bandera = 0;
      }
      else if( mes == ABRIL || mes == JUNIO || mes == AGOSTO || mes == NOVIEMBRE ){
         if( dia >= 1 && dia <= 30 )
            bandera = 0;
      }
   }
   if( bandera == 1 )
      printf( "Por favor ingrese un valor valido\n" );
   return bandera;
}

datosPersona ** crearMatrizDinamica(){
   int i;
   datosPersona ** matriz = malloc( FILAS * sizeof( datosPersona * ) );
   for( i = 0; i < FILAS; i++ )
      matriz[ i ] = malloc( COLUMNAS * sizeof( datosPersona ) );
   return matriz;
}