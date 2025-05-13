#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <exception>
#include <cmath>

ordUniversal::ordUniversal(float A, float B, float C, int limCusto)
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

void ordUniversal::ordenadorUniversal(int* V, int tam, int MinTamParticao, int limiarQuebras, contador_t &s)
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
void ordUniversal::registraEstatisticas(double &custo, contador_t &stats)
{
    custo = (double)(coefA*stats.cmp) + (coefB*stats.move) + (coefC*stats.calls);
}

void ordUniversal::imprimeEstatisticas(double* custo, contador_t* stats, int t, int numMPS, double diffCusto)
{
    //std::cout << "iter " << numMPS << " " << std::endl;
    std::cout << "mps " << t << " cost " << *(custo) << " cmp " << stats->cmp 
              << " move " << stats->move << " calls " << stats->calls << " " << std::endl;
    if(numMPS == 5)
    {
        std::cout << "nummps 6 limParticao " << t << " mpsdiff " << diffCusto << std::endl;
    }         
}

int ordUniversal::menorCusto(estatisticas_t* stats)
{
    double min = stats[0].custo;
    int indiceMin = 0;
    for(int i = 1; i < 6; i++)
    {
        if(stats[i].custo < min)
        {
            min = stats[i].custo;
            indiceMin = i;
        }
    }
    return indiceMin;
}

//ACHO que está pronto
int ordUniversal::determinaLimiarParticao(int* v, int tam, int limiarCusto)
{
    int minMPS = 2; //menor partição possível
    int maxMPS = tam; //maior partição possível
    int passoMPS = (maxMPS - minMPS )/5; //divisão em 5 intervalos equidistantes
    int diffCusto = limiarCusto + 1; //iniciamos com um custo maior que o limiar - T na 1° iter
    estatisticas_t estatisticas[6];
    int limParticao = 2;
    int numMPS = 6; //tamanho máximo de numMPS
    //mps na impressão será o valor de t, nro da iteração será numMPS
    while((diffCusto > limiarCusto) && (numMPS >= 5))
    {
        int iter = 0;
        std::cout << "iter " << iter << " " << std::endl;
        numMPS=0;
        for(int t=minMPS; t<=maxMPS; t+=passoMPS) //para cada tamanho possível de partição
        {
            int* vTemp = new int[tam];
            for(int i = 0; i < tam; i++)
            {
                vTemp[i] = v[i];
            }
            estatisticas[numMPS].limParticao = t;
            estatisticas[numMPS].custo = 0.0;
            resetcounter(estatisticas[numMPS].stats);
            ordenadorUniversal(vTemp, tam , t , tam, estatisticas[numMPS].stats);
            registraEstatisticas(estatisticas[numMPS].custo, estatisticas[numMPS].stats); //passa um ponteiro para a posição no array custo
            imprimeEstatisticas(&estatisticas[numMPS].custo, &estatisticas[numMPS].stats, estatisticas[numMPS].limParticao, numMPS, diffCusto); //modificaremos o seu valor
            numMPS++;
            delete[] vTemp;
        }
        int limMinPartIndex = menorCusto(estatisticas); //obteremos o valor explícito do limP, depois o seu índice
        limParticao = estatisticas[limMinPartIndex].limParticao;
        calculaNovaFaixa(limMinPartIndex, minMPS, maxMPS, passoMPS, numMPS);
        //mudar para indices do maior e menor custo
        diffCusto = fabs(estatisticas[minMPS].custo - estatisticas[maxMPS].custo);
        iter++;
    }
    return limParticao;
}

int ordUniversal::getMPS(int indice, int minMPS, int passoMPS)
{
    return minMPS + (indice*passoMPS);
}

//limParticao é a partição melhor/de menor custo encontrada em determinarLimiarParticao
//talvez tenhamos de passar parâmetros dinamicamente, visando a atualizá-los
void ordUniversal::calculaNovaFaixa(int limParticao , int &minMPS, int &maxMPS, int &passoMPS, int numMPS)
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
    int oldminMPS = minMPS;
    //mudar getMPS para obter o valor limParticao (t) armazenado nas posições indicadas do vetor
    minMPS = getMPS(newMin, oldminMPS, (passoMPS)); //calcula o novo tamanho de partição
    maxMPS = getMPS(newMax, oldminMPS, (passoMPS));
    passoMPS = (int) (maxMPS - minMPS) / 5 ;
    if(passoMPS == 0) 
        passoMPS++;
}

//antes de determinar o limiar de quebras, devemos obter o limiar de partição (será usado na chamada do ordenador)
/*int ordUniversal::determinaLimiarQuebras(int* v, int tam, int limiarCusto)
{
    int minLQ = 1; //menor quantidade de quebras
    int maxLQ = tam - 1; //maior quantidade de quebras
    int passoLQ = (maxLQ - minLQ)/5; //divisão em 5 intervalos equidistantes
    int diffCusto = limiarCusto + 1; //iniciamos com um custo maior que o limiar - T na 1° iter
    estatisticas_t estatisticasQS[6];
    estatisticas_t estatisticasIN[6];
    int limQB = 1;
    int numLQ = 6; //tamanho máximo de numMPS
    //mps na impressão será o valor de t, nro da iteração será numMPS
    while((diffCusto > limiarCusto) && (numLQ >= 5))
    {
        numLQ=0;
        for(int t=minLQ; t<=maxLQ; t+=passoLQ) //para cada tamanho possível de partição
        {
            ordenadorUniversal(v, tam , t , limQB, &stats[numLQ]);
            registraEstatisticas(&custo[numLQ], &stats[numLQ]); //passa um ponteiro para a posição no array custo
            imprimeEstatisticas(&custo[numLQ], stats, limQB, numLQ, diffCusto); //modificaremos o seu valor
            numLQ++;
            //imprimeEstatisticas provavelmente será alterado
        }
        //limQB = menorCusto(custo);
        //calculaNovaFaixa(limQB, minLQ, maxLQ, passoLQ, numLQ);
        diffCusto = fabs(custo[minLQ] - custo[maxLQ]); //provavelmente devemos usar 
    }
    return limQB;
}*/