#ifndef ORDENADORUNIVERSAL_HPP
#define ORDENADORUNIVERSAL_HPP
#include "ordenadores.hpp"

//struct para registrar estatísticas no limiar de partição
typedef struct estatistica 
{
    double custo;
    int limParticao;
    contador_t stats;
} estatisticas_t;

//struct para registrar estatísticas no limiar de quebras 
typedef struct stat
{
    double custoIN;
    double custoQS;
    int limQuebras;
    double diffCusto;
    contador_t statsIN;
    contador_t statsQS;
} estatisticasLQ;

class ordUniversal
{
    private:
    double coefA;       //comps
    double coefB;       //movs
    double coefC;       //calls
    float limiarCusto;  
    int nroQuebras;
    int limiarQuebras;
    int minTamParticao;
    int seed;

    public:
    ordUniversal(double A, double B, double C, float limCusto, int seed); //construtor para a classe
    void ordenadorUniversal(int* V, int tam, int MinTamParticao, int limiarQuebras, contador_t &s);
    int calculaQuebras(int* vetor, int tam);

////métodos get e set para os atributos privados da classe///////////////////////////////////////////////////////////////////////// 
    void setnroQuebras(int qtQuebras);
    void setLimiarQuebras(int limQB);
    void setMinTamParticao(int minTParticao);

////métodos utilizados para obter o Limiar de Partição///////////////////////////////////////////////////////////////////////////////
    int determinaLimiarParticao(int* v, int tam, int limiarCusto);
    void calculaNovaFaixa(int limParticao , int &minMPS, int &maxMPS, int &passoMPS, int numMPS, estatisticas_t* stats);
    int getMPS(int indice, estatisticas_t* stats, int numMPS);
    int menorCusto(estatisticas_t* stats);
    int encontraElemento(estatisticas_t* stats, int particao, int numMPS);
    void registraEstatisticas(double &custo, contador_t &stats); //esta função também é utilizada para o limiar de quebras
    void imprimeEstatisticas(double* custo, contador_t* stats, int t, int numMPS, double diffCusto);
    
////métodos utilizados para obter o Limiar de Quebras////////////////////////////////////////////////////////////////////////////////
    int determinaLimiarQuebras(int* v, int tam, int limiarCusto, int limTamParticao);
    void calculaNovaFaixaLQ(int limMinQBIndex, int &minLQ, int &maxLQ, int &passoLQ, int numLQ, estatisticasLQ* stats);
    int shuffleVector(int* vetor, int size, int numShuffle);
    void calculaDiffCustosLQ(estatisticasLQ* stats, int numLQ);
    int getLQ(int indice, estatisticasLQ* stats, int numLQ);
    int menorCustoLQ(estatisticasLQ* stats, int numLQ);
    int encontraElementoLQ(estatisticasLQ* stats, int quebras, int numLQ);
    void imprimeEstatisticasLQ(estatisticasLQ stats, int t, int numLQ);
};
#endif

/* antes de invocar o ordenador universal, determinamos os limiares de quebras e tamanho de partição,
   que são passados como parâmetros para o ordenador (será um método da classe)
*/

/*
   para obter o limiar de quebras, iremos simular os 2 algoritmos no meio do intervalo (0, n-1)
   e, a partir daí, checar se devemos, então, investigar a primeira ou a segunda metade do intervalo 
   (similar a uma busca binária). o custo será dado pela expressão de custo f dada na descrição do TP 
   consideramos que, se o vetor possui k quebras, então ordená-lo tem o mesmo custo de ordenar um vetor
   de k elementos com k-1 quebras
   um vetor com k quebras está dividido em k+1 segmentos já ordenados - podemos os ordenar cada segmento
   separadamente com cada um dos algoritmos e combinar os custos, como feito para o limiar de partição
   (é semelhante a simular a ordenação para um número x de quebras)
   para o limite de quebras, também faremos a divisão em 5 intervalos e, para cada um deles, 
   aplicaremos diretamente o qs e o is, comparando os custos obtidos e usando isso para o refinamento
*/
