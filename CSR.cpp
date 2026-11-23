#include "CSR.h"
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

void criaComprasCSR(Lista *dados, matrizCSR *A) {
    int cont = 0;
    A->row_ptr.push_back(cont);

    for (int i; i < dados->clientes.size(); i++) {
        vector<int> comprasClieteOrdenada;

        for (int x : dados->comprasCliente[i]) {
            comprasClieteOrdenada.push_back(x);
        }

        sort(comprasClieteOrdenada.begin(), comprasClieteOrdenada.end());

        for (int p : comprasClieteOrdenada) {
            cont++;

            A->col_index.push_back(p);
            A->values.push_back(1);
        }
        A->row_ptr.push_back(cont);
    }
    return;
}

void criaInterseccaoCSR(matrizCSR *A, matrizCSR *C) {
    int num_clientes = A->row_ptr.size() - 1;

    C->row_ptr.push_back(0);
    int cont = 0;

    for (int i=0; i < num_clientes; i++) {
        for (int j=0; j < num_clientes; j++) {

            int soma = 0;
            
            int inicioLinhaI = A->row_ptr[i];
            int fimLinhaI = A->row_ptr[i+1];
            int inicioLinhaJ = A->row_ptr[j];
            int fimLinhaJ = A->row_ptr[j+1];

            while (inicioLinhaI < fimLinhaI && inicioLinhaJ < fimLinhaJ) {
                if (A->col_index[inicioLinhaI] == A->col_index[inicioLinhaJ]) {
                    soma += A->values[inicioLinhaI] * A->values[inicioLinhaJ];
                    inicioLinhaI++;
                    inicioLinhaJ++;
                } else if (A->col_index[inicioLinhaI] < A->col_index[inicioLinhaJ]) {
                    inicioLinhaI++;
                } else {
                    inicioLinhaJ++;
                }
            }
            
            if (soma != 0) {
                C->values.push_back(soma);
                C->col_index.push_back(j);
                cont++;
            }
        }
        C->row_ptr.push_back(cont);
    }
    return;
}

void criaSimilaridadeCSR()

