#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "ListaCompras.h"
#include "MatrizSimilaridade.h"

typedef struct {
    int produto;
    double nota;
} Produto;

std::vector<Produto> recomendarProdutos(MatrizSimilaridade *matriz, Lista *dados,int cliente, int k);

#endif