//Para a avl do índice pacote tempo, podemos utilizar como valor da árvore ponteiros para os eventos associados
//isso facilitará a impressão e armazenamento dos eventos obtidos via caminhamento in-order na árvore
#ifndef INDICEPACTEMPO_HPP
#define INDICEPACTEMPO_HPP

#include <sstream>
#include <iomanip>
#include <string>
#include "arvoreAVL.hpp"
#include "evento.hpp"

class indicePacTempo
{
    private:
    arvoreAVL<std::string, Evento*> arvPacTempo;
    std::string geraChave(int idPacote, int tempo, int tipo);

    public:
    void registraEvento(int idPacote, int tempo, int tipo, Evento* evento);
    Evento* buscaEvento(int idPacote, int tempo, int tipo);
    void eventosDoPacote(std::string chave, int idPac, int tempoLim, Evento** buffer, int& qtd);

    void inOrderPrint(Evento** eventos, int& index);
};

#endif