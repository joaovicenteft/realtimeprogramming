include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ut.h"
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358978
#endif

void writingFile(char *string, char *file);

void loopWriting(char *file, int loops, double xc, double yc);

void identityMatrix(double *matrixNotIdentity);
