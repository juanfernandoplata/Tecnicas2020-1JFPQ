local_t ** crearCC( int * pisos, int * localesxPiso );
=========================================================================================
- La funcion basse del programa
- Se encarga de crear la matriz que modela el centro comercial
- Como parametros entran las dimensiones de la matriz
- Posteriormente se crea la matriz dinamica utilizando la funcion malloc
- Una vez creada la matriz el elemento idLocal de cada elemento de la matriz es
  inicializado en -1 para representar un local que esta disponible
=========================================================================================
int multiplicadorDecimal( int localesxPiso );
=========================================================================================
- Es la funcion mas sencilla del programa
- No obstante es recursiva
- Se encarga de determinar el multiplicador de la variable pisoLocal en la funcion
  agregarLocal
- Esto se hace con el objetivo de crear un id que sea unico para cada local
- Notese que la manera mas sencilla de lograr eso es asegurandose de que la cifra que
  se refiere al piso del local debe estar ubicada en una posicion diferente a las
  casillas que se refieran a la posicion del local en el piso
=========================================================================================
void agregarLocal( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Esta funcion se encarga de agregar un local a la matriz
- Como parametros entran la matriz, el numero de pisos y el numero de locales por piso
- Estos no representan la ubicacion del local, solo son validadores para los ciclos de la
  funcion
- Posteriormente la funcion solicita los datos necesarios para agregar el local,
  realiza las validaciones pertinentes para que no existan conflictos, y finalmente
  agrega el local a la matriz
=========================================================================================
void numeroLocalesEnUso( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Otra de las funciones mas sencillas del programa
- Si sabemos, por definicion, que los id's asociados a un local que tengan un valor igual
  a -1 representan un local disponible, entonces es claro que el numero de locales en uso
  debe ser igual al numero de pisos, por el numero de locales por piso, menos todos los
  locales con id's igual a -1
- Dos ciclos for anidados se encargan de verificar este valor en cada elemento de la matriz
=========================================================================================
void listarLocalesPorPiso( local_t ** centroComercial, int localesxPiso );
=========================================================================================
- Esta funcion no utiliza ciclos for anidados
- No es necesario porque vamos a acceder a los valores de una sola dimension de la matriz
- Asi, la funcion fija un valor, que el usuario determina, como indice de la matriz,
  mientras que el subindice varia segun un ciclo for
- De este modo recorremos los valores de un solo fila de la matriz, e imprimimos los
  valores pertinentes
- En este caso, solo el nombre del local
- Notese que solo se imprimen aquellos locales que tienen un id diferente de -1, es decir,
  que no estan vacios
=========================================================================================
void listarLocales( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Esta funcion es similar a la anterior en tanto que lista los locales
- Sin embargo, en este caso no se listan solo los locales de un solo piso, sino todos los
  locales del centro comercial
- Para esto se construyen dos ciclos for anidados, que permitan recorrer toda la matriz
- Notese que, al igual que en la funcion anterior, solo se imprime la informacion de los
  locales que tienen id's diferentes a -1
=========================================================================================
void modificarInformacionLocal( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Esta funcion es considerablemente mas compleja que el resto de las funciones del programa
- Su complejidad radica en el numero de validaciones que deben hacerse, y el numero de casos
  diferentes que pueden llegar a presentar
- De forma resumida, existen tres posibilidades
- 1. Que el usuario quiera modificar el nombre del local
     - En este caso tan solo se tiene que cambiar el nombre, no se necesitan validaciones
- 2. Que el usuario quiera modificar la ubicacion del local
     - En este caso existen dos posibilidades, que la ubicacion nueva del local ya este
       ocupada o no. Por este motivo se tiene que ver si el usuario quiere intercambiar
       o no los locales.
- 3. Que el usuario quiera modificar el id del local
     - Esta se sopeso. No se sabia si se le debia dar ese poder al usuario. Al final
       se opto por permitirle al usuario modificar el id de un local, aunque se le advierte
       que ello podria generar id's repetidos en el futuro, pues la validacion hecha a
       continuacion solo garantiza que el id nuevo que el usuario quiere asignar no exista
       ya para algun otro local
=========================================================================================
void eliminarLocal( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Puesto que este modelo del centro comercial distingue entre locales disponibles
  y locales no disponibles a traves del elemento idLocal, podemos representar el cierre
  de un local como una restauracion del valor idLocal asociado al local en cuestion a
  su estado original
- La funcion eliminarLocal hace esto
=========================================================================================
void reiniciarEstadosDePago( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Al struct local se le agrego un enum llamado estadoPago
- Este hace referencia al estado del pago de la renta del local en cuestion
- Por defecto todos los locales son inicializados sin deuda de renta
- Sin embargo, tal que el pago de la renta suele hacerse cada mes, esta funcion le
  permite al usuario reiniciar el estado de pago de todos los locales a la vez,
  representando el inicio de mes
=========================================================================================
void registrarPagoRentaLocal( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Esta funcion registra el pago de la renta de un local
- Para esto, solicita el id del local que realizo el pago, y modifica su estado de pago
  de renta para que almacene el valor del enum AL_DIA
=========================================================================================
void generarRegistroDePagos( local_t ** centroComercial, int pisos, int localesxPiso );
=========================================================================================
- Si se modela el estado de pago de la renta de los locales, entonces es pertinente
  poder saber en un momento dado en el tiempo que locales han pagado su renta y que locales
  no
- Para esto, la funcion generarRegistroDePagos genera un archivo con el nombre, id, costo
  de la renta y estado de pago de todos los locales que esten en uso
- Para generar el costo de la renta, se supone que este depende de el costo del metro
  cuadrado en funcion del tiempo
- Asi, el usuario debe ingresar el costo del metro cuadrado, que despues es multiplicado
  por el numero de metros cuadrados del local(valor que tambien fue agregado al struct local)
=========================================================================================