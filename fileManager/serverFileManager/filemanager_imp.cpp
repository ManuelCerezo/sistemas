#include "filemanager_imp.h"

filemanager_imp::filemanager_imp(int client_id){
    char *direct = nullptr;
    int dataLen = 0;
    this->cliente_id = client_id;
    this->salir = false;

    recvMSG(this->cliente_id,(void**)&direct,&dataLen);
    this->op_file= new FileManager(string(direct));
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
            case OP_LISTFILES:{
               vector<string*>* flist= this->op_file->listFiles();
               int num_files = flist->size();
               sendMSG(this->cliente_id,(void*)&num_files,sizeof(int));

                for(unsigned int i=0;i<flist->size();++i){
                   sendMSG(this->cliente_id,(void*)flist->at(i)->c_str(),flist->at(i)->length()+1);
                }  
                this->op_file->freeListedFiles(flist);
                
            }break;
            case OP_READ_FILE:{
                //opcion leer fichero.
                char *data =  nullptr;
                int dataLen = 0;
                unsigned long int dataLenMax = 0;
                int tam_nameFile = 0;
                char *fileName = nullptr;
                char *paquete = nullptr;
                
                //recibimos el mensaje.
                recvMSG(this->cliente_id,(void**)&paquete,&dataLen);
                memcpy(&tam_nameFile,paquete,sizeof(int));
                fileName = new char[tam_nameFile];
                memcpy(fileName,&paquete[sizeof(int)],tam_nameFile);
                delete paquete;

                //Leemos el fichero
                this->op_file->readFile(fileName,data,dataLenMax);

                //Empaquetamos el fichero
                paquete = new char[(sizeof(char)*dataLenMax)+sizeof(unsigned long int)];

                memcpy(paquete,&dataLenMax,sizeof(unsigned long int));
                memcpy(&paquete[sizeof(unsigned long int)],data,sizeof(char)*dataLenMax);

                //Enviamos el fichero en un paquete.
                sendMSG(this->cliente_id,(void*)paquete,(sizeof(char)*dataLenMax)+sizeof(unsigned long int));

                delete fileName;
                delete paquete;
                delete data;

            }break;
            case OP_WRITE_FILE:{
                char * paquete = nullptr;
                char * nameFile = nullptr;
                int dataLen = 0;
                unsigned long int tam_data = 0;
                int tam_aux = 0;
                char * data = nullptr;

                //Recibimmos el paquete nombre fichero + su tamanio
                recvMSG(this->cliente_id,(void**)&paquete,&dataLen);
                tam_aux= dataLen - sizeof(int);
                nameFile = new char[tam_aux];
                memcpy(&tam_aux,paquete,sizeof(int));
                memcpy(nameFile,&paquete[sizeof(int)],tam_aux);
                std::cout<<"Nombre fich: "<<nameFile<<std::endl;

                delete paquete;
                dataLen = 0;
                tam_aux = 0;

                //Recibimos segundo paquete.
                recvMSG(this->cliente_id,(void**)&paquete,&dataLen);
                memcpy(&tam_data,paquete,sizeof(unsigned long int));
                data = new char[tam_data+1];
                memcpy(data,&paquete[sizeof(unsigned long int)],tam_data);
                /*std::cout<<"DTOS : "<<std::endl;
                std::cout<<"Nombre fichero a escribir: "<<nameFile<<std::endl;
                std::cout<<"Contenido: "<<data<<std::endl;*/
                //Ejecutamos consulta
                this->op_file->writeFile(nameFile,data,tam_data);

                delete data;
                delete nameFile;
                delete paquete;
            }break;
        }
    }
}
filemanager_imp::~filemanager_imp(){
    delete this->op_file;
}