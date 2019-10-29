#include "ut.h"

double* definingUt(int k) {
    
    double *elementsOfMatrix_ut = (double*)malloc(sizeof(char)*k);

    if (!k) {
        elementsOfMatrix_ut[0] = 0;
        elementsOfMatrix_ut[1] = 0;
    } else if (k < 10) {
        elementsOfMatrix_ut[0] = 1;
        elementsOfMatrix_ut[1] = 0.2*M_PI;
    } else if (k >= 10) {
        elementsOfMatrix_ut[0] = 1;
        elementsOfMatrix_ut[1] = -(0.2*M_PI);
    }

    return elementsOfMatrix_ut;
}

void add_ut(char *string, int t) {

    if (!t) {
        strcat(string, "   ");
        strcat(string, "0");
        strcat(string, "   ");
    } else if (t < 10) {
        strcat(string, "   ");
        strcat(string, "1   0.628");
        strcat(string, "   ");
    } else if (t >= 10) {
        strcat(string, "   ");
        strcat(string, "1   -0.628");
        strcat(string, "   ");
    }
}