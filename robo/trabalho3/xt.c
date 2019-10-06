#include "xt.h"

void insertElementsOfXt(double xc, double yc, double *elementsOfMatrix_xt) {

    elementsOfMatrix_xt[0] = sin(xc);
    elementsOfMatrix_xt[1] = 0;
    elementsOfMatrix_xt[2] = cos(yc);
    elementsOfMatrix_xt[3] = 0;
    elementsOfMatrix_xt[4] = 0;
    elementsOfMatrix_xt[5] = 1;

}