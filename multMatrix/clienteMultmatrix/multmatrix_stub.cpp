#include "multmatrix_stub.h"


multmatrix_stub::multmatrix_stub(){
    char *ip = new char[strlen(SERVER_IP)+1];
    memcpy(ip,SERVER_IP,strlen(SERVER_IP)+1);
    this->server_id = initClient(ip,SERVER_PORT);
    
    delete ip;
}



void  multmatrix_stub::writeMatrix(matrix_t* m, const char *fileName){
    int tipo_operacion = OP_WRITE_MATRIX;
    char * paquete = new char[sizeof(int)*((m->rows*m->cols)+2)+strlen(fileName)+1];

    //Mandamos el mensaje -> escribir matriz.
    sendMSG(this->server_id,(void**)&tipo_operacion,sizeof(int));

    //empaquetamos la matriz y nombre archivo.
    memcpy(paquete,&m->rows,sizeof(int));
    memcpy(&paquete[sizeof(int)],&m->cols,sizeof(int));
    memcpy(&paquete[sizeof(int)*2],m->data,(sizeof(int)*(m->rows*m->cols)));
    memcpy(&paquete[(sizeof(int)*(m->rows*m->cols)+2)],fileName,strlen(fileName)+1);

    //Mandamos el mensaje.
    sendMSG(this->server_id,(void**)paquete,sizeof(int)*((m->rows*m->cols)+2)+strlen(fileName)+1);
    
    delete paquete;
    return ;
}

matrix_t* multmatrix_stub::readMatrix(const char* fileName){
    int tipo_operacion = OP_READ_MATRIX;
    char *paquete = nullptr;
    int dataLen = 0;
    matrix_t *matriz = new matrix_t();

    std::cout<<"nombre archivo: "<<fileName<<std::endl;

    //enviamos operacion 
    sendMSG(this->server_id,(void**)&tipo_operacion,sizeof(int));
    
    //Enviamos argumentos.
    sendMSG(this->server_id,(void**)fileName,strlen(fileName)+1);

    //recibimos resultado.
    recvMSG(this->server_id,(void**)&paquete,&dataLen);

    memcpy(&matriz->rows,paquete,sizeof(int));
    memcpy(&matriz->cols,&paquete[sizeof(int)],sizeof(int));
    matriz->data = new int[(matriz->rows * matriz->cols)];
    memcpy(matriz->data,&paquete[2*sizeof(int)],sizeof(int)*(matriz->rows*matriz->cols));
    delete paquete;

    return matriz;
}


matrix_t * multmatrix_stub::createIdentity(int rows, int cols){
    //Crear una matriz identidad rows * cols.
    int tipo_operacion = OP_CREATE_IDENTITY;
    matrix_t * mat = new matrix_t();
    char *paquete = new char[sizeof(int)*(rows * cols)];
    int datapaq = 0;
    sendMSG(this->server_id,(void**)&tipo_operacion,sizeof(int));

    //Empaquetamos la informacion.
    memcpy(paquete,&rows,sizeof(int));
    memcpy(&paquete[sizeof(int)],&cols,sizeof(int));

    //Enviamos el paquete.
    sendMSG(this->server_id,(void**)paquete,(sizeof(int)*2));

    //Recibimos el paquete
    recvMSG(this->server_id,(void**)&paquete,&datapaq);

    //Desempaquetamos el paquete.
    memcpy(&mat->rows,paquete,sizeof(int));
    memcpy(&mat->cols,&paquete[sizeof(int)],sizeof(int));
    mat->data = new int[mat->cols*mat->rows];
    memcpy(mat->data,&paquete[sizeof(int)*2],sizeof(int)*(mat->rows * mat->cols));
    delete paquete;
    return mat;
}


matrix_t * multmatrix_stub::createRandMatrix(int rows, int cols){ //Igual que crear identidad.
    //Crear una matriz random rows * cols.
    int tipo_operacion = OP_CREATE_RAND_MATRIX;
    matrix_t * mat = new matrix_t();
    char *paquete = new char[sizeof(int)*2];
    int datapaq = 0;
    sendMSG(this->server_id,(void**)&tipo_operacion,sizeof(int));

    //Empaquetamos la informacion.
    memcpy(paquete,&rows,sizeof(int));
    memcpy(&paquete[sizeof(int)],&cols,sizeof(int));

    //Enviamos el paquete.
    sendMSG(this->server_id,(void**)paquete,(sizeof(int)*2));
    
    delete paquete;
    //Recibimos el paquete
    recvMSG(this->server_id,(void**)&paquete,&datapaq);
   

    //Desempaquetamos el paquete.
    memcpy(&mat->rows,paquete,sizeof(int));
    memcpy(&mat->cols,&paquete[sizeof(int)],sizeof(int));

    mat->data = new int[mat->cols*mat->rows];
    memcpy(mat->data,&paquete[sizeof(int)*2],sizeof(int)*(mat->rows * mat->cols));

    delete paquete;
    return mat;
}

matrix_t * multmatrix_stub::multMatrix(matrix_t* m1, matrix_t *m2){
    //Tenemos 2 matrices y tenemos que multiplicarlas
    char * paquete = new char[sizeof(int)*(2*(m1->rows * m1->cols)+4)];
    matrix_t * mat = new matrix_t();
    int datapaq = 0;
    int tipo_operacion = OP_MULT_MATRIX;
    sendMSG(this->server_id,(void**)&tipo_operacion,sizeof(int));
    //Empaquetamos las matrices.
    memcpy(paquete,&m1->rows,sizeof(int));
    memcpy(&paquete[sizeof(int)],&m1->cols,sizeof(int));
    memcpy(&paquete[2*sizeof(int)],m1->data,sizeof(int)*(m1->rows*m1->cols));

    memcpy(&paquete[sizeof(int)*((m1->rows*m1->cols)+2)],&m2->rows,sizeof(int));
    memcpy(&paquete[sizeof(int)*((m1->rows*m1->cols)+3)],&m2->cols,sizeof(int));
    memcpy(&paquete[sizeof(int)*((m1->rows*m1->cols)+4)],m2->data,sizeof(int)*(m2->rows*m2->cols));

    //std::cout<<"Matrices empaquetadas"<<std::endl;

    sendMSG(this->server_id,(void**)paquete,sizeof(int)*((2*(m1->rows*m1->cols))+4));
    //std::cout<<"Matrices enviadas"<<std::endl;

    delete paquete;

    //Recibimos el paquete
    recvMSG(this->server_id,(void**)&paquete,&datapaq);
    //std::cout<<"Matriz recibida"<<std::endl;

    //Desempaqueto
    memcpy(&mat->rows,paquete,sizeof(int));
    memcpy(&mat->cols,&paquete[sizeof(int)],sizeof(int));
    mat->data = new int[mat->rows * mat->cols];
    memcpy(mat->data,&paquete[sizeof(int)*2],sizeof(int)*(mat->rows * mat->cols));

    delete paquete;
    return mat;
}
multmatrix_stub::~multmatrix_stub(){
    int operacion=OP_SALIR;
	sendMSG(this->server_id, (void*)&operacion, sizeof(int));
	closeConnection(this->server_id);
}