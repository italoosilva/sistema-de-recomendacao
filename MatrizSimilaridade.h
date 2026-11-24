#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H


#include <stdlib.h>
#include "ListaCompras.h"
#include "CSR.h"


typedef struct {
    int numClientes;
    double *Similaridade;
    matrizCSR S;
    int algoritmo;
} MatrizSimilaridade;

int CalcularSimilaridade(MatrizSimilaridade *matriz, Lista *ListaCompras, int algoritimo);

int ClienteSimilar(MatrizSimilaridade *matriz, int cliente);

double SimilaridadeClientes(MatrizSimilaridade *matriz, int cliente1, int cliente2);




#endif
