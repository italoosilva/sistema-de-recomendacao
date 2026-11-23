#include <vector>
#include <list>
#include <algorithm>
#include "recomendacao.h"
#include "ListaCompras.h"
#include "MatrizSimilaridade.h"

using namespace std;

bool ordenarPorNota(const Produto &a, const Produto &b) {
    return a.nota < b.nota;
}

vector<Produto> recomendarProdutos(MatrizSimilaridade *matriz, Lista *dados,int cliente, int k) {
    if (0 > cliente || cliente >= (int)dados->clientes.size()) {
        vector<Produto> v;
        return v;
    }

    vector<Produto> produtos;
    vector<double> notas(dados->produtos.size(), 1.0);
    list<int> &lista_cliente = dados->comprasCliente[cliente];

    for (int i=0; i < matriz->numClientes; i++) {
        double similar = SimilaridadeClientes(matriz, cliente, i);
        if (cliente == i || similar >= 1) {
            continue;
        }

        list<int> &lista = dados->comprasCliente[i];

        for (int p : lista) {
            if (find(lista_cliente.begin(), lista_cliente.end(), p) != lista_cliente.end()) {
                continue;
            }

            notas[p] *= similar;
        }
    }

    for (int j = 0; j < (int)notas.size(); j++) {
        if (notas[j] < 1) {
            produtos.push_back({j, notas[j]});
        }
    }

    sort(produtos.begin(), produtos.end(), ordenarPorNota);

    while ((int)produtos.size() > k) {
    produtos.pop_back();
    }
    
    return produtos;
}


vector<Produto> recomendarProdutosCSR(matrizCSR *S, Lista *dados, int cliente, int k) {
    if (0 > cliente || cliente >= (int)dados->clientes.size()) {
        vector<Produto> v;
        return v;
    }

    vector<Produto> produtos;
    vector<double> notas(dados->produtos.size(), 1.0);
    list<int> &lista_cliente = dados->comprasCliente[cliente];

    for (int i = S->row_ptr[cliente]; i < S->row_ptr[cliente + 1]; i++) {
        int vizinho = S->col_index[i];   
        double similar = S->values[i];   

        if (cliente == vizinho || similar >= 1) {
            continue;
        }

        list<int> &lista = dados->comprasCliente[vizinho];

        for (int p : lista) {
            if (find(lista_cliente.begin(), lista_cliente.end(), p) != lista_cliente.end()) {
                continue;
            }
            
            notas[p] *= similar;
        }
    }

    for (int j = 0; j < (int)notas.size(); j++) {
        if (notas[j] < 1) {
            produtos.push_back({j, notas[j]});
        }
    }

    sort(produtos.begin(), produtos.end(), ordenarPorNota);

    while ((int)produtos.size() > k) {
        produtos.pop_back();
    }
    
    return produtos;
}