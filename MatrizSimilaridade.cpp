#include <stdio.h>
#include "ListaCompras.h"
#include <stdlib.h>
#include <algorithm>
#include "MatrizSimilaridade.h"
using namespace std;

int CalcularSimilaridade(MatrizSimilaridade *matriz, Lista *listaCompras) {
    int numClientes = listaCompras->clientes.size();
    int numProdutos = listaCompras-> produtos.size();

    int *A = (int*) malloc (numClientes *numProdutos*sizeof(int));
    int *B = (int*) malloc (numProdutos *numClientes*sizeof(int));
    int *C = (int*) malloc (numClientes *numClientes*sizeof(int));
}
   