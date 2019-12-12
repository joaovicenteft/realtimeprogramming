#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358978
#endif

#ifndef Alpha1
    #define Alpha1 1
#endif

#ifndef Alpha2
    #define Alpha2 1
#endif

matrix* definedRef(double t);
matrix* Linearizacao(matrix*xt, matrix* vt, double R);
matrix* RoboXtLinha(matrix* xt, matrix* ut);
matrix* RoboXt(matrix* XtLinha, matrix* XtLinhaAntigo, double t);
matrix* RoboYt(matrix* xt, double R);
matrix* ModeloRefYmLinha(matrix* Ref, matrix* Ym);
matrix* ModeloRefYm(matrix* YmLinha, matrix* YmLinhaAntigo, double t);
matrix* ControleBloco(matrix* YmLinha, matrix* Ym, matrix* Yt);