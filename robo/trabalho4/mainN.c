#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>
#include "matrix.h"
#include "ut.h"
#include "yf.h"
#include <math.h>

#define MAX (20)

matrix *bufferU,*bufferYf;

sem_t bufferUCheio;
sem_t bufferUVazio;
sem_t AuxU;

sem_t bufferYfCheio;
sem_t bufferYfVazio;
sem_t AuxYf;
char stringToBeWritten[10000];
int k = 0;
double d = 10;
double auxVe[3];

void writingFile(char *string, char *file) {
    FILE *fp = fopen(file, "w+");
    fputs(string, fp);
}

void *tarefa1 (void*args){
    while(k<=MAX){
        sem_wait(&bufferUVazio);
        sem_wait(&AuxU);

        matrix_putValues(bufferU,definingUt(k));

        sem_post(&AuxU);
        sem_post(&bufferUCheio);

        sem_wait(&bufferYfCheio);
        sem_wait(&AuxYf);
        
        char aux[100];
        snprintf(aux, 50, "%d", k);
        strcat(stringToBeWritten, aux);
        strcat(stringToBeWritten, "   ");
        add_ut(stringToBeWritten, k);
        
        for (int i = 0; i < 3; i++) {
            char aux[100];
            snprintf(aux, 50, "%f", bufferYf->matrix[i][0]);
            strcat(stringToBeWritten, aux);
        
        for (int i = 0; i < 3; i++) {
            char aux[100];
            snprintf(aux, 50, "%f", bufferYf->matrix[i][0]);
            strcat(stringToBeWritten, aux);
            strcat(stringToBeWritten, "   ");
        }
            strcat(stringToBeWritten, "   ");
        }
        strcat(stringToBeWritten,  "   ");
        strcat(stringToBeWritten, "\n");
        k=k+1;

        sem_post(&AuxYf);
        sem_post(&bufferYfVazio);
    }
    writingFile(stringToBeWritten, "out");
    return NULL;
}

void *tarefa2 (void*args){

    while(k<MAX){
        sem_wait(&bufferUCheio);
        sem_wait(&AuxU);

        sem_wait(&bufferYfVazio);
        sem_wait(&AuxYf);
        calculingXt(bufferU,k,auxVe);
        matrix_putValues(bufferYf,auxVe);
        matrix_multiScalar(bufferYf,(1+(0.5*d*cos((bufferU->matrix[1][0]*k)/57.29))));

        sem_post(&AuxYf);
        sem_post(&bufferYfCheio);

        sem_post(&AuxU);
        sem_post(&bufferUVazio);
    }

    return NULL;
}
int main(int argc, char *argv[]){

    sem_init(&bufferUCheio, 0,  0);
    sem_init(& bufferUVazio, 0,  1);
    sem_init(&AuxU, 0,  1);

    sem_init(&bufferYfCheio, 0,  0);
    sem_init(&bufferYfVazio, 0,  1);
    sem_init(&AuxYf, 0,  1);

    bufferU = matrix_createMatrix("u",2,1);
    bufferYf = matrix_createMatrix("Yf",3,1);

    pthread_t Ttarefa1, Ttarefa2;
    pthread_create(&Ttarefa1, NULL, tarefa1, NULL);
    pthread_create(&Ttarefa2, NULL, tarefa2, NULL);
    
    pthread_join(Ttarefa1, NULL);
    pthread_join(Ttarefa2, NULL);

}
