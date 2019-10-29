#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

matrix * matrix_createMatrix(char*nome,int lines,int columns){
    matrix * d;
    d = malloc (sizeof (struct matriz));
    d->column=columns;
    d->line=lines;
    strcpy(d->name,nome);
    return d;
}

void matrix_putValues(matrix*d, double*putValues)
{
    int cont=0;
    int i, j;
    for (i=0; i<d->line; i++ ){
        for (j=0; j<d->column; j++ ){ 
            d->matrix[i][j]=putValues[cont];
            cont++;
        }
    }
    return;
}

void matrix_printMatrix(matrix*d)
{
    double AUX;
    printf("%s\n",d->name);
    int i, j;
    for (i=0; i<d->line; i++ ){
        printf("| ");
        for (j=0; j<d->column; j++ ){ 
            AUX=d->matrix[i][j];
            printf("%lf ",AUX);
        }
        printf("|\n");
    }
    return;
}

matrix * matrix_sum(matrix*a,matrix*b)
{
    int i, j;
    matrix * d;
    d->column=a->column;
    d->line=b->line;
    d = malloc (sizeof (struct matriz));
    if((a->column!=b->column)&&(a->line!=b->line)){
        printf("N possible do that, The matrix's have a diferent order!!\n");
        return d;
    }
    strcpy(d->name,"Result");
    for (i=0; i<d->line; i++ ){
        for (j=0; j<d->column; j++ ){ 
            d->matrix[i][j]=a->matrix[i][j]+b->matrix[i][j];
        }
    }
    return d;
}

matrix * matrix_subtract(matrix*a,matrix*b)
{
    int i, j;
    matrix * d;
    d = malloc (sizeof (struct matriz));
    d->column=a->column;
    d->line=b->line;
    if((a->column!=b->column)&&(a->line!=b->line)){
        printf("N possible do that, The matrix's have a diferent order!!\n");
        return d;
    }
    strcpy(d->name,"Result");
    for (i=0; i<d->line; i++ ){
        for (j=0; j<d->column; j++ ){ 
            d->matrix[i][j]=a->matrix[i][j]-b->matrix[i][j];
        }
    }
    return d;
}
matrix * matrix_multiply(matrix*a,matrix*b)
{
    int i, j, l;
    matrix * d;
    d = malloc(sizeof(struct matriz));
    d->column=b->column;
    d->line=a->line;
    strcpy(d->name,"Result");
    if((a->column!=b->line)&&(a->line!=b->column)){
        printf("Is not possible to do this, the matrix has a situation!!\n");
        return d;
    }
    for (i=0; i<d->line; i++ )
    {
        for (j=0; j<d->column; j++ )
        { 
            d->matrix[i][j]=0;
            for(l=0; l<b->line; l++)
            {
                d->matrix[i][j]=d->matrix[i][j]+(a->matrix[i][l]*b->matrix[l][j]);
            }
        }
    }
    return d;
}

void matrix_addScalar(matrix*a,double toAdd)
{
    int i, j;
    for (i=0; i<a->line; i++ ){
        for (j=0; j<a->column; j++ ){ 
            a->matrix[i][j]=a->matrix[i][j]+toAdd;
        }
    }
    return;
}

void matrix_multiScalar(matrix*a,double toMulti)
{
    int i, j;
    for (i=0; i<a->line; i++ ){
        for (j=0; j<a->column; j++ ){ 
            a->matrix[i][j]=a->matrix[i][j]*toMulti;
        }
    }
    return;
}

matrix * matrix_transposed(matrix * a)
{
    int i, j;
    matrix * d;
    d = malloc(sizeof(struct matriz));
    d->column=a->line;;
    d->line=a->column;
    strcpy(d->name,"Transposed");
    for (i=0; i<d->line; i++ ){
        for (j=0; j<d->column; j++ ){ 
            d->matrix[i][j]=a->matrix[j][i];
        }
    }
    return d;
}
matrix* matrix_reduce(matrix*a,int line,int column)
{
    int i, j;
    matrix * d;
    d = malloc(sizeof(struct matriz));
    d->column=a->line-1;;
    d->line=a->column-1;
    strcpy(d->name,"rEDUCE");
    int i2=0;
    int j2=0;
    for (i=0;i<d->line;i++){
        if(i2==line) i2++;
        j2=0;
        for (j=0;j<d->column;j++){
            if(j2==column) j2++; 
            d->matrix[i][j]=a->matrix[i2][j2];
            j2++;
        }
        i2++;
    }
    return d;
}
double pow(double base,double pot)
{
    int i;
    double result=1;
    for(i=0;i<pot;i++){
        result*=base;
    }
    return result;
}
double matrix_determinant(matrix*a)
{
    int j;
    if(a->line==1) return a->matrix[0][0];
    else if(a->line==2){
        return (a->matrix[0][0]*a->matrix[1][1])-(a->matrix[0][1]*a->matrix[1][0]);
    }else{
        double result=0;
        for(j=0;j<a->column;j++){
            matrix*AUX=matrix_reduce(a,0,j);
            result+=a->matrix[0][j]*(pow(-1,j)*matrix_determinant(AUX));
            free(AUX);
        }
        return result;
    }
}
matrix * matrix_adj(matrix * a)
{
    int i, j;
    matrix * d;
    d = malloc(sizeof(struct matriz));
    d->column=a->line;
    d->line=a->column;
    strcpy(d->name,"Adjunt");
    for (i=0; i<d->line; i++ ){
        for (j=0; j<d->column; j++ ){ 
            matrix * AUX=matrix_reduce(a,i,j);
            d->matrix[i][j]=(pow(-1,i+j) * matrix_determinant(AUX));
            free(AUX);
        }
    }
    return d;
}
matrix * matrix_invers(matrix * a)
{
    matrix * d = matrix_adj(a);
    if(matrix_determinant(a)!=0){
        matrix_multiScalar(d,(1/matrix_determinant(a)));
        strcpy(d->name,"Inverse");
        return d;
    }else{
        printf("Impossible to inverte the matrix");
        strcpy(d->name,"NPosible");
        return d;
    }
}

void identityMatrix(double *matrixNotIdentity) {
    int k = 1;

    matrixNotIdentity[0] = 1;

    for (int i = 1; i < 9; i++) {
        if (k == 4) {
            matrixNotIdentity[i] = 1;
            k = 0;
        } else {
            matrixNotIdentity[i] = 0;
        }
        k++;
    }
}