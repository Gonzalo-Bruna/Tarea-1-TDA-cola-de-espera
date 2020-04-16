#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"

Jugador * crearJugador(int id, char *nombre, int elo){

    Jugador * jugador = (Jugador *) malloc (sizeof(Jugador));
    jugador->idJugador = id;
    jugador->nombreJugador = nombre;
    jugador->elo = elo;
    return jugador;
}

Emparejamiento * crearEmparejamiento(){

    return (Emparejamiento *) calloc(1, sizeof(Emparejamiento));

}

char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

void ingresarJugadoresDesdeArchivo(List * v2, List * v5){

    system("cls");

    int opcion;

    do{

        printf("1.- Instertar jugador(es) mediante archivo csv\n");
        printf("0.- Volver al menu principal\n\n");
        printf("ingrese una opcion: ");

        scanf("%d", &opcion);

        if(opcion < 0 || opcion > 1){

            system("cls");
            printf("Por favor ingrese la opcion correcta\n");

        }

    }while(opcion < 0 || opcion > 1);

    if( opcion == 0 ) return;

    printf("\n");
    printf("Ingrese el nombre del archivo csv que desea ingresar, incluyendo su extension: ");

    char nombreArchivo[30];

    do{

        scanf("%s", nombreArchivo);

        FILE * fp;
        fp = fopen(nombreArchivo, "r");


        if (fp == NULL){
            printf("\n");
            printf("Error al abrir el archivo, revise que haya ingresado el nombre de manera correcta, incluyendo su extension, e intentelo de nuevo: ");
        }
        else{

            char linea[1024];

            //lo que haré será crear dos colas para el archivo de entrada, una 2vs2 y una 5vs5, entonces iremos ingresando jugadores y se irá
            //comprobando cada vez que se ingresa uno si es que puede existir un emparejamiento, en caso contrario, seguirán en la cola de espera

            while(fgets(linea, 1023, fp)){

                int id = atoi(get_csv_field(linea, 1));
                char *nombre = get_csv_field(linea, 2);
                int elo = atoi(get_csv_field(linea, 3));

                Jugador * jugador = crearJugador(id, nombre, elo);
                if(strcmp(get_csv_field(linea, 4), "2vs2") == 0){

                    //metemos en una lista todos los que se quieran emparejar en un enfretamiento 2v2
                    if(v2->size >= 3){

                        intentarEmparejamiento2v2(v2, jugador);

                    }
                    else{
                        pushFront(v2, jugador);

                    }

                }
                else{

                    if(v5->size >= 9){
                        intentarEmparejamiento5v5(v5, jugador);
                    }
                    else{
                        pushBack(v5, jugador); //metemos en esta lista los que quieran emparejarse en un enfrentamiento 5v5
                    }
                }
            }

            printf("\n");
            break;
        }

    }while(1);

    system("pause");

}

void ingresarJugadorManual(List * v2, List * v5){

    system("cls");

    int opcion;
    do{
        printf("1.- Ingresar jugador(es) manualmente");
        printf("\n");
        printf("0.- Volver al menu principal");
        printf("\n");
        printf("\n");

        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);

        if (opcion != 0 && opcion != 1){

            system("cls");
            printf("por favor ingrese una opcion correcta: \n");

        }
        else{
            break;
        }
    }while(1);

    if(opcion == 0) return;

    printf("\n");

    do{

        printf("Por favor ingrese la cantidad de jugadores que desea ingresar: ");
        scanf("%d", &opcion);

        if(opcion <= 0){
            system("cls");
            printf("El numero ingresado debe ser mayor a 0");
            printf("\n");
            printf("\n");
        }

    }while(opcion <= 0);

    int id;
    int elo;
    char modo[5];

    int cont = 1;

    printf("\n");

    while(opcion > 0){

        char * nombre = (char *) malloc (50 * sizeof(char));

        printf("Por favor, ingrese el id del jugador %d: ", cont);
        scanf("%d", &id);

        if(existeJugador(v2, v5, id) == 0 ) {

            printf("\n");
            printf("El jugador que has ingresado, ya se encuentra en la cola de espera para enfrentamiento 2vs2");
            printf("\n");
            printf("Por favor reintentelo: ");
            printf("\n");
            printf("\n");
            continue;

        }

        printf("Ahora ingrese el nombre del jugador: ");
        scanf("%s", nombre);
        printf("Ingrese tambien su elo: ");
        scanf("%d", &elo);
        printf("Por ultimo ingrese la modalidad de juego (2vs2 o 5vs5): ");
        scanf("%s", modo);

        Jugador * jugador = crearJugador(id, nombre, elo);

        if(strcmp(modo, "2vs2") == 0){
            if(v2->size >= 3){
                intentarEmparejamiento2v2(v2, jugador);
            }
            else{
                pushBack(v2, jugador);
                printf("\n");
                printf("Jugador %d ingresado correctamente a la cola de espera 2vs2", cont);
                printf("\n");
                printf("\n");
            }
        }
        else if(strcmp(modo, "5vs5") == 0){
            if(v5->size >= 9){
                intentarEmparejamiento5v5(v5, jugador);
            }
            else{
                pushBack(v5, jugador);
                printf("\n");
                printf("Jugador %d ingresado correctamente a la cola de espera 5vs5", cont);
                printf("\n");
                printf("\n");
            }
        }

        opcion--;
        cont++;

    }

    system("pause");

}

void eliminarJugador(List * v2, List * v5){

    system("cls");

    int opcion;
    while(1){
        printf("1.- Eliminar un jugador de la lista de espera");
        printf("\n");
        printf("0.- Volver al menu principal");
        printf("\n");
        printf("\n");

        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);

        if (opcion != 0 && opcion != 1){

            system("cls");
            printf("por favor ingrese una opcion correcta: \n");

        }
        else{
            break;
        }
    }

    if(opcion == 0) return;

    int id;
    char modo[5];

    printf("\n");
    printf("por favor, ingrese el id del jugador que desea eliminar: ");
    scanf("%d", &id);

    if(existeJugador(v2,v5, id) == 1){
        printf("\n");
        printf("No existe ningun jugador con la id especificada en ninguna de las colas de espera");
        printf("\n");
        printf("\n");
        system("pause");
        return;
    }

    printf("ahora ingrese la cola de espera en la que se encuentra (2vs2 o 5vs5): ");
    scanf("%s", modo);

    if(strcmp(modo, "2vs2") == 0){
        if(eliminarListaEspera(v2, id) == 0){
            printf("\n");
            printf("El jugador ha sido eliminado correctamente de la cola de espera 2vs2");
            printf("\n");
            printf("\n");
        }
    }
    else if(strcmp(modo, "5vs5") == 0){
        if(eliminarListaEspera(v5, id) == 0){
            printf("\n");
            printf("El jugador ha sido eliminado correctamente de la cola de espera 5vs5");
            printf("\n");
            printf("\n");
        }

    }

    system("pause");

}

void mostrarJugadoresEnEspera(List * v2, List * v5){

    Jugador * jugadorv2 = first(v2);
    if ( jugadorv2 == NULL){

        printf("\n");
        printf("No hay jugadores en la cola de espera para juego 2vs2");
        printf("\n");
        printf("\n");

    }
    else{

        printf("\n");
        printf("Para el modo 2vs2, se encuentran los siguientes jugadores en lista de espera: ");
        printf("\n");
        printf("\n");
        while(jugadorv2 != NULL){

            printf("%s, id: %d, elo: %d\n", jugadorv2->nombreJugador, jugadorv2->idJugador, jugadorv2->elo);
            jugadorv2 = next(v2);
        }
        printf("\n");

    }

    Jugador * jugadorv5= first(v5);
    if ( jugadorv5 == NULL){

        printf("No hay jugadores en la cola de espera para juego 5vs5");
        printf("\n");
        printf("\n");

    }
    else{

        printf("Para el modo 5vs5, se encuentran los siguientes jugadores en lista de espera: ");
        printf("\n");
        printf("\n");
        while(jugadorv5 != NULL){

            printf("%s, id: %d, elo: %d\n", jugadorv5->nombreJugador, jugadorv5->idJugador, jugadorv5->elo);
            jugadorv5 = next(v5);
        }
        printf("\n");

    }

    system("pause");
}

void intentarEmparejamiento2v2(List * v2, Jugador * nuevo){

    Emparejamiento * match = crearEmparejamiento(); /* creamos una variable emparejamiento que contiene una lista, entonces si es posible unirse
    a un emparejamiento, el jugador se une a la lista */

    match->jugadores = createList();
    pushBack (match->jugadores, nuevo);

    match->eloMax = nuevo->elo;
    match->eloMin = nuevo->elo;
    match->eloProm = match->eloProm + nuevo->elo;

    Jugador * jugador = first(v2);

    while(jugador != NULL){

        if ( (jugador->elo < (match->eloMin + 50) ) && ( jugador->elo > (match->eloMax - 50 ) ) ){

            if(jugador->elo > match->eloMax){
                match->eloMax = jugador->elo;
            }
            else if(jugador->elo < match->eloMin){
                match->eloMin = jugador->elo;
            }

            match->eloProm = match->eloProm + jugador->elo;

            pushFront(match->jugadores, jugador);

            if(match->jugadores->size == 4){

                match->eloProm = match->eloProm / 4;

                Jugador * aux = first(match->jugadores);

                printf("\n");
                printf("Emparejamiento 2vs2 realizado");
                printf("\n");
                printf("\n");
                printf("Elo promedio: %d", match->eloProm);
                printf("\n");
                printf("Jugadores emparejados: ");
                printf("\n");
                printf("\n");

                while(aux != NULL){

                    //eliminamos de la lista de espera al jugador si es que encontramos un match,
                    //lo hacemos dentro del while porque hay que eliminar a los 4 jugadores
                    if(eliminarListaEspera(v2, aux->idJugador) == 0);


                    printf("%s\n", aux->nombreJugador);
                    aux = next(match->jugadores);

                }

                free(match);
                return;

            }

        }

        jugador = next(v2);
    }

    free(match); //si se termina la funcion sin emparejamiento hay que borrar la memoria guardada en match
    pushBack(v2, nuevo); //si no se pudo encontrar match, el jugador permanece en la cola de espera

}

void intentarEmparejamiento5v5(List * v5, Jugador * nuevo){

    Emparejamiento * match = crearEmparejamiento(); /* creamos una variable emparejamiento que contiene una lista, entonces si es posible unirse
    a un emparejamiento, el jugador se une a la lista */

    match->jugadores = createList();
    pushBack (match->jugadores, nuevo);

    match->eloMax = nuevo->elo;
    match->eloMin = nuevo->elo;
    match->eloProm = match->eloProm + nuevo->elo;

    Jugador * jugador = first(v5);

    while(jugador != NULL){

        if ( (jugador->elo < (match->eloMin + 50) ) && ( jugador->elo > (match->eloMax - 50 ) ) ){

            if(jugador->elo > match->eloMax){
                match->eloMax = jugador->elo;
            }
            else if(jugador->elo < match->eloMin){
                match->eloMin = jugador->elo;
            }

            match->eloProm = match->eloProm + jugador->elo;

            pushBack(match->jugadores, jugador);

            if(match->jugadores->size == 10){

                match->eloProm = match->eloProm / 10;

                Jugador * aux = first(match->jugadores);

                printf("\n");
                printf("Emparejamiento 5vs5 realizado");
                printf("\n");
                printf("\n");
                printf("Elo promedio: %d", match->eloProm);
                printf("\n");
                printf("Jugadores emparejados: ");
                printf("\n");
                printf("\n");

                int cont = 1;

                while(aux != NULL){

                    //eliminamos de la lista de espera al jugador si es que encontramos un match,
                    //lo hacemos dentro del while porque hay que eliminar a los 4 jugadores
                    if(cont != 1){
                        if(eliminarListaEspera(v5, aux->idJugador) == 0);
                    }
                    printf("%s\n", aux->nombreJugador);
                    aux = next(match->jugadores);

                }

                free(match);
                return;

            }

        }

        jugador = next(v5);
    }

    free(match); //si se termina la funcion sin emparejamiento hay que borrar la memoria guardada en match
    pushBack(v5, nuevo); // si no se pudo encontrar match el jugador permanece en la cola de espera
}

int eliminarListaEspera(List * list, int id){

    Jugador * jugador = first(list);
    while(jugador != NULL){

        if (jugador->idJugador == id){

            popCurrent(list);
            return 0;
        }

        jugador = next(list);

    }

    return 1;

}

int existeJugador(List * v2, List * v5, int id){

    Jugador * jugadorv2 = first(v2);
    Jugador * jugadorv5 = first(v5);

    while(jugadorv2 != NULL){
        if(jugadorv2->idJugador == id){

            return 0;
        }

        jugadorv2 = next(v2);
    }

    while(jugadorv5 != NULL){
        if(jugadorv5->idJugador == id){

            return 0;
        }

        jugadorv5 = next(v5);
    }

    return 1;
}
