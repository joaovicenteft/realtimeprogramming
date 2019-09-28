#include "sum.h"

void sumArgv(char *valueOne, char *valueTwo) {
    int value1 = atoi(valueOne);
    int value2 = atoi(valueTwo);

    int sum = value1 + value2;

    printf("A soma dos valores é (%d)\n", sum);
}
