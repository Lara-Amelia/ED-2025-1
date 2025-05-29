#include "unionFind.hpp"
#include <iostream>

UnionFind::UnionFind(int quantidade_subconjuntos)
{
    subconjuntos = new Subconjunto[quantidade_subconjuntos];
    tamanho = quantidade_subconjuntos;
}

UnionFind::~UnionFind()
{
    delete[] subconjuntos;
}

void UnionFind::Make(int x)
{
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x)
{
    int novaRaiz = x;
    while(subconjuntos[novaRaiz].representante != novaRaiz)
    {
        novaRaiz = subconjuntos[novaRaiz].representante;
    }
    subconjuntos[x].representante = novaRaiz;
    return novaRaiz;
}

void UnionFind::Union(int x, int y)
{
    int raizX = Find(x);
    int raizY = Find(y);
    if(raizX != raizY)
    {
        if(subconjuntos[raizX].rank < subconjuntos[raizY].rank)
        {
            subconjuntos[raizX].representante = subconjuntos[raizY].representante;
        }

        else if(subconjuntos[raizX].rank > subconjuntos[raizY].rank)
        {
            subconjuntos[raizY].representante = subconjuntos[raizX].representante;
        }
        else
        {
            subconjuntos[raizX].representante = subconjuntos[raizY].representante;
            subconjuntos[raizX].rank++;
        }
    }
}