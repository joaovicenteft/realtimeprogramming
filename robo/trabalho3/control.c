#include "control.h"
#include "xt.h"


void writingFile(char *string, char *file) {
    FILE *fp = fopen(file, "w+");
    fputs(string, fp);
}

void loopWriting(char *file, int loops) {

    double elementsOfMatrix_xt[7];
    double elementsOfIdentity[9];
    double *elementsOfMatrix_ut;
    char* tab = "   ";
    char stringToBeWritten[10000];
    int i = 0;

    matrix *(matrix_identity) = matrix_createMatrix("identity", 3, 3);
    identityMatrix(elementsOfIdentity);
    matrix_putValues(matrix_identity, elementsOfIdentity);

    matrix *(matrix_xt) = matrix_createMatrix("matrix_xt,", 3, 2);
    insertElementsOfXt(1 , 1,elementsOfMatrix_xt);
    matrix_putValues(matrix_xt, elementsOfMatrix_xt);

    while (i <= loops) {

        elementsOfMatrix_ut = definingUt(i);


        matrix *matrix_ut = matrix_createMatrix("Matrix u(t)", 2, 1);
        matrix_putValues(matrix_ut, elementsOfMatrix_ut);

        matrix *matrixResponse_xt = matrix_multiply(matrix_xt, matrix_ut);

        matrix *matrix_yt = matrix_multiply(matrix_identity, matrixResponse_xt); // y(t)

        char aux[100];
        snprintf(aux, 50, "%d", i);
        strcat(stringToBeWritten, aux);
        strcat(stringToBeWritten, "   ");

        add_ut(stringToBeWritten, i);

        for (int k = 0; k < 3; k++) {
            char aux[100];
            snprintf(aux, 50, "%f", matrix_yt->matrix[k][0]);
            strcat(stringToBeWritten, aux);
            strcat(stringToBeWritten, "   ");
        }

        strcat(stringToBeWritten, tab);
        strcat(stringToBeWritten, "\n");
        i++;
    }

        writingFile(stringToBeWritten, file);
}