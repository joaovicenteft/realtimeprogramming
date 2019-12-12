#include "stdint.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
// header da função u(t)

#ifndef M_PI
    #define M_PI 3.14159265358978
#endif

void add_ut(char *string, int t); // adiciona os valores de u(t) em um string
double* definingUt(int k); // define o valor de u(k) de acordo com k