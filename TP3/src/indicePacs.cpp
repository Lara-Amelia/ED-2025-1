#include <iomanip>
#include <sstream>
#include "indicePacs.hpp"

//insere um novo pacote na árvore do índice
void indicePacs::registraPacote(int idPac, int tempoReg)
{
    arv.insere(idPac, tempoReg);
}

//verifica se um pacote com um certo id existe no índice
bool indicePacs::existePac(int idPac)
{
    return arv.existe(idPac);
}

//busca um certo pacote no índice
int indicePacs::tempoRegistro(int idPac)
{
    return arv.busca(idPac);
}

//gera a chave que define qual será o nó inicial para busca 
//no índice pacoteTempo
std::string indicePacs::geraChaveParaBuscaTempo(int idPacote, int tipo) 
{
        Node<int, int>* node = arv.buscaNode(idPacote);
        if (!node) return "";

        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << node->chave;
        oss << std::setw(7) << std::setfill('0') << node->valor;
        oss << tipo;
        return oss.str();
}