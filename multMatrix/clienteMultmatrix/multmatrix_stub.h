#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix_h.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 65000
#define OP_SALIR 				0
#define OP_READ_MATRIX  		10
#define OP_MULT_MATRIX  		11
#define OP_WRITE_MATRIX  		12
#define OP_CREATE_IDENTITY  	13
#define OP_CREATE_RAND_MATRIX	14

class multmatrix_stub{
    
private:
    int server_id = -1;
public:
    multmatrix_stub();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrix(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
    ~multmatrix_stub();
};
