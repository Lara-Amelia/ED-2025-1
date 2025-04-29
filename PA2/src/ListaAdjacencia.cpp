#include "include/ListaAdjacencia.hpp"
#include "include/ListaEncadeada.hpp"

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
    if((pos > tamanho) || (pos < 0))
        throw "Posição inválida!"; //talvez usar exception
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
        throw "Posição inválida!"; //talvez usar exception
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
    if(tamanho == 0)
        throw "ERRO: lista vazia!";
    p = head->prox;
    while(p != nullptr)
    {
        if(p->vertice == pesquisado)
        {
            aux = p->vertice;
            break;
        }
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

int* ListaAdjacencia::geraVetorTam()
{
    int grauVert[tamanho];
    NodeAdj* p = head; //como se fosse um iterador
    //preenche um vetor com o tamanho de cada lista
    for(int i = 0; i < tamanho; i++)
    {
        p = p->prox;
        grauVert[i] = p->listaArestas.tamanho;
    }
}