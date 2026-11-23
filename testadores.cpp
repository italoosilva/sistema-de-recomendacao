#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
#include "MatrizSimilaridade.h"
#include <ctime>
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
    if (CalcularSimilaridade(&matriz, dados, 0) == 0) {
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
    if (CalcularSimilaridade(&matriz, dados, 0) == 0) {
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
int Primeiros(Lista *dados, Lista *sub, int k) {
    for (int i = 0; i < k; i++) {
        sub->clientes.push_back(dados->clientes[i]);
        sub->comprasCliente.push_back(dados->comprasCliente[i]);
    }
    sub->produtos = dados->produtos;
    return 1;
}
void teste4(Lista *dados) {
    int tamanhos[4] = {100, 200, 400, 800};
    int total = dados->clientes.size();

    printf("\n%10s %14s %14s\n", "clientes", "padrao (s)", "adaptado (s)");
    for (int t = 0; t < 4; t++) {
        int k = tamanhos[t];
        if (k > total) {
            k = total;
        }

        Lista sub;
        Primeiros(dados, &sub, k);
        MatrizSimilaridade m0;
        MatrizSimilaridade m1;

        clock_t inicio = clock();
        int ok0 = CalcularSimilaridade(&m0, &sub, 0);
        double tempo0 = double(clock() - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        int ok1 = CalcularSimilaridade(&m1, &sub, 1);
        double tempo1 = double(clock() - inicio) / CLOCKS_PER_SEC;

        if (ok0 == 0 || ok1 == 0) {
            printf("Erro ao calcular a similaridade.\n");
            return;
        }

        int diferentes = 0;
        for (int i = 0; i < k * k; i++) {
            if (m0.Similaridade[i] != m1.Similaridade[i]) {
                diferentes++;
            }
        }
        printf("%10d %14.4f %14.4f   (celulas diferentes: %d)\n", k, tempo0, tempo1, diferentes);

        free(m0.Similaridade);
        free(m1.Similaridade);
        if (k == total) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo.csv> <número do testador (1-4)> \n", argv[0]);
        return 1;
    }

    Lista dados;
    organizarDados(argv[1], &dados);
    int opcao = atoi(argv[2]);
        if (opcao == 1) {
        teste1(&dados);
    } else if (opcao == 2) {
        teste2(&dados);

        } else if (opcao == 3) {
        teste3(&dados);
    } else if (opcao == 4) {
        teste4(&dados);
    } else {
        printf("Erro: o número deve estar entre 1-4\n");
        return 1;
    }
}
