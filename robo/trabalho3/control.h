#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358978
#endif

void add_ut(char *string, int t);

void writingFile(char *string, char *file);

void loopWriting(char *file, int loops,
            matrix *matrix_xt, matrix *matrix_identity);

void identityMatrix(double *matrixNotIdentity);

void definingUt(double *elementsOfMatrix_ut, int t);
// set the values of u(t) according to the time

void performOperation(double xc, double yc, double tetha,
    double v, double omega, matrix **matrix_xt, matrix ** matrix_identity);