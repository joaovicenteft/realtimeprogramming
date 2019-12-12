#include "matrix.h"
#include "yf.h"


void calculingXt(matrix*ut,int t,double*vetor) {
    double retorno[3];
    vetor[0]=-(cos((ut->matrix[1][0]*t)/57.29)/ut->matrix[1][0]);
    vetor[1]=(sin((ut->matrix[1][0]*t)/57.29)/ut->matrix[1][0]);
    vetor[2]=ut->matrix[1][0]*t;
    return;
}
