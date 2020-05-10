#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"

int main (){

    List * v2 = createList();
    List * v5 = createList();

    int opcion = 0;

    printf("Bienvenido a nuestro nuevo sistema de emparejamiento, ingrese una opcion: \n\n");

    do{

        printf("1.- Ingresar jugador(es) desde un archivo\n");
        printf("2.- Ingresar jugador(es) manualmente\n");
        printf("3.- Eliminar jugador de la cola de espera\n");
        printf("4.- Mostrar jugadores en la lista de espera\n");
        printf("0.- Salir\n\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion){

            case 0: printf("\nGracias por probar nuestro sistema de emparejamiento!\n");
            return 0;
            case 1: ingresarJugadoresDesdeArchivo(v2, v5);
            system("cls");
            break;
            case 2: ingresarJugadorManual(v2, v5);
            system("cls");
            break;
            case 3: eliminarJugador(v2, v5);
            system("cls");
            break;
            case 4: mostrarJugadoresEnEspera(v2, v5);
            system("cls");
            break;
            default: system("cls");
            printf("no se ha ingresado ninguna de las opciones anteriores, escriba una opcion correcta:\n\n");
            break;
        }

    }while(1);

    return 0;

}

