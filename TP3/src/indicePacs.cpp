#include <iomanip>
#include <sstream>
#include "indicePacs.hpp"

void indicePacs::registraPacote(int idPac, int tempoReg)
{
    arv.insere(idPac, tempoReg);
}

bool indicePacs::existePac(int idPac)
{
    return arv.existe(idPac);
}

int indicePacs::tempoRegistro(int idPac)
{
    return arv.busca(idPac);
}

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