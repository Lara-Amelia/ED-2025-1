#include "Fila.hpp"
#include <exception>
#include <stdexcept>

//implementação do TAD Fila utilizado na definição de rotas com Busca em Largura

//métodos relacionados ao nó da fila////////////////////////////////////////////////////////////////////////
TipoCelula::TipoCelula()
{
    item = -1;
    prox = nullptr;
}

//métodos da classe Fila em si//////////////////////////////////////////////////////////////////////////////
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
    if (Vazia() || (frente->prox == nullptr)) // Or if (frente->prox == nullptr)
    {
        throw std::out_of_range("Fila vazia: Nao eh possivel desenfileirar");
    }

    TipoCelula* p = frente->prox; // nó que será removido (o primeiro elemento real)
    int aux = p->item;

    frente->prox = p->prox; // pula o nó removido

    if (tras == p) // se o nó removido era o último, atualizar o ponteiro tras para dummy
        tras = frente;

    delete p; // deleta o nó removido
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