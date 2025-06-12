#include "Listas.hpp"
#include <iostream>

//Métodos da classe ListaEncadeada e Node associado
//Não implementamos operações de remoção pois elas não são necessárias em nosso sistema
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
    /*if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception*/
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
    /*if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar */
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
//nuca precisaremos de fazer remoções em nossa lista/grafo

int ListaEncadeada::pesquisa(int pesquisado)
{
    int aux = -1; Node *p;
    /*if(tamanho == 0)
        throw "ERRO: lista vazia!";*/
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Métodos associados à classe ListaAdjacencia e ao Node correspondente
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

ListaAdjacencia::ListaAdjacencia()
{
    tamanho = 0;
    head = new NodeAdj();
    tail = head;
}

ListaAdjacencia::~ListaAdjacencia()
{
    LimpaAdj();
    delete head;
}

NodeAdj* ListaAdjacencia::PosicionaAntesAdj(int pos)
{
    NodeAdj *p; int i;
    /*if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception*/
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
    /*if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception*/
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
    p->listaArestas.inserePosicao(e, size); //conferir
}

int ListaAdjacencia::pesquisaVert(int pesquisado)
{
    int aux = -1; NodeAdj *p;
    /*if(tamanho == 0)
        throw "ERRO: lista vazia!";*/
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

void ListaAdjacencia::ImprimeAdj()
{
    NodeAdj* p = head;
    for(int i = 0; i < tamanho; i++)
    {
        p = p->prox;
        p->listaArestas.Imprime();
    }
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

//provavelmente não necessiatremos deste método
int* ListaAdjacencia::geraVetorTam()
{
    int* grauVert = new int[tamanho];
    //lembrar de dar delete no vetor criado
    NodeAdj* p = head; //como se fosse um iterador
    //preenche um vetor com o tamanho de cada lista
    for(int i = 0; i < tamanho; i++)
    {
        p = p->prox;
        grauVert[i] = p->listaArestas.tamanho;
    }
    return grauVert;
}