#include "include/ListaAdjacencia.hpp"
#include "include/ListaEncadeada.hpp"
#include <iostream>

Node::Node()
{
    nroVertice = -1;
    prox = nullptr;
}

Node::Node(int valor)
{
    nroVertice = valor;
    prox = nullptr;
}

ListaEncadeada::ListaEncadeada()
{
    tamanho = 0;
    head = new Node();
    tail = head;
}

ListaEncadeada::~ListaEncadeada()
{
    Limpa();
    delete head;
}

Node* ListaEncadeada::PosicionaAntes(int pos)
{
    Node *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception
    p = head;
    for(i = 0; i < pos; i++)
    {
        p = p->prox;
    }
    return p;
}

Node* ListaEncadeada::PosicionaEm(int pos)
{
    Node *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception
    p = head;
    for(i = 0; i <= pos; i++)
    {
        p = p->prox;
    }
    return p;
}

void ListaEncadeada::setVert(int pos, int novoVertice)
{
    Node *p;
    p = PosicionaEm(pos);
    p->nroVertice = novoVertice; 
}

int ListaEncadeada::getVert(int pos)
{
    Node *p;
    p = PosicionaEm(pos);
    return p->nroVertice;
}

void ListaEncadeada::inserePosicao(int item, int pos)
{
    Node *p, *novo;
    p = PosicionaAntes(pos);
    novo = new Node(item);
    novo->prox = p->prox;
    p->prox = novo;
    tamanho++;
    if(novo->prox == nullptr)
        tail = novo;
}
 //nuca precisaremos de fazer remoções em nossa lista/grafo

int ListaEncadeada::pesquisa(int pesquisado)
{
    int aux = -1; Node *p;
    if(tamanho == 0)
        throw "ERRO: lista vazia!";
    p = head->prox;
    while(p != nullptr)
    {
        if(p->nroVertice == pesquisado)
        {
            aux = p->nroVertice;
            break;
        }
    }
    return aux;
} 

//checar se fica no modelo correto
void ListaEncadeada::Imprime()
{
    Node *p;
    p = head->prox;
    while(p != nullptr)
    {
        std::cout << p->nroVertice << " ";
        p = p->prox;
    }
    std::cout << std::endl;
}

void ListaEncadeada::Limpa()
{
    Node *p = head->prox;
    while(p != nullptr)
    {
        head->prox = p->prox;
        delete p;
        p = head->prox;
    }
    tail = head;
    tamanho = 0;
}