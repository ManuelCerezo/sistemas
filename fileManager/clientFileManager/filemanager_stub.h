#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string>
#include <map>
#include <vector>
#include <dirent.h>

#define SERVER_IP               "127.0.0.1"
#define SERVER_PORT             31010
#define OP_SALIR 				0
#define OP_READ_FILE 		    10
#define OP_WRITE_FILE  		    11
#define OP_LISTFILES            12

using namespace std;

class Filemanager_stub{

private:
    int server_id = -1;
public:
    void salir();
    Filemanager_stub(string path);
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int &dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
    ~Filemanager_stub();
};
