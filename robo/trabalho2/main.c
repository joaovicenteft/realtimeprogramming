#include "matrix.h"
#include <stdio.h>
#include <string.h>

int main()
{

    double tentando[16];
    tentando[0]=1;
    tentando[1]=0;
    tentando[2]=0;
    tentando[3]=1;
    tentando[4]=1;
    tentando[5]=2;
    tentando[6]=3;
    tentando[7]=2;
    tentando[8]=2;
    tentando[9]=3;
    tentando[10]=4;
    tentando[11]=0;
    tentando[12]=1;
    tentando[13]=2;
    tentando[14]=-1;
    tentando[15]=-2;
    matrix*matriz1=matrix_createMatrix("Matriz1",3,3);
    matrix_putValues(matriz1,tentando);
    matrix*matriz2=matrix_createMatrix("Matriz2",3,3);
    matrix_putValues(matriz2,tentando+3);
    printf("Dada as duas matrizes:\n");
    matrix_printMatrix(matriz1);
    matrix_printMatrix(matriz2);
    printf("A Biblioteca Pode fazer as seguintes operações.\n");
    printf("Soma:\n");
    matrix*soma=matrix_sum(matriz1,matriz2);
    matrix_printMatrix(soma);
    printf("Subtração:\n");
    matrix*subtracao=matrix_subtract(matriz1,matriz2);
    matrix_printMatrix(subtracao);
    printf("Multiplicação:\n");
    matrix*multi=matrix_multiply(matriz1,matriz2);
    matrix_printMatrix(multi);
    printf("Outro Exemplo de multiplicação com matrizes de ordens diferentes porem com\nnumeros de linhas igual ao numero de colunas da outra:\n");
    matrix*matriz3=matrix_createMatrix("Matriz3",4,2);
    matrix_putValues(matriz3,tentando);
    matrix*matriz4=matrix_createMatrix("Matriz4",2,3);
    matrix_putValues(matriz4,tentando+3);
    printf("Dada as duas matrizes:\n");
    matrix_printMatrix(matriz3);
    matrix_printMatrix(matriz4);
    printf("Multiplicação:\n");
    matrix*multi2=matrix_multiply(matriz3,matriz4);
    matrix_printMatrix(multi2);
    printf("Agora para demonstrar as operações por escalar\ntemos a Matriz4 e a escalar 5:\n");
    matrix_printMatrix(matriz4);
    printf("Matriz4+5=\n");
    matrix_addScalar(matriz4,5);
    matrix_printMatrix(matriz4);
    printf("Matriz4-5=\n");
    matrix_addScalar(matriz4,-10);
    matrix_printMatrix(matriz4);
    matrix_addScalar(matriz4,5);
    printf("Matriz4*5=\n");
    matrix_multiScalar(matriz4,5);
    matrix_printMatrix(matriz4);
    printf("Agora demonstrando a matriz tranposta:\n");
    matrix_printMatrix(matriz4);
    multi2=matrix_transposed(matriz4);
    matrix_printMatrix(multi2);
    printf("Para o exemplo do determinante, temos a seguinte matriz:\n");
    matrix*matrizA=matrix_createMatrix("MatrizA",4,4);
    matrix_putValues(matrizA,tentando);
    matrix_printMatrix(matrizA);
    printf("Determinante: %lf\n",matrix_determinant(matrizA));
    printf("Matriz invertida de será:");
    multi2=matrix_invers(matrizA);
    matrix_printMatrix(multi2);
    return 0;
}