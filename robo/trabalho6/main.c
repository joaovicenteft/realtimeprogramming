#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include "statistics.h"
#include "matrix.h"
#include "blocos.h"
#ifndef TempMax
    #define TempMax 20
#endif

//os buffers serão as variaveis entre os blocos, vão ser dados por matrizes
matrix *bufferV, *bufferU, *bufferY, *bufferX, *XtLinha, *bufferRef, *bufferYm, *bufferYmLinha, *auxBuffer,  *auxBuffer2;
double R= 0.6/2;
double t = 0;

//Contadores de Jitter
double JitterRef120[400];
double JitterModeloRef[400];
double JitterControle[400];
double JitterLinearizacao[400];
double JitterRobo[400];



int contRef120=0;
int contModeloRef=0;
int contControle=0;
int contLinearizacao=0;
int contRobo=0;

//Semaforos para os Produtores
sem_t ProduzRef, ProduzY, ProduzYm, ProduzYmLinha, ProduzV, ProduzX, ProduzU;

//Semaforos Para os Consumidores
sem_t ConsomeRef, ConsomeY, ConsomeYm, ConsomeYmLinha, ConsomeV, ConsomeX, ConsomeU;

//Gerar Ref
void* Ref120(void*args)
{
    clock_t start;
    double dif;
    while(t<=TempMax)
    {   
        start=clock();
        sem_wait(&ProduzRef);
            bufferRef=definedRef(t);
            t=t+0.12;
        sem_post(&ConsomeRef);
        dif=difftime(clock(), start);
        JitterRef120[contRef120]=120 - dif/1000.0;
        usleep(120000-dif);
        contRef120++;
    }
}
//Bloco ModeloRef
void* ModeloRef(void*args)
{
    clock_t start;
    double dif;
    while(t<=TempMax)
    {
        start=clock();
        sem_wait(&ConsomeRef);
        sem_wait(&ProduzYm);
        sem_wait(&ProduzYmLinha);
            auxBuffer=bufferYmLinha;
            bufferYmLinha=ModeloRefYmLinha(bufferRef,bufferYm);
            bufferYm=ModeloRefYm(bufferYmLinha, auxBuffer, t);
        sem_post(&ProduzRef);
        sem_post(&ConsomeYm);
        sem_post(&ConsomeYmLinha);
        dif=difftime(clock(),start);
        JitterModeloRef[contModeloRef]=50 - dif/1000.0;
        usleep(50000 - dif);
        contModeloRef++;
    }
}
//Bloco Controle
void* Controle(void*args)
{
    clock_t start;
    double dif;
    while(t<=TempMax)
    {
        start=clock();
        sem_wait(&ConsomeY);
        sem_wait(&ConsomeYm);
        sem_wait(&ConsomeYmLinha);
        sem_wait(&ProduzV);
            bufferV=ControleBloco(bufferYmLinha, bufferYm, bufferY);
        sem_post(&ProduzYm);
        sem_post(&ProduzYmLinha);
        sem_post(&ProduzY);
        sem_post(&ConsomeV);
        dif=difftime(clock(),start);
        JitterControle[contControle]=50-dif/1000.0;
        usleep(50000-dif);
        contControle++;
    }
}
//Bloco Linearização
void* Linear(void*args)
{
    clock_t start;
    double dif;
    while(t<=TempMax)
    {
        start=clock();
        sem_wait(&ConsomeX);
        sem_wait(&ConsomeV);
        sem_wait(&ProduzU);
            bufferU=Linearizacao(bufferX, bufferV, R);
        sem_post(&ProduzX);
        sem_post(&ProduzV);
        sem_post(&ConsomeU);
        dif= difftime(clock(),start);
        JitterLinearizacao[contLinearizacao]=40 -dif/1000.0;
        usleep(40000-dif);
        contLinearizacao++;
    }
}
//Bloco Robo
void* Robo(void*args)
{
    clock_t start;
    double dif;
    while(t<=TempMax)
    {
        start=clock();
        sem_wait(&ConsomeU);
        sem_wait(&ProduzX);
        sem_wait(&ProduzY);
            printf("%.2lf, %lf, %lf, %lf\n", t-0.12 ,bufferX->matrix[0][0] , bufferX->matrix[1][0], bufferX->matrix[2][0]);
            auxBuffer2=XtLinha;
            XtLinha=RoboXtLinha(bufferX, bufferU);
            bufferX=RoboXt(XtLinha, auxBuffer, t);
            bufferY=RoboYt(bufferX, R);
        sem_post(&ProduzU);
        sem_post(&ConsomeX);
        sem_post(&ConsomeY);
        dif=difftime(clock(),start);
        JitterRobo[contRobo]=30 - dif/1000.0;
        usleep(30000-dif);
        contRobo++;
    }

}

void estatistcs(){
    for(int i = 0; i<contRef120; i++)
    {
        printf("%lf\n", JitterControle[i]);
    }
}

void main(){
    //Iniciando semaphoros produtores
    sem_init(&ProduzRef, 0,  1);
    sem_init(&ProduzU, 0,  1);
    sem_init(&ProduzV, 0,  1);
    sem_init(&ProduzX, 0,  0);
    sem_init(&ProduzY, 0,  0);
    sem_init(&ProduzYm, 0,  1);
    sem_init(&ProduzYmLinha, 0,  1);

    //Iniciando semaphoros Consumidores
    sem_init(&ConsomeRef, 0,  0);
    sem_init(&ConsomeU, 0,  0);
    sem_init(&ConsomeV, 0,  0);
    sem_init(&ConsomeX, 0,  1);
    sem_init(&ConsomeY, 0,  1);
    sem_init(&ConsomeYm, 0,  0);
    sem_init(&ConsomeYmLinha, 0,  0);

    //iniciando as Matrixes do Buffer que serão responsaveis por comunicar os blocos
    double aux[11] = {0,0,0,0,0,0,0,0,0,0,0};
    bufferV = matrix_createMatrix("V",2,1);
    bufferU = matrix_createMatrix("U",2,1);
    bufferY = matrix_createMatrix("Y",2,1);
    bufferX = matrix_createMatrix("X",3,1);
    bufferRef = matrix_createMatrix("Ref",2,1);
    bufferYm = matrix_createMatrix("Ym",2,1);
    bufferYmLinha = matrix_createMatrix("YmL",2,1);
    XtLinha = matrix_createMatrix("XtL",3 , 1);
    matrix_putValues(bufferY,aux);
    matrix_putValues(bufferX,aux);
    matrix_putValues(bufferU,aux);
    matrix_putValues(bufferV,aux);
    matrix_putValues(bufferYm,aux);
    matrix_putValues(bufferYmLinha,aux);
    matrix_putValues(bufferRef,aux);
    matrix_putValues(XtLinha, aux);


    //Nomeando as Threads
    pthread_t TRef120, TModeloRef, TControle, TLinearizacao, TRobo;

    //Criando as Threads
    pthread_create(&TRef120, NULL, Ref120, NULL);
    pthread_create(&TModeloRef, NULL, ModeloRef, NULL);
    pthread_create(&TControle, NULL, Controle, NULL);
    pthread_create(&TLinearizacao, NULL, Linear, NULL); 
    pthread_create(&TRobo, NULL, Robo, NULL);

    //Finalizando as Threads
    pthread_join(TRef120, NULL);
    pthread_join(TModeloRef, NULL);
    pthread_join(TControle, NULL);
    pthread_join(TLinearizacao, NULL);
    pthread_join(TRobo, NULL);


    int countFullTime[5]={contRef120, contModeloRef, contControle, contLinearizacao, contRobo};

    Statistics_Calculing(JitterRef120, JitterModeloRef
     ,JitterControle, JitterLinearizacao, JitterRobo, countFullTime);
}