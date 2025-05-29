#include "minHeap.hpp"
#include "unionFind.hpp"
#include <iostream>

int main(void)
{
    int numVertices, numArestas;
    //Faz a leitura dos dados e das arestas com seus custos da entrada padrão
    std::cin >> numVertices >> numArestas;
    //int* vertices = new int[numVertices];

    //Aresta* arestas = new Aresta[numArestas];
    /*for (int i = 0; i < numArestas; ++i) 
    {
        std::cin >> arestas[i].u >> arestas[i].v >> arestas[i].custo;
    }*/

    //imprimir o valor da árvore geradora mínima 
    Heap heap(numArestas);
    for (int i = 0; i < numArestas; ++i) 
    {
        Aresta a;
        std::cin >> a.u >> a.v >> a.custo;
        heap.Inserir(a);
    }

    UnionFind grafo(numVertices);
    int custo = 0;
    int edges = 0;
    for(int i = 0; i < numVertices; i++)
    {
        grafo.Make(i); 
    }

    while (!heap.Vazio() && edges < numVertices - 1) 
    {
        Aresta menor = heap.Remover();
        int raizU = grafo.Find(menor.u);
        int raizV = grafo.Find(menor.v);

        if (raizU != raizV) 
        {
            custo += menor.custo;
            edges++;
            grafo.Union(raizU, raizV);
        }
    }
    std::cout << custo << std::endl;
}