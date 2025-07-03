#ifndef INDICEPACS_HPP
#define INDICEPACS_HPP

#include "evento.hpp"
#include "arvoreAVL.hpp"
#include <string>

class indicePacs
{
    private: 
    arvoreAVL<int, int> arv;

    public:
    void registraPacote(int idPac, int tempoReg);
    bool existePac(int idPac);
    int tempoRegistro(int idPac);
    std::string geraChaveParaBuscaTempo(int idPacote);
};

#endif