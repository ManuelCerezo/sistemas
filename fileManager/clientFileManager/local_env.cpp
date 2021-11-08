#include "local_env.h"

local_env::local_env(string *path){ //Constructor
    this->path = path;
}

void local_env::list_directory(){
    struct dirent * elemento;
    string elem;
    //cout<<"aqui si"<<endl;
    if((this->directorio = opendir(this->path->c_str())) == nullptr){
        cout<<"[ERROR]: No se ha podido abrir el directorio"<<endl;
    }else{
        while ((elemento = readdir(this->directorio)) != nullptr){
            elem = elemento->d_name;
            if(elem != "." && elem != ".."){
                cout<<elem;
                cout<<" ";
            }
        }
     cout<<endl;
    }
    closedir(this->directorio);
}
bool local_env::comp_file(string *fileName){
    struct dirent * elemento;
    string elem;
    //cout<<"aqui si"<<endl;
    if((this->directorio = opendir(this->path->c_str())) == nullptr){
        cout<<"[ERROR]: No se ha podido abrir el directorio"<<endl;
    }else{
        while ((elemento = readdir(this->directorio)) != nullptr){
            elem = elemento->d_name;
            if(elem != "." && elem != ".."){
                if(elem == fileName->c_str()){
                    closedir(this->directorio);
                    return true;
                }
            }
        }
        closedir(this->directorio);
    }
    return false;
}

string *local_env::get_path(){
    return this->path;
}
void local_env::createFile(char *nameFich, char * data, unsigned long dataLen){
    string path = *this->path+"/"+string(nameFich);
    FILE * fich = fopen(path.c_str(),"w");
    fwrite(data,dataLen,1,fich);
    fclose(fich);
}

void local_env::readFile(char *nameFich, char *&data, unsigned long int &dataLen){
    string path = *this->path+"/"+string(nameFich);
    FILE * fich = fopen(path.c_str(),"r");

    //Obtenemos el tamanio fichero
    fseek (fich , 0 , SEEK_END);
    dataLen = ftell(fich);
    rewind(fich);

    if (data != nullptr){ //añadimos memoria a data
        delete data;
    }else{
        data = new char[dataLen];
    }

    //Escribimos en el fichero
    fread(data,dataLen,1,fich);
    fclose(fich);
}


local_env::~local_env(){ //Destructor
    delete  this->path;
    closedir(this->directorio);
}