#include "p1.h"

void processingData(char *stringOne, char *stringTwo) {
    int one = atoi(stringOne);
    int two = atoi(stringTwo);

    int sum = one + two; // irrelevant
    int difference = one - two; // from one to two


    printf("sum (%d) | difference (%d)\n", sum, difference);
}