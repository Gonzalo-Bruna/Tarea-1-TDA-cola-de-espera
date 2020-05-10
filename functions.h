#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "list.h"

//definimos el struct jugador, que será ingresado o leido de un archivo csv
typedef struct Jugador{

    int idJugador;
    char * nombreJugador;
    int elo;

}Jugador;

//definimos una función que crea un jugador y lo retorna
Jugador * crearJugador(int, char *, int);

//definimos el struct emparejamiento que entra directamente en una lista los jugadores que se pueden emparejar
typedef struct Emparejamiento{

    int eloMax;
    int eloMin;
    int eloProm;
    List * jugadores;

} Emparejamiento;

//crea un struct Emparejamiento y lo retorna inicializado
Emparejamiento * crearEmparejamiento();

//retorna la cadena que es pasada por parametro duplicada
char * _strdup (const char *);

//retorna el dato i de la linea leída de un archivo csv
const char *get_csv_field (char *, int);

//funcion del menu, añade jugadores desde un archivo, cuando termina vuelve al menu principal
void ingresarJugadoresDesdeArchivo(List *, List *);

//funcion del menu, añade jugadores ingresados por teclado
void ingresarJugadorManual(List *, List *);

//funcion del menu, elimina un jugador que se especifique por id
void eliminarJugador(List *, List *);

//función que intenta realizar un emparejamiento del tamaño respectivo, si es que hay uno, se libera la memoria de los jugadores y se imprime en pantalla
void intentarEmparejamiento2v2(List *, Jugador *);

//función que intenta realizar un emparejamiento del tamaño respectivo
void intentarEmparejamiento5v5();

//esta funcion elimina el jugador asociado al id que se ingrese por parametro
int eliminarListaEspera(List *, int);

//muestra a los jugadores en ambas listas de espera, en caso de no haber jugadores en una cola, lo indicará en la pantalla
void mostrarJugadoresEnEspera(List *, List *);

//funcion que comprueba si existe un jugador en alguna de las dos listas, de existir retorna 0, caso contrario retorna 1
int existeJugador (List *, List *, int);


#endif
