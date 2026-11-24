#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
#include "MatrizSimilaridade.h"
#include <ctime>
#include "recomendacao.h"
#include "CSR.h"
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
int Primeiros(Lista *dados, Lista *listaReduzida, int numClientes) {
    for (int i = 0; i < numClientes; i++) {
        listaReduzida->clientes.push_back(dados->clientes[i]);
        listaReduzida->comprasCliente.push_back(dados->comprasCliente[i]);
    }
    listaReduzida->produtos = dados->produtos;
    return 1;
}
void teste4(Lista *dados) {
    int tamanhos[4] = {100, 200, 400, 800};
    int total = dados->clientes.size();

    printf("\n%10s %14s %14s\n", "clientes", "padrao (s)", "adaptado (s)");
    for (int t = 0; t < 4; t++) {
        int n = tamanhos[t];
        if (n > total) {
            n = total;
        }

        Lista listaReduzida;
        Primeiros(dados, &listaReduzida, n);
        MatrizSimilaridade matrizPadrao;
        MatrizSimilaridade matrizAdaptada;

        clock_t inicio = clock();
        CalcularSimilaridade(&matrizPadrao, &listaReduzida, 0);
        clock_t fim = clock();
        double tempoPadrao = double(fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        CalcularSimilaridade(&matrizAdaptada, &listaReduzida, 1);
        fim = clock();
        double tempoAdaptado = double(fim - inicio) / CLOCKS_PER_SEC;

        int diferentes = 0;
        for (int i = 0; i < n * n; i++) {
            if (matrizPadrao.Similaridade[i] != matrizAdaptada.Similaridade[i]) {
                diferentes++;
            }
        }
        printf("%10d %14.4f %14.4f   (celulas diferentes: %d)\n", n, tempoPadrao, tempoAdaptado, diferentes);

        free(matrizPadrao.Similaridade);
        free(matrizAdaptada.Similaridade);
        if (n == total) {
            break;
        }
    }
}
void teste5(Lista*dados){
    int tamanhos[4] = {250, 500, 1000, 2000};
    int total = dados ->clientes.size();

       printf("\n%8s %11s %11s %15s %15s\n", "clientes", "padrao (s)", "CSR (s)", "padrao (bytes)", "CSR (bytes)");
    for (int t = 0; t < 4; t++) {
        int n = tamanhos[t];
        if (n > total) {
            n = total;
        }
        Lista listaReduzida;
        Primeiros(dados, &listaReduzida, n);
        MatrizSimilaridade matrizPadrao;
        clock_t inicio = clock();
        CalcularSimilaridade(&matrizPadrao, &listaReduzida, 0);
        clock_t fim = clock();
        double tempoPadrao = double(fim - inicio) / CLOCKS_PER_SEC;
        matrizCSR A;
        matrizCSR C;
        matrizCSR S;
        inicio = clock();
        criaComprasCSR(&listaReduzida, &A);
        criaInterseccaoCSR(&A, &C);
        criaSimilaridadeCSR(&A, &C, &S);
        fim = clock();
        double tempoCSR = double(fim - inicio) / CLOCKS_PER_SEC;
        double memoriaPadrao = (double)n * n * sizeof(double);
                double memoriaCSR = S.values.size() * sizeof(double);
        memoriaCSR += S.col_index.size() * sizeof(int);
        memoriaCSR += S.row_ptr.size() * sizeof(int);

               printf("%8d %11.4f %11.4f %15.0f %15.0f\n", n, tempoPadrao, tempoCSR, memoriaPadrao, memoriaCSR);
        free(matrizPadrao.Similaridade);
        if (n == total) {
            break;
        }

}
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo.csv> <número do testador (1-5)> \n", argv[0]);
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
    }else if (opcao == 5) {
        teste5(&dados);
    }
     else {
        printf("Erro: o número deve estar entre 1-5\n");
        return 1;
    }
    return 0;
}
