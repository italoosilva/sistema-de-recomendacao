#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "ListaCompras.h"
using namespace std;



int organizarDados(char *caminho, Lista *dados) {
    char cod_cliente[20];
    char cod_produto[20];
    char nome_produto[200];

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %*[^,], %19[^,],%19[^,],%199[^\r\n]",
                  cod_cliente, cod_produto, nome_produto) == 3) {

        if (dados->indices_clientes.find(cod_cliente) == dados->indices_clientes.end()) {
            dados->indices_clientes[cod_cliente] = dados->clientes.size();
            dados->clientes.push_back(cod_cliente);
            dados->comprasCliente.push_back(list<int>());
        }

        if (dados->indices_produtos.find(cod_produto) == dados->indices_produtos.end()) {
            dados->indices_produtos[cod_produto] = dados->produtos.size();
            dados->produtos.push_back(nome_produto);
        }

        int ind_cliente = dados->indices_clientes[cod_cliente];
        int ind_produto = dados->indices_produtos[cod_produto];
        list<int> &lista = dados->comprasCliente[ind_cliente];

        if (std::find(lista.begin(), lista.end(), ind_produto) == lista.end()) {
            lista.push_back(ind_produto);
        }
    }

    fclose(arquivo);
    return 1;

}

int gerarLista(Lista *dados, char *codCliente) {
    if (dados->indices_clientes.find(codCliente) == dados->indices_clientes.end()) {
        printf("\nCliente %s nao encontrado. \n", codCliente);
        return -1;
    }
    
    return dados->indices_clientes[codCliente];;
}
