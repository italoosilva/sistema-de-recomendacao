#include <stdio.h>
#include <stdlib.h>
#include "MatrizSimilaridade.h"

using namespace std;

int CalcularSimilaridade(MatrizSimilaridade *matriz, Lista *listaCompras, int algoritmo) {
    int numClientes = listaCompras->clientes.size();
    int numProdutos = listaCompras-> produtos.size();

    matriz->numClientes = numClientes;
    matriz->algoritmo = algoritmo;

    if (algoritmo == 2) {
        matrizCSR csrA;
        matrizCSR csrC;

        matriz->Similaridade = NULL;
        matriz->S = matrizCSR();
        matriz->algoritmo = 2;

        criaComprasCSR(listaCompras, &csrA);
        criaInterseccaoCSR(&csrA, &csrC);
        criaSimilaridadeCSR(&csrA, &csrC, &matriz->S);
        return 1;
    }

    int *A = (int*) malloc (numClientes *numProdutos*sizeof(int));
    int *B = NULL;
    if (algoritmo ==0){
        B = (int*) malloc (numProdutos *numClientes*sizeof(int));
    }
    int *C = (int*) malloc (numClientes *numClientes*sizeof(int));
    
    matriz->Similaridade = (double*) malloc (numClientes * numClientes * sizeof(double));

if (A == NULL || (algoritmo == 0 && B == NULL) || C == NULL|| matriz->Similaridade == NULL) {
    perror("Error");
    return 0;
  
}


for (int i = 0; i < numClientes; i++) {
    for (int j = 0; j < numProdutos; j++) {
        A[i * numProdutos + j] = 0;
    }
}
if (algoritmo == 0) {
    for (int i = 0; i < numProdutos; i++) {
        for (int j = 0; j < numClientes; j++) {
            B[i * numClientes + j] = 0;
        }
    }
}
for (int i = 0; i < numClientes; i++) {
    for (int p : listaCompras->comprasCliente[i]) {
        A[i * numProdutos + p] = 1;
    }
}
if (algoritmo == 0) {
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
} else {
    for (int i = 0; i < numClientes; i++) {
        for (int j = i; j < numClientes; j++) {
            int soma = 0;
            for (int k = 0; k < numProdutos; k++) {
                soma += A[i * numProdutos + k] * A[j * numProdutos + k];
            }
            C[i * numClientes + j] = soma;
            C[j * numClientes + i] = soma;
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

    if (matriz->algoritmo == 2) {
        if (cliente1 == cliente2) {
            return 0.0;
        }

        for (int i = matriz->S.row_ptr[cliente1]; i < matriz->S.row_ptr[cliente1 + 1]; i++) {
            if (matriz->S.col_index[i] == cliente2) {
                return matriz->S.values[i];
            }
        }
        
        return 1.0;
    }

    return matriz->Similaridade[cliente1 * n + cliente2];
}

int ClienteSimilar(MatrizSimilaridade *matriz, int cliente) {
    int n = matriz->numClientes;
    if (cliente < 0 || cliente >= n) {
        return -1;
    }
    int melhor=-1;
    double menor=1.0;

    if (matriz->algoritmo == 2) {
        for (int i = matriz->S.row_ptr[cliente]; i < matriz->S.row_ptr[cliente + 1]; i++) {
            if (matriz->S.values[i] < menor) {
                menor = matriz->S.values[i];
                melhor = matriz->S.col_index[i];
            }
        }
        return melhor;
    }

    double aux=0;
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