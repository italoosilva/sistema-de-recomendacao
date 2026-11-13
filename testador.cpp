#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
using namespace std;

void teste(Lista *dados, char *codCliente) {
    int ind_cliente = gerarLista(dados, codCliente);

    if (ind_cliente < 0) { 
        printf("\nCliente %s nao encontrado. \n", codCliente);
        return;
    }

    cout << "\n" << "Produtos comprados pelo cliente " << codCliente << "\n";
    for (int p : dados->comprasCliente[ind_cliente]) {
        cout << "- " << dados->produtos[p] << "\n";
    }
}

int main() {
    Lista dados;

    char codigo1[] = "04536701";
    char codigo2[] = "ZZZZZZZZ";
    char codigo3[] = "11360801";

    char caminho[] = "dados/dados_venda_cluster_17.csv";
    organizarDados(caminho, &dados);

    teste(&dados, codigo1);
    teste(&dados, codigo2);
    teste(&dados, codigo3); 
    
    return 0;
}