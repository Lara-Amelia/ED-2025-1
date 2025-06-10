#ifndef PILHA_HPP
#define PILHA_HPP
#include "pacote.hpp"

//a pilha utilizada é sempre de pacotes. Logo, suas células são do TAD Pacote
//talvez possamos fazer a pilha recebendo apenas o identificador do pacote
//(é menos custoso já que não movimentamos o registro em si, mas tem de checar se sequer há identificador)

//talvez classe
class tipoNo
{
    private:
    Pacote item;
    tipoNo* prox;

    public:
    tipoNo(Pacote inserido);
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
    void Empilha(Pacote item);
    Pacote Desempilha();
    void Limpa();
};

#endif