#include "filemanager_stub.h"

Filemanager_stub::Filemanager_stub(std::string path){
    char *ip = new char[strlen(SERVER_IP)+1];
    memcpy(ip,SERVER_IP,strlen(SERVER_IP)+1);
    this->server_id = initClient(ip,SERVER_PORT);
    
    delete ip;
}

void Filemanager_stub::readFile(char *fileName, char *&data, unsigned long &dataLength){

}
void Filemanager_stub::writeFile(char *fileName, char *data, unsigned long dataLength){

}
void Filemanager_stub::freeListedFiles(std::vector<std::string *> *fileList){

}
Filemanager_stub::~Filemanager_stub(){
    int operacion=OP_SALIR;
	sendMSG(this->server_id, (void*)&operacion, sizeof(int));
	closeConnection(this->server_id);
}