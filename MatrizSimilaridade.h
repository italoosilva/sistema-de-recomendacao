#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H


#include <stdlib.h>
#include "ListaCompras.h"

typedef struct {
    int numClientes;
    double *Similaridade;
} MatrizSimilaridade;

int CalcularSimilaridade(MatrizSimilaridade *matriz, Lista *ListaCompras);



int ClienteSimilar(MatrizSimilaridade *matriz, int cliente);
#endif
