#include "Listas.hpp"
#include "transporte.hpp"

Transporte::Transporte()
{}

Transporte::~Transporte()
{}

void Transporte::InsereVertice()
{
    int size = armazens.tamanho;
    armazens.InsereVert(size, size);
}

void Transporte::InsereAresta(int v, int w)
{
    armazens.InsereAresta(v, w);
}



int Transporte::QuantidadeVertices()
{
    return armazens.tamanho;
}

int Transporte::QuantidadeArestas()
{
    int qtArestas = 0;
    NodeAdj* p = armazens.head;
    for(int i = 0; i < armazens.tamanho; i++)
    {
        p = p->prox;
        qtArestas += p->listaArestas.tamanho;
    }
    return qtArestas/2;
}

int Transporte::GrauMinimo()
{
    int* gVertex = armazens.geraVetorTam();
    //percorrer gVertex, encontrar o menor elemento e o vertice associado
    int min = gVertex[0];
    for(int i = 1; i < armazens.tamanho; i++)
    {
        if(gVertex[i] < min)
        {
            min = gVertex[i];
        }
    }
    return min;
}

int Transporte::GrauMaximo()
{
    int* gVertex =armazens.geraVetorTam();
    int max = gVertex[0];
    for(int i = 0; i < armazens.tamanho; i++)
    {
        if(gVertex[i] > max)
        {
            max = gVertex[i];
        }
    }
    return max;
}

void Transporte::ImprimeVizinhos(int v)
{
    NodeAdj *p = armazens.PosicionaEmAdj(v);
    p->listaArestas.Imprime();
}