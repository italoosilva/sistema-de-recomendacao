#include <stdio.h>
#include <algorithm>
#include "MatrizSimilaridade.h"
using namespace std;

int CalcularSimilaridade(MatrizSimilaridade &matriz, Lista &listaCompras) {
    matriz.clientes = listaCompras.clientes;
    matriz.produtos = listaCompras.produtos;
    int numClientes = listaCompras.clientes.size();
    int numProdutos = listaCompras.produtos.size();
    matriz.Similaridade.resize(numClientes, vector<double>(numClientes, 0.0));

    vector<vector<int>> A;
    for (int i = 0; i < numClientes; ++i) {
        vector<int> linha;
        for (int j = 0; j < numProdutos; ++j) {
            linha.push_back(0);
        }
        A.push_back(linha);
    }
    vector<vector<int>> B;
    for (int i = 0; i < numProdutos; ++i) {
        vector<int> linha;
        for (int j = 0; j < numClientes; ++j) {
            linha.push_back(0);
        }
        B.push_back(linha);
    }
     vector<vector<int>> C;
    for (int i = 0; i < numClientes; ++i) {
        vector<int> linha;
        for (int j = 0; j < numClientes; ++j) {
            linha.push_back(0);
        }
        C.push_back(linha);
    }

    for (int i = 0; i < numClientes; ++i) {
        for (int j = i + 1; j < numClientes; ++j) {
            double sim = SimilaridadeClientes(matriz, listaCompras, listaCompras.clientes[i], listaCompras.clientes[j]);
            matriz.Similaridade[i][j] = sim;
            matriz.Similaridade[j][i] = sim;
        }
    }
    return 1;
}