#include "stdio.h"
#include "stdlib.h"

double* functionVector(int t) {

    double *vectorOfThis = (double*)malloc(sizeof(char)*100);

    for (int i = 0; i < t; i++) {
        vectorOfThis[i] = i;
    }

    return vectorOfThis;
}



int main(int argc, char *argv[]) {

    double *vectorR;
    vectorR = functionVector(8);

    printf("%lf\n", vectorR[2]);
}