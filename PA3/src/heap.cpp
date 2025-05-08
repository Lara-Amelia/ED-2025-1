#include "heap.hpp"

Heap::Heap(int maxsize)
{
    tamanho = 0; //usaremos para medir onde/quantos elementos já foram inseridos
    data = new int[maxsize];
}

Heap::~Heap()
{
    delete[] data;
}

int Heap::GetAncestral(int posicao)
{
    return (posicao-1)/2;
}

int Heap::GetSucessorDir(int posicao)
{
    return 2 * posicao + 2;
}

int Heap::GetSucessorEsq(int posicao)
{
    return 2 * posicao + 1;
}

bool Heap::Vazio()
{
    if(tamanho == 0)
        return true;
    else
        return false;    
}

void Heap::Inserir(int x)
{
    data[tamanho] = x; //inserimos na última posição
    int i = tamanho;
    //anteriores em nível/pais
    int p;
    while(i > 0)
    {
        p = GetAncestral(i);
        if(data[i] < data[p])
        {
            int aux = data[p];
            data[p] = data[i];
            data[i] = aux;
            i = p;
        }
        else
            break;  
    }
    tamanho++;
}

int Heap::Remover()
{
    int x = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    int i = 0;
    //int s = menor sucessor de i
    int menor = i;
    int sEsq;
    int sDir;
    while(true)
    {
        sEsq = GetSucessorEsq(i);
        sDir = GetSucessorDir(i);
        /*if(data[sDir] <= data[sEsq])
            s = sDir;
        else
            s = sEsq;
        int aux = data[s];
        data[s] = data[i];
        data[i] = aux;
        i = s;*/
        //checa se ambos os filhos existem e qual é o menor deles
        if ((sEsq < tamanho) && (data[sEsq] < data[menor])) 
        {
            menor = sEsq;
        }
        if ((sDir < tamanho) && (data[sDir] < data[menor])) 
        {
            menor = sDir;
        }

        //se o menor sucessor é menor que o atual, trocamos de posição
        if (menor != i)
        {
            int aux = data[menor];
            data[menor] = data[i];
            data[i] = aux;
            i = menor; 
        } else 
        {
            break; //heap está em ordem
        }
    };
    return x;
}