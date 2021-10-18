#include "multmatrix.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
//#include "matrix_h.h"
#define OP_SALIR 				0
#define OP_READ_MATRIX  		10
#define OP_MULT_MATRIX  		11
#define OP_WRITE_MATRIX  		12
#define OP_CREATE_IDENTITY  	13
#define OP_CREATE_RAND_MATRIX	14

class multmatrix_imp{
private:
    int cliente_id = -1;
    bool salir = false;
    multMatrix *op_mat = nullptr;
    
public:
    multmatrix_imp(int client_id);
    bool getSalir(){return salir;};
    void atenderOperacion();
    ~multmatrix_imp();
};