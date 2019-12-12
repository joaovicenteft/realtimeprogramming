#include "statistics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "math.h"

void biggestNumber(double *jitter, double *biggestNumber, int fullTime) {

    for (int i = 0; i < fullTime; i++) {
        if (jitter[i] > (*biggestNumber)) {
            (*biggestNumber) = jitter[i];
        }
    }
}

void smalestNumber(double *jitter, double *smalestNumber, int fullTime) {
    for (int i = 0; i < fullTime; i++) {
        if (jitter[i] < (*smalestNumber)) {
            (*smalestNumber) = jitter[i];
        }
    }
}

void varianca(double *jitter, double *varianca, int fullTime, int jitterMean) {
    
    for (int i = 0; i < fullTime; i++) {
        (*varianca) += ((jitter[i]-jitterMean)*(jitter[i]-jitterMean));
    }

    (*varianca) = (*varianca)/(fullTime-1);
}

void desvio(double varianca, double *desvio) {
    (*desvio) = sqrt((varianca));
}

void soma(double *soma, int fullTime, double *jitter) {

    for (int i = 0; i < fullTime; i++) {
        (*soma) +=  jitter[i];
    }
}

void Statistics_Calculing(double* jitterRef, double* jitterModeloRef, double* jitterControle,
 double* jitterLinear, double* jitterRobo, int *fullTime)
{

    // soma de cada jitter
    double somaRef=0, somaModeloRef=0, somaControle=0, somaLinear=0, somaRobo=0;

    // maximo de cada jitter
    double maximoRef = 0, maximoModeloRef = 0, maximoControle = 0, maximoLinear = 0, maximoRobo = 0;
    
    // minimo de cada jitter
    double minimoRef = 100000, minimoModeloRef = 100000, minimoControle = 100000, minimoLinear = 100000, minimoRobo = 10000;
    
    // media de cada jitter
    double mediaRef, mediaModeloRef, mediaControle, mediaLinear, mediaRobo;
    
    // new parameters
    
    double variancaRef, variancaModeloRef, variancaControle, variancaLinear, variancaRobo;
    double desvioRef, desvioModeloRef, desvioControle, desvioLinear, desvioRobo;

    // end new parameters


    soma(&somaRef, fullTime[0], jitterRef);
    soma(&somaModeloRef, fullTime[1], jitterModeloRef);
    soma(&somaLinear, fullTime[2], jitterLinear);
    soma(&somaControle, fullTime[3], jitterControle);
    soma(&somaRobo, fullTime[4], jitterRobo);

    mediaRef = somaRef/fullTime[0];
    mediaModeloRef = somaModeloRef/fullTime[1];
    mediaControle = somaControle/fullTime[2];
    mediaRobo = somaRobo/fullTime[3];
    mediaLinear = somaLinear/fullTime[4];

    printf("\n");

    // maior e menor de cada tempo

    // cálculo do maior tempo
    biggestNumber(jitterRef, &maximoRef, fullTime[0]);
    biggestNumber(jitterModeloRef, &maximoModeloRef, fullTime[1]);
    biggestNumber(jitterControle, &maximoControle, fullTime[2]);
    biggestNumber(jitterLinear, &maximoLinear, fullTime[3]);
    biggestNumber(jitterRobo, &maximoRobo, fullTime[4]);


    // cálculo do menor tempo
    smalestNumber(jitterRef, &minimoRef, fullTime[0]);
    smalestNumber(jitterModeloRef, &minimoModeloRef, fullTime[1]);
    smalestNumber(jitterControle, &minimoControle, fullTime[2]);
    smalestNumber(jitterLinear, &minimoLinear, fullTime[3]);
    smalestNumber(jitterRobo, &minimoRobo, fullTime[4]);

    
    ///////////////////////////////////////////

    // cálculo da variança
    varianca(jitterRef, &variancaRef, fullTime[0], mediaRef);
    varianca(jitterModeloRef, &variancaModeloRef, fullTime[1], mediaRef);
    varianca(jitterControle, &variancaControle, fullTime[2], mediaControle);
    varianca(jitterLinear, &variancaLinear, fullTime[3], mediaLinear);
    varianca(jitterRobo, &variancaRobo, fullTime[4], mediaRobo);

    // cálculo do desvio

    desvio(variancaRef, &desvioRef);
    desvio(variancaModeloRef, &desvioModeloRef);
    desvio(variancaControle, &desvioControle);
    desvio(variancaLinear, &desvioLinear);
    desvio(variancaRobo, &desvioRobo);

    printf("Soma referência (%.3lf)\n", somaRef);
    printf("Soma modelo (%.3lf)\n", somaModeloRef);
    printf("Soma controle (%.3lf)\n", somaControle);
    printf("Soma linear (%.3lf)\n", somaLinear);
    printf("Soma robô (%.3lf)\n", somaRobo);

    printf("\n");

    printf("Maior referência (%.3lf)\n", maximoRef);
    printf("Maior modelo (%.3lf)\n", maximoModeloRef);
    printf("Maior controle (%.3lf)\n", maximoControle);
    printf("Maior linear (%.3lf)\n", maximoLinear);
    printf("Maior robô (%.3lf)\n", maximoRobo);

    printf("\n");

    printf("Menor referência (%.3lf)\n", minimoRef);
    printf("Menor modelo (%.3lf)\n", minimoModeloRef);
    printf("Menor controle (%.3lf)\n", minimoControle);
    printf("Menor linear (%.3lf)\n", minimoLinear);
    printf("Menor robô (%.3lf)\n", minimoRobo);

    printf("\n");

    printf("Variância referência (%.3lf)\n", variancaRef);
    printf("Variância modelo (%.3lf)\n", variancaModeloRef);
    printf("Variância controle (%.3lf)\n", variancaControle);
    printf("Variância linear (%.3lf)\n", variancaLinear);
    printf("Variância robô (%.3lf)\n", variancaRobo);

    printf("\n");

    printf("Desvio referência (%.3lf)\n", desvioRef);
    printf("Desvio modelo (%.3lf)\n", desvioModeloRef);
    printf("Desvio controle (%.3lf)\n", desvioControle);
    printf("Desvio linear (%.3lf)\n", desvioLinear);
    printf("Desvio robô (%.3lf)\n", desvioRobo);

    printf("\n");
}