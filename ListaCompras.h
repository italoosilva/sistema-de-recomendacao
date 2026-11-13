#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <map>
#include <list>
#include <string>

typedef struct {
    std::vector<std::string> clientes;
    std::map<std::string,int> indices_clientes;
    
    std::vector<std::string> produtos;
    std::map<std::string,int> indices_produtos;

    std::vector<std::list<int>> comprasCliente;
} Lista;

int organizarDados(char *caminho, Lista *dados);
int gerarLista(Lista *dados, char *codCliente);

#endif