#include "filemanager_imp.h"

filemanager_imp::filemanager_imp(int client_id){
    this->cliente_id = client_id;
    this->salir = false;
    this->op_mat = new FileManager(" PONEMOS EL PATH"); 
}
void filemanager_imp::atenderOperacion(){
    int operacion = -1;
    char *datos = nullptr;
    int dataLen = 0;

    while (this->getSalir() != true){

        //Recibimos los datos
        recvMSG(this->cliente_id,(void**)&datos,&dataLen);
		memcpy(&operacion,datos, sizeof(int));
        delete datos;

        switch (operacion){
            case OP_SALIR:{
                this->salir = true;
            }break;
            case OP_READ_FILE:{

            }break;
            case OP_WRITE_FILE:{
                
            }break;
        }
    }
}
void filemanager_imp::atenderOperacion(){
    delete this->op_mat;
}