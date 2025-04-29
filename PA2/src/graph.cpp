#include "ListaAdjacencia.hpp"
#include "ListaEncadeada.hpp"
#include "graph.hpp"

Grafo::Grafo()
{}

Grafo::~Grafo()
{}

void Grafo::InsereVertice()
{
    int size = vertices.tamanho;
    vertices.InsereVert(size, size);
}

void Grafo::InsereAresta(int v, int w)
{
    vertices.InsereAresta(v, w);
}

int Grafo::QuantidadeVertices()
{
    return vertices.tamanho;
}

int Grafo::QuantidadeArestas()
{
    int qtArestas = 0;
    NodeAdj* p = vertices.head;
    for(int i = 0; i < vertices.tamanho; i++)
    {
        p = p->prox;
        qtArestas += p->listaArestas.tamanho;
    }
    return qtArestas/2;
}

int Grafo::GrauMinimo()
{
    int* gVertex = vertices.geraVetorTam();
    //percorrer gVertex, encontrar o menor elemento e o vertice associado
    int min = gVertex[0];
    for(int i = 1; i < vertices.tamanho; i++)
    {
        if(gVertex[i] < min)
        {
            min = gVertex[i];
        }
    }
    return min;
}

int Grafo::GrauMaximo()
{
    int* gVertex = vertices.geraVetorTam();
    int max = gVertex[0];
    for(int i = 0; i < vertices.tamanho; i++)
    {
        if(gVertex[i] > max)
        {
            max = gVertex[i];
        }
    }
    return max;
}

void Grafo::ImprimeVizinhos(int v)
{
    NodeAdj *p = vertices.PosicionaEmAdj(v);
    p->listaArestas.Imprime();
}