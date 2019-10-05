#include "stdio.h"
#include "stdlib.h"
#include "control.h"

int main(int argc, char *argv[]) {

    matrix *matrix_xt, *matrix_identity;
    performOperation(1, 1, 1, 1, 1, &matrix_xt, &matrix_identity);
    loopWriting(argv[1], 20, matrix_xt, matrix_identity);
}