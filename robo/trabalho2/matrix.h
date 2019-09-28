#ifndef MATRIX_H
#define MATRIX_H
#define MAX_LINE 10
#define MAX_COL 10
#define MAX_CHAR_NAME 10

typedef struct matriz{

    double matrix[MAX_LINE][MAX_COL];
    int line;
    int column;
    char name[MAX_CHAR_NAME];

}matrix;

void matrix_putValues(matrix*d, double*putValues);
matrix * matrix_createMatrix(char*nome,int lines,int columns);
void matrix_printMatrix(matrix*d);
matrix * matrix_sum(matrix*a,matrix*b);
matrix * matrix_subtract(matrix*a,matrix*b);
matrix * matrix_multiply(matrix*a,matrix*b);
void matrix_addScalar(matrix*a,double toAdd);
void matrix_multiScalar(matrix*a,double toMulti);
matrix * matrix_transposed(matrix * a);
matrix* matrix_reduce(matrix*a,int line,int column);
double pow(double base,double pot);
double matrix_determinant(matrix*a);
matrix * matrix_adj(matrix * a);
matrix * matrix_invers(matrix * a);

#endif