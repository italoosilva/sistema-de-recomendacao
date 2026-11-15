#ifndef  SIMILARIDADE_H
#define SIMILARIDADE_H

#include <vector>
#include <string>
#include <iostream>
#include "ListaCompras.h"

typedef struct {
    std::vector<std::string> clientes;
    std::vector<std::string> produtos;
    std::vector<std::vector<double>> Similaridade;
} MatrizSimilaridade;

int CalcularSimilaridade(MatrizSimilaridade &matriz, Lista &listaCompras);

double SimilaridadeClientes(MatrizSimilaridade &matriz, Lista &listaCompras, std::string cliente1, std::string cliente2);

int ClienteMaisSimilar(MatrizSimilaridade &matriz, int cliente);
#endif
