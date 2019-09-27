#include "stdio.h"
#include "stdlib.h"
#include "sum.h"
#include "difference.h"

void verifiyTypeOfArgv(int *ok1, int *ok2, int teste1,
            int teste2, char *argv1, char *argv2, int argc1) {

    char *zero = "0";
    
    if (!teste1) { 
        if (!(strcmp(argv1, zero)))
            (*ok1) = 1; /* é um inteiro zero, logo continua ok */
        else
            (*ok1) = 0; /* não é um inteiro */
    }

    if (!teste2) {
        if (!(strcmp(argv2, zero)))
            (*ok2) = 1;
        else
            (*ok2) = 0;
    }
}

int main(int argc, char *argv[]) {

    int ok1 = 1; /* inicia tudo ok */
    int ok2 = 1;

    if (argc == 3) {  

        int teste1 = atoi(argv[1]);
        int teste2 = atoi(argv[2]);
     
        verifiyTypeOfArgv(&ok1, &ok2, teste1, teste2,
            argv[1], argv[2], argc);

        if (ok1 && ok2) {
            sumArgv(argv[1], argv[2]);
            differenceArgv(argv[1], argv[2]);
        } else {
            printf("falhou\n");
        } 
    } else {
        printf("falhou\n");
    }
}