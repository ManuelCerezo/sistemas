#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "filemanager_imp.h"
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
    filemanager_imp *server = new filemanager_imp(client_id);

    while(server->getSalir()!= true){
        server->atenderOperacion();
    }
    delete server;
}