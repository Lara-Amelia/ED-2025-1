#include "escalonador.hpp"
#include "evento.hpp"

//talvez tenhamos de alterar para que lide com eventos em si, ou podemos utilizar somente as ids de eventos

Heap::Heap(int maxsize)
{
    tamanho = 0; //usaremos para medir onde/quantos elementos já foram inseridos
    data = new Evento*[maxsize];
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
    return tamanho == 0;  
}

int Heap::getTam()
{
    return tamanho;
}

void Heap::Inserir(Evento* eventoPtr)
{
    data[tamanho] = eventoPtr; //inserimos na última posição
    int i = tamanho;
    //anteriores em nível/pais
    int p;
    while(i > 0)
    {
        p = GetAncestral(i);
        if(data[i]->getChave() < data[p]->getChave())
        {
            Evento* aux = data[p];
            data[p] = data[i];
            data[i] = aux;
            i = p;
        }
        else
            break;  
    }
    tamanho++;
}

Evento* Heap::Remover()
{
    Evento* x = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    if(tamanho == 0)
        return x;
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
        if ((sEsq < tamanho) && (data[sEsq]->getChave() < data[menor]->getChave())) 
        {
            menor = sEsq;
        }

        if ((sDir < tamanho) && (data[sDir]->getChave() < data[menor]->getChave())) 
        {
            menor = sDir;
        }

        //se o menor sucessor é menor que o atual, trocamos de posição
        if (menor != i)
        {
            Evento* aux = data[menor];
            data[menor] = data[i];
            data[i] = aux;
            i = menor; 
        } 

        else 
        {
            break; //heap está em ordem
        }
    };
    return x;
}

/*Evento Heap::Topo()
{
    return data[0];  // ou const Evento& se preferir não copiar
}*/