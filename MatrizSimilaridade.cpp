#include <stdio.h>
#include <stdlib.h>
#include "MatrizSimilaridade.h"

using namespace std;

int CalcularSimilaridade(MatrizSimilaridade *matriz, Lista *listaCompras) {
    int numClientes = listaCompras->clientes.size();
    int numProdutos = listaCompras-> produtos.size();

    int *A = (int*) malloc (numClientes *numProdutos*sizeof(int));
    int *B = (int*) malloc (numProdutos *numClientes*sizeof(int));
    int *C = (int*) malloc (numClientes *numClientes*sizeof(int));
    matriz->numClientes = numClientes;
    matriz->Similaridade = (double*) malloc (numClientes * numClientes * sizeof(double));

if (A == NULL || B == NULL || C == NULL|| matriz->Similaridade == NULL) {
    perror("Error");
    return 0;
  
}


for (int i = 0; i < numClientes; i++) {
    for (int j = 0; j < numProdutos; j++) {
        A[i * numProdutos + j] = 0;
    }
}
for (int i = 0; i < numProdutos; i++) {
    for (int j = 0; j < numClientes; j++) {
        B[i * numClientes + j] = 0;
    }
}
for (int i = 0; i < numClientes; i++) {
    for (int p : listaCompras->comprasCliente[i]) {
        A[i * numProdutos + p] = 1;
    }
}
for (int i = 0; i < numClientes; i++) {
    for (int j = 0; j < numProdutos; j++) {
        B[j * numClientes + i] = A[i * numProdutos + j];
    }
}
for (int i = 0; i < numClientes; i++) {
    for (int j = 0; j < numClientes; j++) {
        C[i * numClientes + j] = 0;
        for (int k = 0; k < numProdutos; k++) {
            C[i * numClientes + j] += A[i * numProdutos + k] * B[k * numClientes + j];
        }
}
}
for (int i = 0; i < numClientes; i++) {
    for (int j = 0; j < numClientes; j++) {
        double produtosIguais = C[i * numClientes + j];
        double totalCompras = C[i *numClientes + i];
        if (totalCompras == 0) {
            matriz->Similaridade[i * numClientes + j] = 1.0;
        } else {
            matriz->Similaridade[i * numClientes + j] = 1.0 - (produtosIguais / totalCompras);
        }
    }
}
    free(A);
    free(B);
    free(C);
    return 1;
}
double SimilaridadeClientes(MatrizSimilaridade *matriz, int cliente1, int cliente2) {
 int n = matriz->numClientes;
 if (cliente1 < 0 ||  cliente1 >= n ||cliente2 < 0 ||  cliente2 >= n)  {
        
    return -1.0;
    }
    return matriz->Similaridade[cliente1 * n + cliente2];
}
int ClienteSimilar(MatrizSimilaridade *matriz, int cliente) {
    int n = matriz->numClientes;
    if (cliente < 0 || cliente >= n) {
        return -1;
    }
    int melhor=-1;
    double aux=0;
    double menor=1.0;
    for (int i = 0; i < n; i++) {
        if (i != cliente) {
            aux = SimilaridadeClientes(matriz, cliente, i);
            if (aux < menor) {
                menor = aux;
                melhor = i;
}
    
}
    }
    return melhor;
}