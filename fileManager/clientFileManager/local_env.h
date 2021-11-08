#include<iostream>
#include<dirent.h>
#include<string.h>

using namespace std;

class local_env{
private:
    string *path =  nullptr;
    DIR *directorio = nullptr;
public:
    local_env(string *path);
    string *get_path();
    bool comp_file(string *fileName);
    void createFile(char *nameFich, char * data, unsigned long dataLen);
    void readFile(char *nameFich, char *&data, unsigned long int &dataLen);
    void list_directory();
    ~local_env();
};