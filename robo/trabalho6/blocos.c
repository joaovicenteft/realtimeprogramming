#include "matrix.h"
#include "blocos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>

//definir BufferRef
matrix* definedRef(double t)
{
    matrix* toReturn = matrix_createMatrix("Ref",2,1);
    double aux[2];
    aux[0]=(5/M_PI)*cos(0.2*M_PI*t);
    if (t<10) {
        aux[1]=(5/M_PI)*sin(0.2*M_PI*t);
    } else  {
        aux[1]=-1*(5/M_PI)*sin(0.2*M_PI*t);
    } 
    matrix_putValues(toReturn,aux);
    return toReturn;
}


// Bloco de Linearização
matrix* Linearizacao(matrix*xt, matrix* vt, double R)
{
    matrix*L=matrix_createMatrix("L",2,2);
    double LTerms[4] = {cos(xt->matrix[2][0]), -R*sin(xt->matrix[2][0]), sin(xt->matrix[2][0]), R*cos(xt->matrix[2][0])};
    matrix_putValues(L, LTerms);
    matrix*LInvers=matrix_invers(L);
    return matrix_multiply(LInvers,vt);
}

//As Duas Proximas funções são reponsaveir pelo bloco robo, dever ser executadas em sequencia
matrix* RoboXtLinha(matrix* xt, matrix* ut)
{
    matrix*Aux=matrix_createMatrix("Aux",3,2);//criei uma 2x2
    double AuxTerms[6] = {cos(xt->matrix[2][0]), 0, sin(xt->matrix[2][0]), 0, 0, 1};
    matrix_putValues(Aux,AuxTerms);//coloquei os valores do vetor na matrix 2x2
    return matrix_multiply(Aux,ut);//retornei a multiplicação
}
matrix* RoboXt(matrix* XtLinha, matrix* XtLinhaAntigo, double t)
{
    matrix* Xt = matrix_createMatrix("Xt",3,1);
    double aux[3] = {(t-(t-0.12))*(XtLinha->matrix[0][0]+XtLinhaAntigo->matrix[0][0])/2, (t-(t-0.12))*(XtLinha->matrix[1][0]+XtLinhaAntigo->matrix[1][0])/2, (t-(t-0.12))*(XtLinha->matrix[2][0]+XtLinhaAntigo->matrix[2][0])/2};
    matrix_putValues(Xt, aux);
    return Xt;
}
matrix* RoboYt(matrix* xt, double R)
{
    matrix* Aux=matrix_createMatrix("Aux",2,3);//criei uma 2x2
    double AuxTerms[6] = {1, 0, 0, 0, 1, 0};
    matrix_putValues(Aux, AuxTerms);
    matrix* Aux2=matrix_createMatrix("Aux2", 2, 1);
    double AuxTerms2[2] = { R*cos(xt->matrix[2][0]), R*sin(xt->matrix[2][0])};
    matrix_putValues(Aux2, AuxTerms2);
    Aux=matrix_multiply(Aux, xt);
    Aux->matrix[0][0]=Aux->matrix[0][0]+Aux2->matrix[0][0];
    Aux->matrix[1][0]=Aux->matrix[1][0]+Aux2->matrix[1][0];
    return Aux;
}
//fim do bloco Robo

//Bloco do Modelo Ref, Formula para ym e YmLinha
matrix* ModeloRefYmLinha(matrix* Ref, matrix* Ym)
{
    matrix* ymLinha = matrix_createMatrix("Ym/",2,1);
    double aux[2] = { Alpha1*(Ref->matrix[0][0]-Ym->matrix[0][0]), Alpha2*(Ref->matrix[1][0]-Ym->matrix[1][0])};
    matrix_putValues(ymLinha, aux);
    return ymLinha;
}

matrix* ModeloRefYm(matrix* YmLinha, matrix* YmLinhaAntigo, double t)
{
    matrix* ym = matrix_createMatrix("Ym",2,1);
    double aux[2] = {(t-(t-0.12))*(YmLinha->matrix[0][0]+YmLinhaAntigo->matrix[0][0])/2, (t-(t-0.12))*(YmLinha->matrix[1][0]+YmLinhaAntigo->matrix[1][0])/2};
    matrix_putValues(ym, aux);
    return ym;
}

//Funções para definir o Bloco de controle v(T)
matrix* ControleBloco(matrix* YmLinha, matrix* Ym, matrix* Yt)
{
    matrix* Vt = matrix_createMatrix("Vt",2,1);
    double aux[2] = { YmLinha->matrix[0][0] + Alpha1*( Ym->matrix[0][0] - Yt->matrix[0][0] ) , YmLinha->matrix[1][0] + Alpha2*( Ym->matrix[1][0] - Yt->matrix[1][0] )};
    matrix_putValues(Vt,aux);
    return Vt;
}
