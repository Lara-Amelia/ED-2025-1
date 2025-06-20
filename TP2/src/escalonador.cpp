#include "escalonador.hpp"
#include "evento.hpp"

#include <exception>
#include <stdexcept>

//construtor para a classe
Heap::Heap(int maxsize)
{
    tamanho = 0; //usaremos para medir onde/quantos elementos já foram inseridos
    data = new Evento*[maxsize];
}

//destrutor para a classe
Heap::~Heap()
{
    delete[] data;
}

//métodos para localização de itens no vetor////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//método para checar se o escalonador/heap está vazio
bool Heap::Vazio()
{
    return tamanho == 0;  
}

int Heap::getTam()
{
    return tamanho;
}

void Heap::setMaxSize(int n)
{
    maxsize = n;
}

//insere elementos (ponteiros para Evento no escalonador)
void Heap::Inserir(Evento* eventoPtr)
{
    if (tamanho == maxsize) 
    {
        throw std::runtime_error("Heap cheia: Nao eh possivel inserir mais eventos."); //
    }

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

//remove elementos do heap/escalonador
Evento* Heap::Remover()
{
    if (tamanho == 0) // Check if heap is empty
    {
        throw std::runtime_error("Escalonador vazio: Nao é possivel remover eventos."); //
    }

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