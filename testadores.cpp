#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
using namespace std;

void teste1(Lista *dados) {
    for (int i=0; i<3; i++) {
        char codCliente[20];
        printf("\nDigite o código do cliente: ");
        scanf("%19s", &codCliente);

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

void teste2() {
    return;
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
        // teste2();
    } else if (opcao == 3) {
        // teste2();
    }else { 
        printf("Erro: p número deve estar entre 1-3");
        return 1;
    }

    return 0;
}

