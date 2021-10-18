#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix_stub.h"

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;

}
int main(){
    multmatrix_stub * matriz = new multmatrix_stub();
    //matrix_t *m1 = nullptr;
    //matrix_t *m2 = nullptr;
    //matrix_t *res = nullptr;
    matrix_t *m3 = nullptr;
    
    //m1 = matriz->createRandMatrix(5,5);
    m3 = matriz->createIdentity(5,5);
    //res = matriz->multMatrix(m1,m2);
    //m3 = matriz->readMatrix("resultado.txt");
    matriz->writeMatrix(m3,"resultado.txt");

    int i = 0;
    for (i = 0; i< (m3->rows * m3->cols);i++){ 
        std::cout<<"pos["<<i<<"]: "<<m3->data[i]<<std::endl;
    }
    delete m3;
    delete matriz;
    //delete m1;
    //delete m2;
    //delete res;
    //delete m3;

    /*
    multMatrix* mmatrix=new multMatrix();
    matrix_t* m1= mmatrix->createRandMatrix(5,5);
    matrix_t* m2= mmatrix->createIdentity(5,5);
    matrix_t* mres=mmatrix->multMatrices(m1,m2);
    mmatrix->writeMatrix(mres,"resultado.txt");
    matrix_t* m3=mmatrix->readMatrix("resultado.txt");
    matrix_t* mres2=mmatrix->multMatrices(m1,m3);
    mmatrix->writeMatrix(mres2,"resultado2.txt");

    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete mmatrix;*/

    return 0;

}
