#ifndef HEAP_HPP
#define HEAP_HPP

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Inserir(int x);
        int Remover();

        bool Vazio();

    private:
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int tamanho;
        int* data; //vetor com a heap
};

#endif