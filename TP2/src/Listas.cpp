#include "Listas.hpp"
#include <iostream>
#include <exception>

//Métodos da classe ListaEncadeada e Node associado///////////////////////////////////////////////////////////////////////
//Não implementamos operações de remoção pois elas não são necessárias em nosso sistema

//construtor default para o node 
Node::Node()
{
    aresta = -1;
    prox = nullptr;
}

Node::Node(int valor)
{
    aresta = valor;
    prox = nullptr;
}

//construtor para a lista encadeada
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

//método que posiciona o ponteiro no node anterior à posição desejada
Node* ListaEncadeada::PosicionaAntes(int pos)
{
    Node *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw std::runtime_error("posição inválida na lista encadeada"); 
    p = head;
    for(i = 0; i < pos; i++)
    {
        p = p->prox;
    }
    return p;
}

//método que posiciona o ponteiro na posição desejada
Node* ListaEncadeada::PosicionaEm(int pos)
{
    Node *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw std::runtime_error("posição inválida na lista encadeada");  
    p = head;
    for(i = 0; i <= pos; i++)
    {
        p = p->prox;
    }
    return p;
}

void ListaEncadeada::setAresta(int pos, int novoVertice)
{
    Node *p;
    p = PosicionaEm(pos);
    p->aresta = novoVertice; 
}

int ListaEncadeada::getAresta(int pos)
{
    Node *p;
    p = PosicionaEm(pos);
    return p->aresta;
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

int ListaEncadeada::pesquisa(int pesquisado)
{
    int aux = -1; Node *p;
    if(tamanho == 0)
        throw std::out_of_range("ERRO: lista encadeada vazia!");
    p = head->prox;
    while(p != nullptr)
    {
        if(p->aresta == pesquisado)
        {
            aux = p->aresta;
            break;
        }
        p = p->prox;
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
        std::cout << p->aresta << " ";
        p = p->prox;
    }
    std::cout << std::endl;
}

void ListaEncadeada::Limpa()
{
    if (head == nullptr) return; 

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

int ListaEncadeada::getTamanho()
{
    return tamanho;
}

//construtor de cópia para a lista encadeada, caso seja necessário
ListaEncadeada::ListaEncadeada(const ListaEncadeada& outra)
{
    tamanho = 0;
    head = new Node();
    tail = head;

    Node* p = outra.head->prox;
    while (p != nullptr)
    {
        inserePosicao(p->aresta, tamanho);
        p = p->prox;
    }
}

//sobrecarga do operador de igualdade para cópias
ListaEncadeada& ListaEncadeada::operator=(const ListaEncadeada& outra)
{
    if (this != &outra)
    {
        Limpa();  // limpa a lista atual

        Node* p = outra.head->prox;
        while (p != nullptr)
        {
            inserePosicao(p->aresta, tamanho);
            p = p->prox;
        }
    }
    return *this;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//Métodos associados à classe ListaAdjacencia e ao Node correspondente/////////////////////////////////////
NodeAdj::NodeAdj()
{
    vertice = -1;
    prox = nullptr;
    //listaArestas chama o contrutir default automaticmante
}

NodeAdj::NodeAdj(int nroVer)
{
    vertice = nroVer;
    prox = nullptr;
}

//construtor default para a lista de adjacência
ListaAdjacencia::ListaAdjacencia()
{
    tamanho = 0;
    head = new NodeAdj();
    tail = head;
}

//destrutor para a lista de adjacência
ListaAdjacencia::~ListaAdjacencia()
{
    LimpaAdj();
    delete head;
}

NodeAdj* ListaAdjacencia::PosicionaAntesAdj(int pos)
{
    NodeAdj *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw std::out_of_range ("Posição inválida na lista de adjacência"); //talvez usar exception
    p = head;
    for(i = 0; i < pos; i++)
    {
        p = p->prox;
    }
    return p;
}

NodeAdj* ListaAdjacencia::PosicionaEmAdj(int pos)
{
    NodeAdj *p; int i;
    if((pos > tamanho) || (pos < 0))
        throw std::out_of_range("Posição inválida na lista de adjacência"); //talvez usar exception
    p = head;
    for(i = 0; i <= pos; i++)
    {
        p = p->prox;
    }
    return p;
}

void ListaAdjacencia::InsereVert(int nroVert, int pos)
{
    NodeAdj *novo;
    novo = new NodeAdj(nroVert);
    if(pos == 0)
    {
        novo->prox = head->prox;
        head->prox = novo;
        if((tamanho == 0) || (novo->prox == nullptr))
            tail = novo;
    }
    else
    {   
        NodeAdj *p = PosicionaAntesAdj(pos);
        novo->prox = p->prox;
        p->prox = novo;
        if(novo->prox == nullptr)
            tail = novo;
    }
    tamanho++;
}

void ListaAdjacencia::InsereAresta(int v, int e)
{
    NodeAdj *p = PosicionaEmAdj(v);
    int size = p->listaArestas.tamanho; 
    p->listaArestas.inserePosicao(e, size); 
}

int ListaAdjacencia::pesquisaVert(int pesquisado)
{
    int aux = -1; NodeAdj *p;
    if(tamanho == 0)
        throw std::out_of_range("ERRO: lista vazia!");
    p = head->prox;
    while(p != nullptr)
    {
        if(p->vertice == pesquisado)
        {
            aux = p->vertice;
            break;
        }
        p = p->prox;
    }
    return aux;
}

void ListaAdjacencia::LimpaAdj()
{
    NodeAdj *p = head->prox;
    while(p != nullptr)
    {
        head->prox = p->prox;
        p->listaArestas.Limpa();
        delete p;
        p = head->prox;
    }
    tail = head;
    tamanho = 0;
}