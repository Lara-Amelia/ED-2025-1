#include "include/ListaAdjacencia.hpp"
#include "include/ListaEncadeada.hpp"

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
}