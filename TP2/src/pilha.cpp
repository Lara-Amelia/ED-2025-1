#include "pilha.hpp"
#include "pacote.hpp"
#include <exception>
#include <string>
#include <stdexcept>

//métodos relacionados aos nós da pilha ///////////////////////////////////////////////////////////////////////////
tipoNo::tipoNo(Pacote* inserido)
{
    item = inserido;
    prox = NULL;
}

tipoNo::tipoNo()
{
    item = nullptr;
    prox = NULL;
}

//métodos da pilha em si////////////////////////////////////////////////////////////////////////////////////////
Pilha::Pilha()
{
    head = NULL;
    tamanho = 0;
}

Pilha::~Pilha()
{
    Limpa();
}

int Pilha::getTam()
{
    return tamanho;
}

void Pilha::Empilha(Pacote* item)
{
    tipoNo *nova;

    nova = new tipoNo(item);
    nova->item = item;
    nova->prox = head;
    head = nova;
    tamanho++;
}

Pacote* Pilha::Desempilha()
{
    Pacote* aux;
    tipoNo *p;

    if(tamanho == 0)
       throw std::runtime_error("ERRO: a pilha está vazia");
    
    aux = head->item;
    p = head;
    head = head->prox;
    delete p;
    tamanho--;

    return aux; //retorna o item desempilhado
}

//checa se a pilha está ou não vazia
bool Pilha::Vazia()
{
    return tamanho == 0;    
}

//faz a limpeza da pilha
void Pilha::Limpa()
{
    while(!Vazia())
        Desempilha();
}