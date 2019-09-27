#include "difference.h"

void differenceArgv(char *valueOne, char *valueTwo) {
    int value1 = atoi(valueOne);
    int value2 = atoi(valueTwo);

    int difference = value1 - value2;

    printf("A diferença dos valores é (%d)\n", difference);
}