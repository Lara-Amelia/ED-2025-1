#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <exception>
#include <cmath>

ordUniversal::ordUniversal(int A, int B, int C, int limCusto)
{
    coefA = A; coefB = B; coefC = C;
    limiarCusto = limCusto;
    //inicializamos os valores que ainda serão definidos como 0
    limiarQuebras = 0;
    minTamParticao = 0;
    nroQuebras = 0;
}

int ordUniversal:: calculaQuebras(int* vetor, int tam)
{
    int nroQuebras = 0;
    for(int i = 1; i < tam; i++)
    {
        if(vetor[i] < vetor[i-1]) //se o atual for menor que o seu antecessor
            nroQuebras++;
    }
    return nroQuebras;
}

void ordUniversal::ordenadorUniversal(int* V, int tam, int MinTamParticao, int limiarQuebras, contador_t* s)
{
    if(nroQuebras < limiarQuebras)
    {
        insercao (V, tam, s);
    } 
    else 
    {
        if(tam > minTamParticao)
        {
            quickSort(V, 0, (tam-1), s) ;
        } 
        else
        {
            insercao (V, tam, s) ;
        }
    }
}

//fará o cálculo do custo com base nos stats obtidos
void ordUniversal::registraEstatisticas(double* custo, contador_t* stats)
{
    *(custo) = (double)(coefA*stats->cmp) + (coefB*stats->move) + (coefC*stats->calls);
}

void ordUniversal::imprimeEstatisticas(double* custo, contador_t* stats, int t, int numMPS, double diffCusto)
{
    std::cout << "iter " << numMPS << " " << std::endl;
    std::cout << "mps " << t << "cost " << *(custo) << " cmp " << stats->cmp 
              << " move " << stats->move << " calls " << stats->calls << " " << std::endl;
    if(numMPS == 5)
    {
        std::cout << "nummps 6 limParticao " << t << " mpsdiff " << diffCusto << std::endl;
    }         
}

//ACHO que está pronto
int ordUniversal::determinaLimiarParticao(int* v, int tam, int limiarCusto)
{
    int minMPS = 2; //menor partição possível
    int maxMPS = tam; //maior partição possível
    int passoMPS = (maxMPS - minMPS )/5; //divisão em 5 intervalos equidistantes
    int diffCusto = limiarCusto + 1; //iniciamos com um custo maior que o limiar - T na 1° iter
    double custo[6];
    contador_t stats[6];
    int limParticao = 2;
    int numMPS = 6; //tamanho máximo de numMPS
    //mps na impressão será o valor de t, nro da iteração será numMPS
    while((diffCusto > limiarCusto) && (numMPS >= 5))
    {
        numMPS=0;
        for(int t=minMPS; t<=maxMPS; t+=passoMPS) //para cada tamanho possível de partição
        {
            ordenadorUniversal(v, tam , t , tam, &stats[numMPS]);
            registraEstatisticas(&custo[numMPS], &stats[numMPS]); //passa um ponteiro para a posição no array custo
            imprimeEstatisticas(&custo[numMPS], stats, limParticao, numMPS, diffCusto); //modificaremos o seu valor
            numMPS++;
        }
        limParticao = menorCusto();
        calculaNovaFaixa(limParticao, minMPS, maxMPS, passoMPS);
        diffCusto = fabs(custo[minMPS] - custo[maxMPS]);
    }
    return limParticao;
}

//limParticao é a partição melhor/de menor custo encontrada em determinarLimiarParticao
void ordUniversal::calculaNovaFaixa(int limParticao , int minMPS, int maxMPS, int passoMPS)
{
    int newMin, newMax;
    if(limParticao == 0)
    {
        newMin = 0 ;
        newMax = 2 ;
    } 
    else if(limParticao == numMPS-1)
    {
        newMin = numMPS-3;
        newMax= numMPS-1;
    } 
    else 
    {
        newMin = limParticao - 1;
        newMax= limParticao + 1;
    }
    minMPS = getMPS(newMin); //calcula o novo tamanho de partição
    maxMPS = getMPS(newMax);
    passoMPS = (int) (maxMPS - minMPS) / 5 ;
    if (passoMPS == 0) passoMPS++;
}

