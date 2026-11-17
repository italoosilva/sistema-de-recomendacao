#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
#include "MatrizSimilaridade.h"
#include "recomendacao.h"
using namespace std;

void teste1(Lista *dados) {
    for (int i=0; i<3; i++) {
        char codCliente[20];
        printf("\nDigite o código do cliente: ");
        scanf("%19s", codCliente);

        int ind_cliente = gerarLista(dados, codCliente);

        if (ind_cliente < 0) {
            continue;
        }
        
        cout << "\n" << "Produtos comprados pelo cliente " << codCliente << "\n";
        for (int p : dados->comprasCliente[ind_cliente]) {
            cout << "- " << dados->produtos[p] << "\n";
        }
    }
}

void teste2(Lista *dados) {
    MatrizSimilaridade matriz;
    if (CalcularSimilaridade(&matriz, dados) == 0) {
        printf("Erro ao calcular a similaridade.\n");
        return;
    
    }
    for (int i=0; i<3; i++) {
        char codCliente[20];
        printf("\nDigite o código do cliente: ");
        scanf("%19s", codCliente);

        int ind_cliente = gerarLista(dados, codCliente);

        if (ind_cliente < 0) {
            continue;
        }
        int ind_similar = ClienteSimilar(&matriz, ind_cliente);

        if (ind_similar < 0) {
            cout << "Nenhum cliente similar\n";
            continue;
        }
        cout<< "Cliente mais similar: " << dados->clientes[ind_similar] << "\n";
        cout << SimilaridadeClientes(&matriz, ind_cliente, ind_similar) << "\n";
    
    }
    free(matriz.Similaridade);
    return;
}

void teste3(Lista *dados) {
    MatrizSimilaridade matriz;
    if (CalcularSimilaridade(&matriz, dados) == 0) {
        printf("Erro ao calcular a similaridade.\n");
        return;
    }

    for (int i=0; i<3; i++) {
        char codCliente[20];
        printf("\nDigite o código do cliente: ");
        scanf("%19s", codCliente);

        int ind_cliente = gerarLista(dados, codCliente);

        if (ind_cliente < 0) {
            continue;
        }

        int k=10;
        vector<Produto> ranking = recomendarProdutos(&matriz, dados, ind_cliente, k);

        cout << "Lista de produtos recomendados para o cliente " << codCliente << "\n";
        int cont = 1;
        for (Produto p : ranking) {
            cout << cont << ". " << dados->produtos[p.produto] << "\n";
            cont++;
        }
    }
    free(matriz.Similaridade);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo.csv> <número do testador (1-3)> \n", argv[0]);
        return 1;
    }

    Lista dados;
    organizarDados(argv[1], &dados);
    int opcao = atoi(argv[2]);

    if ( opcao == 1) {
        teste1(&dados);
    } else if (opcao == 2) {
        teste2(&dados);
    } else if (opcao == 3) {
        teste3(&dados);
    }else { 
        printf("Erro: p número deve estar entre 1-3");
        return 1;
    }

    return 0;
}

