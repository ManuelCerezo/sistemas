#include <iostream>
#include <unistd.h>
#include "filemanager_stub.h"


void printhelp();
void clearScreen();
int bash(string *namefich);
bool comp_fichName(vector<string *> *fileList,string name_file);
int main(int argc,char** argv){
    bool salir = false;
    string namefich;
    Filemanager_stub *fm=new Filemanager_stub("./directorio/");
    char* data=nullptr;
    unsigned long int fileLen=0;
    vector<std::string*>* vfiles=fm->listFiles();


    
    
    clearScreen();
    cout<<"             [ BASH FILE MANAGER ]\n\n\n\n"<<endl;
    do{
       
        switch (bash(&namefich)){
        case  0:
            
            for(unsigned int i=0;i<vfiles->size();++i){
                cout<<vfiles->at(i)->c_str()<<"  ";
            }
            cout<<endl;
        break;
        case 1:{
            //reseteamos los datos antes de leer un fichero
            if(comp_fichName(vfiles,namefich)){
                fm->readFile((char *)namefich.c_str(),data,fileLen);
            }else{
                cout<<"[ERROR]: file name not found"<<endl;
            }
        }break;
        case 2:{
            if(comp_fichName(vfiles,namefich)){
                fm->writeFile((char *)namefich.c_str(),data,fileLen);
            }else{
                cout<<"[ERROR]: file name not found"<<endl;
            }    
        }break;
        case 3:{
            printhelp();
        }break;
        case 4:{
            cout<<"GoodBye"<<endl;
            fm->freeListedFiles(vfiles);
            delete fm;
            delete[] data;
            salir = true;
        }break;
        default:
            cout<<"[ERROR]: commnad not found"<<endl;
            cout<<"- type 'help' to see commands available"<<endl;
            break;
        }
    }while(salir == false);
    return 0;
}

bool comp_fichName(vector<string *> *fileList,string name_file){

    for(unsigned int i=0;i<fileList->size();++i){
        if( name_file.c_str() == *fileList->at(i)){
            return true;
        }
    }
    return false;
}


void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int bash(string *namefich){
    string command;
    //string namefich;
    cout<<"bash_fm> ";cin>>command;
    if(command == "ls"){
        //cout<<"imprimimos directorio"<<endl;
        return 0;
    }else if(command == "download"){
        cin>>*namefich;
        //cout<<"download :"<<*namefich<<endl;   
        return 1;
    }else if(command == "upload"){
        cin>>*namefich;
        //cout<<"upload :"<<namefich<<endl;
        return 2;
    }else if(command == "help"){
        return 3;
    }else if(command == "exit"){
        return 4;
    }else{
        return -1;
    }
}

void printhelp(){
    cout<<"\n"<<endl;
    cout<<"commands: [ ls ,download ,upload ,exit ]"<<endl;
    cout<<"-> [ ls ]: list files from remote directory"<<endl;
    cout<<"-> [ download fichname]: download fichname from remote directory."<<endl;
    cout<<"-> [ upload fichname ]: upload fichname from localhost directory."<<endl;
    cout<<"-> [ exit ]: exit bash"<<endl;
    cout<<"\n"<<endl;

}

