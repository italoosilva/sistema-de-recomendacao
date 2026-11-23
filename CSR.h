#ifndef CSR_H
#define CSR_H

#include <vector>
#include "ListaCompras.h"

typedef struct {
    std::vector<double> values;
    std::vector<int> col_index;
    std::vector<int> row_ptr;
} matrizCSR;

void criaComprasCSR(Lista *dados, matrizCSR *A);
void criaInterseccaoCSR(matrizCSR *A, matrizCSR *C);
void criaSimilaridadeCSR(matrizCSR *A, matrizCSR *C, matrizCSR *S);

#endif  