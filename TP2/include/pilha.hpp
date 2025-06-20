#ifndef PILHA_HPP
#define PILHA_HPP
#include "pacote.hpp"

class tipoNo
{
    private:
    Pacote* item;
    tipoNo* prox;

    public:
    tipoNo(Pacote* inserido);
    tipoNo();

    friend class Pilha;
};

class Pilha
{
    private:
    int tamanho;
    tipoNo* head;

    public:
    Pilha(); //construtor default
    ~Pilha(); //detrutor
    int getTam();
    bool Vazia();
    void Empilha(Pacote* item);
    Pacote* Desempilha();
    void Limpa();
};

#endif