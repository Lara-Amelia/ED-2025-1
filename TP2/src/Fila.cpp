#include "Fila.hpp"

TipoCelula::TipoCelula()
{
    item = -1;
    prox = nullptr;
}

Fila::Fila()
{
    tamanho = 0;
    frente = new TipoCelula;
    tras = frente;
}

Fila::~Fila()
{
    Limpa();
    delete frente;
}

void Fila::Enfileira(int item)
{
    TipoCelula* nova;

    nova = new TipoCelula();
    nova->item = item;
    tras->prox = nova;
    tras = nova;
    tamanho++;
}

int Fila::Desenfileira()
{
    TipoCelula* p;
    int aux;

    /*if(tamanho == 0)
        throw "fila está vazia!"
    */
    aux = frente->prox->item;
    p = frente;
    frente = frente->prox;
    delete p;
    tamanho--;
    return aux;
}

void Fila::Limpa()
{
    TipoCelula* p;

    p = frente->prox;
    while(p != nullptr)
    {
        frente->prox = p->prox;
        delete p;
        p = frente->prox;
    }
    tamanho = 0;
    tras = frente;
}

int Fila::getTamanho()
{
    return tamanho;
}

bool Fila::Vazia()
{
    return tamanho == 0;
}