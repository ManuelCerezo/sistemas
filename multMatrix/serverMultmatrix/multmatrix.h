#ifndef MULTMATRIX_H
#define MULTMATRIX_H
#include "matrix_h.h"

class multMatrix{

public:
    multMatrix();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
    ~multMatrix();
};

#endif // MULTMATRIX_H
