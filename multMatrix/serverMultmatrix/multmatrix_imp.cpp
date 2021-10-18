#include "multmatrix_imp.h"

multmatrix_imp::multmatrix_imp(int client_id){
    this->cliente_id = client_id;
    this->salir = false;
    this->op_mat = new multMatrix(); //Operaciones con matrices

}

void multmatrix_imp::atenderOperacion(){
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
        case OP_READ_MATRIX:{
            char *nameFile = nullptr;
            matrix_t *mat = nullptr;
            char *paquete = nullptr;

            //Recibimos el mensaje con los datos de cada
            recvMSG(this->cliente_id,(void**)&nameFile,&dataLen);

            mat = this->op_mat->readMatrix(nameFile);

            paquete = new char[sizeof(int)*((mat->rows * mat->cols)+2)];
            
            //Empaquetamos la informacion.
            memcpy(paquete,&mat->rows,sizeof(int));
            memcpy(&paquete[sizeof(int)],&mat->cols,sizeof(int));
            memcpy(&paquete[2*sizeof(int)],mat->data,sizeof(int)*(mat->rows* mat->cols));
            
            //Mandamos la informacion.
            sendMSG(this->cliente_id,paquete,sizeof(int)*((mat->rows * mat->cols) + 2));

            delete paquete;
            delete mat;

        }break;
        case OP_MULT_MATRIX:{ //Multiplicar matrices

            matrix_t *mat1 = new matrix_t();
            matrix_t *mat2 = new matrix_t();
            matrix_t *resultado = nullptr;
            char * paquete = nullptr;
            int tam = 0;

            //recibir matrices
            recvMSG(this->cliente_id,(void**)&paquete,&tam);
            //std::cout<<"Matriz recibida"<<std::endl;
            //desempaquetar m1
            memcpy(&mat1->rows,paquete,sizeof(int));
            memcpy(&mat1->cols,&paquete[sizeof(int)],sizeof(int));
            mat1->data = new int[mat1->rows * mat1->cols];
            memcpy(mat1->data,&paquete[sizeof(int)*2],sizeof(int)*(mat1->rows*mat1->cols));
            //std::cout<<"Matriz m1 desempaquetada"<<std::endl;
            //desempaquetar m2
            memcpy(&mat2->rows,&paquete[sizeof(int)*(2 + (mat1->rows*mat1->cols))],sizeof(int));
            memcpy(&mat2->cols,&paquete[sizeof(int)*(3 + (mat1->rows*mat1->cols))],sizeof(int));
            mat2->data = new int[mat2->rows * mat2->cols];
            memcpy(mat2->data,&paquete[sizeof(int)*(4 + (mat1->rows*mat1->cols))],sizeof(int)*(mat2->rows*mat2->cols));

            delete paquete;
            //Guardamos el resultado de la multiplicacion
            resultado = this->op_mat->multMatrices(mat1,mat2);

            //Empaquetamos
            paquete = new char[sizeof(int)*((resultado->rows*resultado->cols)+2)];
            
            memcpy(paquete,&resultado->rows,sizeof(int));
            memcpy(&paquete[sizeof(int)],&resultado->cols,sizeof(int));
            memcpy(&paquete[2*sizeof(int)],resultado->data,sizeof(int)*(resultado->rows* resultado->cols));

            //Enviamos paquete
            sendMSG(this->cliente_id,(void**)paquete,sizeof(int)*((resultado->rows * resultado->cols) + 2));

            delete paquete;
            delete resultado;

        }break;

        case OP_WRITE_MATRIX:{
            matrix_t *mat = new matrix_t();
            char *paquete = nullptr;
            int dataLen = 0;
            char *filename = nullptr;
            int lenfich = 0;

            //Recibimos el paquete.
            recvMSG(this->cliente_id,(void**)&paquete,&dataLen);

            //Desempaquetamos matriz y fichName
            memcpy(&mat->rows,paquete,sizeof(int));
            memcpy(&mat->cols,&paquete[sizeof(int)],sizeof(int)); //Desmp. fil y col
            mat->data = new int[ mat->rows * mat->cols]; //Mem -> para data
            memcpy(mat->data,&paquete[sizeof(int)*2],sizeof(int)*(mat->cols*mat->rows)); //Desmp. data
            lenfich = dataLen - (sizeof(int)*(mat->cols*mat->rows)+2); //calc. bytes fichName
            filename = new char[lenfich];//Mem -> fichName
            memcpy(filename,&paquete[(sizeof(int)*(mat->cols*mat->rows)+2)],lenfich); //Desemp. fichName

            int i = 0;
            for (i = 0; i< (mat->rows * mat->cols);i++){ 
                std::cout<<"pos["<<i<<"]: "<<mat->data[i]<<std::endl;
            }

            this->op_mat->writeMatrix(mat,filename);

            delete filename;
            delete mat;
            delete paquete;

        }break;
        case OP_CREATE_IDENTITY:{ //Crearmatriz identidad.
            int rows = 0;
            int cols = 0;
            char * paquete = nullptr;
            int tam = 0;
            matrix_t *mat = nullptr;

            //Recibimos paquete
            recvMSG(this->cliente_id,(void**)&paquete,&tam);
            
            //Desempaquetamos.
            memcpy(&rows,paquete,sizeof(int));
            memcpy(&cols,&paquete[sizeof(int)],sizeof(int));

            mat = this->op_mat->createIdentity(rows,cols);
            
            //Empaquetamos
            paquete = new char[sizeof(int)*((rows*cols)+2)];
            memcpy(paquete,&mat->rows,sizeof(int));
            memcpy(&paquete[sizeof(int)],&mat->cols,sizeof(int));
            memcpy(&paquete[2*sizeof(int)],mat->data,sizeof(int)*(mat->rows* mat->cols));

            sendMSG(this->cliente_id,(void**)paquete,sizeof(int)*((mat->rows * mat->cols) + 2));

            delete paquete;
            delete mat;

        }break;
        case OP_CREATE_RAND_MATRIX:{
            int rows = 0;
            int cols = 0;
            char * paquete = nullptr;
            int tam = 0;
            matrix_t *mat = nullptr;
            
            //Recibimos paquete
            recvMSG(this->cliente_id,(void**)&paquete,&tam);
            
            //Desempaquetamos.
            memcpy(&rows,paquete,sizeof(int));
            memcpy(&cols,&paquete[sizeof(int)],sizeof(int));

            mat = this->op_mat->createRandMatrix(rows,cols);

            //Empaquetamos
            paquete = new char[sizeof(int)*((rows*cols)+2)];
            memcpy(paquete,&mat->rows,sizeof(int));
            memcpy(&paquete[sizeof(int)],&mat->cols,sizeof(int));
            memcpy(&paquete[2*sizeof(int)],mat->data,sizeof(int)*(mat->rows * mat->cols));
            
            sendMSG(this->cliente_id,(void**)paquete,sizeof(int)*((mat->rows * mat->cols) + 2));


        }break;
        default:
            break;
        }
    }
    
}

multmatrix_imp::~multmatrix_imp(){
    delete this->op_mat;
}