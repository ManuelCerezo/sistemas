#include "filemanager_stub.h"


Filemanager_stub::Filemanager_stub(std::string path){
    char *ip = new char[strlen(SERVER_IP)+1];
    memcpy(ip,SERVER_IP,strlen(SERVER_IP)+1);
    this->server_id = initClient(ip,SERVER_PORT);
    sendMSG(this->server_id,(void*)path.c_str(),path.length()+1);
    delete ip;
}

std::vector<std::string*>* Filemanager_stub::listFiles(){
    vector<string*>* flist=new vector<string*>();
    int tipo_operacion = OP_LISTFILES;
    int *numfich = nullptr;
    int dataLen = 0;
    char *data_file = nullptr;

    //Enviar operacion listfiles
    sendMSG(this->server_id,(void*)&tipo_operacion,sizeof(int));
    recvMSG(this->server_id,(void**)&numfich,&dataLen);

    for(int i = 0; i < numfich[0];i++){
        recvMSG(this->server_id,(void**)&data_file,&dataLen);
        flist->push_back(new string(data_file));
        delete[] data_file;
    }

    return flist;
}

void Filemanager_stub::readFile(char *fileName, char *&data, unsigned long int &dataLength){
    int tipo_operacion = OP_READ_FILE;
    int recv_dataLen = 0;
    char * paquete = new char [strlen(fileName)+sizeof(int)+1];
    int tam = strlen(fileName)+1;
    
    
    //Mandamos tipo de operacion.
    sendMSG(this->server_id,(void*)&tipo_operacion,sizeof(int));

    memcpy(paquete,&tam,sizeof(int));
    memcpy(&paquete[sizeof(int)],fileName,strlen(fileName)+1);

    //Mandamos nombre fichero.
    sendMSG(this->server_id,(void*)paquete,(strlen(fileName)+sizeof(int)+1));
    delete paquete;

    //recibimos contenido del fichero

    /*
    recvMSG(this->server_id,(void**)&paquete,&recv_dataLen);
    dataLength = recv_dataLen - sizeof(unsigned long int);
    data = new char[dataLength];
    memcpy(data,&paquete[sizeof(unsigned long int)],dataLength);*/

    //se reciben bloques de 1024 bytes
    recvMSG(this->server_id,(void**)&paquete,&recv_dataLen);
    //el primer long int tiene el tamaño completo, se calcula el número de paquetes a partir de él
    memcpy(&dataLength,paquete,sizeof(unsigned long int));
    int tamPack=1024;
    int numPacks=dataLength/tamPack;
    int rest=dataLength%tamPack;

    if(rest>0) numPacks+=1;

    data = new char[dataLength];
    char* recvPtr=data;
    paquete+=sizeof(unsigned long int);
    memcpy(recvPtr,paquete,recv_dataLen-sizeof(unsigned long int));
    recvPtr+=recv_dataLen-sizeof(unsigned long int);
    paquete-=sizeof(unsigned long int);
    delete[] paquete;

    for(int i=1;i<numPacks;i++)
    {
        recvMSG(this->server_id,(void**)&paquete,&recv_dataLen);
        memcpy(recvPtr,paquete,recv_dataLen);
        recvPtr+=recv_dataLen;
        delete[] paquete;
    }

}
void Filemanager_stub::writeFile(char *fileName, char *data, unsigned long int dataLength){
    int tipo_operacion = OP_WRITE_FILE;
    int tam_nameFile = strlen(fileName)+1;
    char *paquete = new char[tam_nameFile+sizeof(int)];
    int tam_paquete = dataLength+sizeof(int);
    int aux = dataLength;

    sendMSG(this->server_id,(void*)&tipo_operacion,sizeof(int));

    //Empaquetamos nombre fich + su tamanio
    memcpy(paquete,&tam_nameFile,sizeof(int));
    memcpy(&paquete[sizeof(int)],fileName,tam_nameFile);

    //Mandamos primer paquete.
    sendMSG(this->server_id,(void*)paquete,tam_nameFile+sizeof(int));
    delete paquete;
    paquete = new char[sizeof(unsigned long int )+dataLength]; //SEGMENTATION CORE +1

    //Empaquetamos data con su tamanio
    memcpy(paquete,&dataLength,sizeof(unsigned long int));
    memcpy(&paquete[sizeof(unsigned long int)],data,dataLength);

    //Mandamos segundo paquete.
    //se divide en bloques de 1024 bytes
    int tamPack=1024;
    int numPacks=(sizeof(unsigned long int )+dataLength)/tamPack;
    int rest=(sizeof(unsigned long int )+dataLength)%tamPack;
    char* prtOut=paquete;
    for(int i =0;i<numPacks;i++){
        sendMSG(this->server_id,(void*)prtOut,tamPack);
        prtOut+=tamPack;
    }
    if(rest>0)
        sendMSG(this->server_id,(void*)prtOut,rest);

    delete paquete;
}

void Filemanager_stub::freeListedFiles(vector<string *> *fileList){

    for(vector<string*>::iterator i=fileList->begin();i!= fileList->end();++i)
    {
        delete *i;
    }
    delete fileList;
}


Filemanager_stub::~Filemanager_stub(){
    int operacion=OP_SALIR;
	sendMSG(this->server_id, (void*)&operacion, sizeof(int));
	closeConnection(this->server_id);
}
