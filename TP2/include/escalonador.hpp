#ifndef HEAP_HPP
#define HEAP_HPP

#include "evento.hpp"

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Inserir(Evento* eventoPtr);
        Evento* Remover();

        void setMaxSize(int n);
        int getTam();
        bool Vazio();

    private:
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int maxsize;
        int tamanho;
        Evento** data; //vetor com a heap
};

#endif