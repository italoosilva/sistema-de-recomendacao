#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "ListaCompras.h"
#include "MatrizSimilaridade.h"
#include "CSR.h"

typedef struct {
    int produto;
    double nota;
} Produto;

bool ordenarPorNota(const Produto &a, const Produto &b);
std::vector<Produto> recomendarProdutos(MatrizSimilaridade *matriz, Lista *dados,int cliente, int k);
std::vector<Produto> recomendarProdutosCSR(matrizCSR *S, Lista *dados, int cliente, int k);

#endif