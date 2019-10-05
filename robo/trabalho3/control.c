#include "control.h"

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

void definingUt(double *elementsOfMatrix_ut, int t) { // set the values of u(t) according to the time
    
    if (!t) {
        elementsOfMatrix_ut[0] = 0;
        elementsOfMatrix_ut[1] = 0;
    } else if (t < 10) {
        elementsOfMatrix_ut[0] = 1;
        elementsOfMatrix_ut[1] = 0.2*M_PI;
    } else if (t >= 10) {
        elementsOfMatrix_ut[0] = 1;
        elementsOfMatrix_ut[1] = -(0.2*M_PI);
    }
}

void writingFile(char *string, char *file) {
    FILE *fp = fopen(file, "w+");
    fputs(string, fp);
}

void loopWriting(char *file, int loops,
            matrix *matrix_xt, matrix *matrix_identity) {

    double elementsOfMatrix_ut[3];
    char* tab = "   ";
    char stringToBeWritten[10000];
    int i = 0;

    while (i < loops) {

        definingUt(elementsOfMatrix_ut, i);

        matrix *matrix_ut = matrix_createMatrix("Matrix u(t)", 2, 1);
        matrix_putValues(matrix_ut, elementsOfMatrix_ut);

        matrix *matrixResponse_xt = matrix_multiply(matrix_xt, matrix_ut);

        matrix *matrix_yt = matrix_multiply(matrix_identity, matrixResponse_xt); // y(t)

        for (int k = 0; k < 3; k++) {
            char aux[100];
            snprintf(aux, 50, "%f", matrix_yt->matrix[k][0]);
            strcat(stringToBeWritten, aux);
            strcat(stringToBeWritten, " ");
        }
        strcat(stringToBeWritten, tab);
        i++;
    }
        writingFile(stringToBeWritten, file);
}

void performOperation(double xc, double yc, double tetha,
    double v, double omega, matrix **matrix_xt, matrix ** matrix_identity) { // response parameters of the control system

    double elementsOfMatrix_xt[7];
    double elementsOfIdentity[9];

    elementsOfMatrix_xt[0] = sin(xc);
    elementsOfMatrix_xt[1] = 0;
    elementsOfMatrix_xt[2] = cos(yc);
    elementsOfMatrix_xt[3] = 0;
    elementsOfMatrix_xt[4] = 0;
    elementsOfMatrix_xt[5] = 1;


    (*matrix_xt) = matrix_createMatrix("matrix1", 3, 2);
    matrix_putValues(*matrix_xt, elementsOfMatrix_xt);

    *matrix_identity = matrix_createMatrix("identity", 3, 3);
    identityMatrix(elementsOfIdentity);
    matrix_putValues(*matrix_identity, elementsOfIdentity);
    
}