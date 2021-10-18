#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "multmatrix_imp.h"

#define SERVER_PORT         65000
using namespace std;


void funcserver(int client_id); //Declaracion de la funcion servidor

int main(int argc, char *argv[]){ //programa principal main.
    int socketID=initServer(SERVER_PORT);
    int clientID = 0;
    while(true){
        if(checkNewConnections()){
            clientID = getNewConnection();
            thread *thd = new thread(funcserver,clientID);
            /*Creamos un proceso nuevo el cual, el codigo del programa del proceso es la funcion servidor que hemos pasado
            introducimos el cliente id para inicializar imp. */
            thd->detach(); //eliminamos el thread
        }
    }

    return 0;
}

void funcserver(int client_id){
    multmatrix_imp *server = new multmatrix_imp(client_id);

    while(server->getSalir()!= true){
        server->atenderOperacion();
    }
    delete server;
}
