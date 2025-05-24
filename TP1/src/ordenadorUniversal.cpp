#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <exception>
#include <cmath>
#include <iomanip>

//FALTA ADICIONAR TRATAMENTO DE EXCEÇÕES, VERIFICAÇÕES DE ESPAÇO/TAMANHO 
//ALOCAÇÃO DINÂMICA NO VETOR DE ESTATISTICAS PARA O LIMIAR DE QUEBRAS
ordUniversal::ordUniversal(double A, double B, double C, float limCusto, int seedArquivo)
{
    coefA = A; coefB = B; coefC = C;
    limiarCusto = limCusto;
    seed = seedArquivo;
    //inicializamos os valores que ainda serão definidos como 0
    limiarQuebras = 0;
    minTamParticao = 0;
    nroQuebras = 0;
}

//template <typename T>
void ordUniversal::ordenadorUniversal(inventado* V, int tam, int MinTamParticao, int limiarQuebras, contador_t &s)
{
    if(nroQuebras < limiarQuebras)
    {
        insercao (V, 0, tam, s);
    } 
    else 
    {
        if(tam > minTamParticao)
        {
            quickSort(V, 0, (tam-1), s, MinTamParticao);
        } 
        else
        {
            insercao(V, 0, tam, s);
        }
    }
}

//template <typename T>
int ordUniversal::calculaQuebras(inventado* vetor, int tam)
{
    int nroQuebras = 0;
    for(int i = 1; i < tam; i++)
    {
        if(vetor[i].chave < vetor[i-1].chave) //se o atual for menor que o seu antecessor
            nroQuebras++;
    }
    return nroQuebras;
}

//template <typename T>
void ordUniversal::setnroQuebras(int qtQuebras)
{
    nroQuebras = qtQuebras;
}

//template <typename T>
void ordUniversal::setLimiarQuebras(int limQB)
{
    limiarQuebras = limQB;
}

//template <typename T>
void ordUniversal::setMinTamParticao(int minTParticao)
{
    minTamParticao = minTParticao;
}

//template <typename T>
int ordUniversal::determinaLimiarParticao(inventado* v, int tam, int limiarCusto)
{
    int minMPS = 2; //menor partição possível
    int maxMPS = tam; //maior partição possível
    int passoMPS = (maxMPS - minMPS )/5.0; //divisão em 5 intervalos equidistantes
    float diffCusto = limiarCusto + 1; //iniciamos com um custo maior que o limiar - T na 1° iter
    estatisticas_t estatisticas[6];
    int limParticao = 2;
    int numMPS = 6; //tamanho máximo de numMPS
    //mps na impressão será o valor de t, nro da iteração será numMPS
    int iter = 0;
    while((diffCusto > limiarCusto) && (numMPS >= 5))
    {
        try
        {
            std::cout << "iter " << iter << " " << std::endl;
            numMPS=0;
            for(int t=minMPS; t<=maxMPS; t+=passoMPS) //para cada tamanho possível de partição
            {
                inventado* vTemp = new inventado[tam];
                for(int i = 0; i < tam; i++)
                {
                    vTemp[i] = v[i];
                }
                estatisticas[numMPS].limParticao = t;
                estatisticas[numMPS].custo = 0.0;
                resetcounter(estatisticas[numMPS].stats);

                ordenadorUniversal(vTemp, tam , t, -1, estatisticas[numMPS].stats);
                registraEstatisticas(estatisticas[numMPS].custo, estatisticas[numMPS].stats);
                
                imprimeEstatisticas(&estatisticas[numMPS].custo, &estatisticas[numMPS].stats, estatisticas[numMPS].limParticao, numMPS, diffCusto);
                numMPS++;
                delete[] vTemp;
            }
            int limMinPartIndex = menorCusto(estatisticas, numMPS); //obteremos o valor explícito do limP, depois o seu índice
            limParticao = estatisticas[limMinPartIndex].limParticao;

            //std::cout << "oldminMPS: " << oldminMPS << std::endl;
            calculaNovaFaixa(limMinPartIndex, minMPS, maxMPS, passoMPS, numMPS, estatisticas);

            int indexminMPS = encontraElemento(estatisticas, minMPS, numMPS);
            //std::cout << "indexminMPS: " << indexminMPS << std::endl;
            int indexmaxMPS = encontraElemento(estatisticas, maxMPS, numMPS);
            //std::cout << "indexmaxMPS: " << indexmaxMPS << std::endl;
            diffCusto = (fabs(estatisticas[indexminMPS].custo - estatisticas[indexmaxMPS].custo));
            //std::cout << "diffCusto final: " << diffCusto << std::endl;
            std::cout << std::fixed << std::setprecision(6);
            std::cout << "nummps " << numMPS << " limParticao " << limParticao << " mpsdiff " << diffCusto << std::endl;
            std::cout << std::endl;
            iter++;
        }    
        catch (const std::bad_alloc& e) 
        {
            std::cerr << "Erro de alocação de memória em vTemp: " << e.what() << '\n';
        }
        catch(const std::invalid_argument& e) 
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::out_of_range& e) 
        {
            std::cerr << "Erro de índice fora do intervalo: " << e.what() << std::endl;
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Erro inesperado: " << e.what() << std::endl;
        }
    }
    return limParticao;
}


//limParticao é a partição melhor/de menor custo encontrada em determinarLimiarParticao
//talvez tenhamos de passar parâmetros dinamicamente, visando a atualizá-los
//template <typename T>
void ordUniversal::calculaNovaFaixa(int limParticao , int &minMPS, int &maxMPS, int &passoMPS, int numMPS, estatisticas_t* stats)
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
    //mudar getMPS para obter o valor limParticao (t) armazenado nas posições indicadas do vetor
    //std::cout << "newMin: " << newMin << std::endl;
    //std::cout << "newMax: " << newMax << std::endl;
    
    minMPS = getMPS(newMin, stats, numMPS); //calcula o novo tamanho de partição
    maxMPS = getMPS(newMax, stats, numMPS);
        //std::cout << "minMPS nova faixa: " << minMPS << std::endl;
        //std::cout << "maxMPS nova faixa: " << maxMPS << std::endl;
    passoMPS = (int)(maxMPS - minMPS)/5;
    if(passoMPS == 0) 
        passoMPS++;

    //na saída a cada iteração, mpsdiff é a diferença entre os custos de newMax e newMin
}

//template <typename T>
int ordUniversal::getMPS(int indice, estatisticas_t* stats, int numMPS)
{
    if((indice < 0) || (indice >= numMPS))
        throw std::out_of_range("Índice fora do intervalo válido em getMPS: " + std::to_string(indice));
    else
        return stats[indice].limParticao;
}

//template <typename T>
int ordUniversal::menorCusto(estatisticas_t* stats, int numMPS)
{
    //VERIFICAR NO VPL SE NÃO GEROU PROBLEMAS
    if (numMPS <= 0) 
    {
        throw std::invalid_argument("menorCusto: vetor de estatísticas vazio ou tamanho inválido.");
    }
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

//template <typename T>
int ordUniversal::encontraElemento(estatisticas_t* stats, int particao, int numMPS)
{
    for(int i = 0; i < numMPS; i++)
    {
        if(stats[i].limParticao == particao)
        {
             return i;
        }
    }   
    throw std::out_of_range("Partição " + std::to_string(particao) + " não encontrada em encontraElemento.");
}

//fará o cálculo do custo com base nos stats obtidos
//template <typename T>
void ordUniversal::registraEstatisticas(double &custo, contador_t &stats)
{
    custo = (double)(coefA*stats.cmp) + (coefB*stats.move) + (coefC*stats.calls);
}

//template <typename T>
void ordUniversal::imprimeEstatisticas(double* custo, contador_t* stats, int t, int numMPS, double diffCusto)
{
    std::cout << std::fixed << std::setprecision(9);
    std::cout << "mps " << t << " cost " << *(custo) << " cmp " << stats->cmp 
              << " move " << stats->move << " calls " << stats->calls << " " << std::endl;
}

//antes de determinar o limiar de quebras, devemos obter o limiar de partição (será usado na chamada do ordenador)
//template <typename T>
int ordUniversal::determinaLimiarQuebras(inventado* v, int tam, int limiarCusto, int limTamParticao)
{
    int minLQ = 1;                     //menor quantidade de quebras 
    int maxLQ = tam/2;                //como já sabemos que in é ineficiente para nros grandes de quebras, usamos metade do intervalo
    int passoLQ = (maxLQ - minLQ)/5; //divisão em 5 intervalos equidistantes
    float diffCusto = limiarCusto + 1; //iniciamos com um custo maior que o limiar - T na 1° iter
    //pode ter vários tamanhos, fazer alguma checagem/alocação dinâmica
    //estatisticasLQ statsLQ[10];
    //int limQuebras = 1;
    int numLQ = 6; 
    int iter = 0;
    estatisticasLQ* statsLQ = nullptr;
    inventado *vTemp = nullptr;
    //minLQ será o valor de limiar que tem a menor diferença absoluta entre IN e QS
    while((diffCusto > limiarCusto) && (numLQ >= 5))
    {
        try
        {
            std::cout << "iter " << iter << " " << std::endl;
            numLQ = (((maxLQ-minLQ))/passoLQ) + 1;
            //já que o valor de numLQ não é fixo, alocamos dinamicamente
            //estatisticasLQ* statsLQ = nullptr;
            statsLQ = nullptr;
            statsLQ = new estatisticasLQ[numLQ];
            numLQ=0;
            estatisticas_t ordenacao;
            //int *vTemp = nullptr;
            vTemp = nullptr;
            vTemp = new inventado[tam];
            for(int i = 0; i < tam; i++)
            {
                vTemp[i] = v[i];
            }
            //faz a ordenação do vetor original temporário
            quickSort(vTemp, 0, tam-1, ordenacao.stats, limTamParticao);
            //t será o valor de cada limiar de quebra testado por iteração
            for(int t=minLQ; t<=maxLQ; t+=passoLQ) //para cada tamanho possível de partição
            {
                //reset estatísticas a cada iteração
                statsLQ[numLQ].limQuebras = t;
                statsLQ[numLQ].custoIN = 0.0;
                statsLQ[numLQ].custoQS = 0.0;
                resetcounter(statsLQ[numLQ].statsIN);
                resetcounter(statsLQ[numLQ].statsQS);

                //chama shuffle, chama INS e QS e registra seus custos separadamente
                srand48(seed);
                shuffleVector(vTemp, tam, t); //vTemp é retornado com o número desejado de quebras
                inventado* vTempIN = new inventado[tam];
                for(int i = 0; i < tam; i++)
                {
                    vTempIN[i] = vTemp[i];
                }            
                quickSort(vTempIN, 0, tam-1, statsLQ[numLQ].statsQS, limTamParticao);
                //calcula o custo individual do QS
                registraEstatisticas(statsLQ[numLQ].custoQS, statsLQ[numLQ].statsQS);

                //passamos com tam e não tam-1 como tamanho
                insercao(vTemp, 0, tam, statsLQ[numLQ].statsIN);
                registraEstatisticas(statsLQ[numLQ].custoIN, statsLQ[numLQ].statsIN);

                imprimeEstatisticasLQ(statsLQ[numLQ], t, numLQ);

                numLQ++;
                delete[] vTempIN;
            }
            calculaDiffCustosLQ(statsLQ, numLQ);
            int limMinQBIndex = menorCustoLQ(statsLQ, numLQ); //obteremos o valor explícito do limP, depois o seu índice
            limiarQuebras = statsLQ[limMinQBIndex].limQuebras;
            //std::cout << "limMinQBIndex: " << limMinQBIndex << std::endl;
            //std::cout << "limiarQuebras: " << limiarQuebras << std::endl;

            calculaNovaFaixaLQ(limMinQBIndex, minLQ, maxLQ, passoLQ, numLQ, statsLQ);

            int indexminLQ = encontraElementoLQ(statsLQ, minLQ, numLQ);
            //std::cout << "indexminLQ: " << indexminLQ << std::endl;
            int indexmaxLQ = encontraElementoLQ(statsLQ, maxLQ, numLQ);
            //std::cout << "indexmaxMPS: " << indexmaxLQ << std::endl;
            diffCusto = static_cast<float>(fabs(statsLQ[indexminLQ].custoIN - statsLQ[indexmaxLQ].custoIN));
            //std::cout << "diffCusto final: " << diffCusto << std::endl;
            std::cout << std::fixed << std::setprecision(6);
            std::cout << "numlq " << numLQ << " limQuebras " << limiarQuebras << " lqdiff " << diffCusto << std::endl;
            if ((diffCusto > limiarCusto) && (numLQ >= 5)) 
            {
                std::cout << std::endl;
            }
            //std::cout << std::endl;
            iter++;
            //delete[] vTemp;
            //delete[] statsLQ;
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "Erro de argumento inválido: " << e.what() << std::endl;
            
            return -1;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << "Erro de acesso a posições inválidas: " << e.what() << std::endl;
            return -2;
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << "Erro: falha na alocação de memória: " << e.what() << std::endl;
            return -3;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Erro inesperado: " << e.what() << std::endl;
            return -4;
        }    
        delete[] vTemp;
        delete[] statsLQ;
    }
    return limiarQuebras;
}

//template <typename T>
void ordUniversal::calculaNovaFaixaLQ(int limMinQBIndex, int &minLQ, int &maxLQ, int &passoLQ, int numLQ, estatisticasLQ* stats)
{
    int newMin, newMax;
    if(limMinQBIndex == 0)
    {
        newMin = 0 ;
        newMax = 2 ;
    } 
    else if(limMinQBIndex == numLQ-1)
    {
        newMin = numLQ-3;
        newMax= numLQ-1;
    } 
    else 
    {
        newMin = limMinQBIndex - 1;
        newMax= limMinQBIndex + 1;
    }
    //mudar getMPS para obter o valor limParticao (t) armazenado nas posições indicadas do vetor
    //std::cout << "newMin: " << newMin << std::endl;
    //std::cout << "newMax: " << newMax << std::endl;
    minLQ = getLQ(newMin, stats, numLQ); //calcula o novo tamanho de partição
    maxLQ = getLQ(newMax, stats, numLQ);
    //std::cout << "minLQ nova faixa: " << minLQ << std::endl;
    //std::cout << "maxLQ nova faixa: " << maxLQ << std::endl;
    passoLQ = (int)(maxLQ - minLQ)/5;
    if(passoLQ == 0) 
        passoLQ++;
    //na saída a cada iteração, mpsdiff é a diferença entre os custos de newMax e newMin   
}

//antes de cada chamada para embaralhamento do vetor (presumivelmente no método determinaLimQuebras),
//devemos chamar srand48(seed)
//numShuffle será o número de quebras que queremos gerar no vetor previamente ordenado
//template <typename T>
int ordUniversal::shuffleVector(inventado* vetor, int size, int numShuffle)
{
    int p1 = 0, p2 = 0; inventado temp;
    for (int t = 0; t < numShuffle; t++) 
    {
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while(p1 == p2) 
        {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        /* Realiza a troca para introduzir uma quebra */
        temp = vetor[p1];
        vetor[p1] = vetor[p2];
        vetor[p2] = temp;
        p1 = p2 = 0;
    }
    return 0;
}

//template <typename T>
void ordUniversal::calculaDiffCustosLQ(estatisticasLQ* stats, int numLQ)
{
    for(int i = 0; i < numLQ; i++)
    {
        stats[i].diffCusto = fabs(stats[i].custoQS - stats[i].custoIN);
    }
}

//template <typename T>
int ordUniversal::getLQ(int indice, estatisticasLQ* stats, int numLQ)
{
    if (indice < 0 || indice >= numLQ) 
    {
        throw std::out_of_range("getLQ: índice fora do intervalo");
    }
    return stats[indice].limQuebras;
}

//template <typename T>
int ordUniversal::menorCustoLQ(estatisticasLQ* stats, int numLQ)
{
    if (numLQ <= 0) 
    {
        throw std::invalid_argument("menorCustoLQ: vetor de estatísticas vazio ou tamanho inválido.");
    }
    double min = stats[0].diffCusto;
    int indexMin = 0;
    for(int i = 0; i < numLQ; i++)
    {
        //std::cout << "diffCusto na posição " << i << " " << stats[i].diffCusto << std::endl;
        if(stats[i].diffCusto < min)
        {
            min = stats[i].diffCusto;
            indexMin = i;
        }
    }
    return indexMin;
}

//template <typename T>
int ordUniversal::encontraElementoLQ(estatisticasLQ* stats, int quebras, int numLQ)
{
    if (numLQ <= 0) 
    {
        throw std::out_of_range("encontraElementoLQ: numLQ inválido");
    }
    for(int i = 0; i < numLQ; i++)
    {
        if(stats[i].limQuebras == quebras)
        {
            return i;
        }
    }   
    throw std::out_of_range("encontraElementoLQ: elemento não encontrado");
}

//template <typename T>
void ordUniversal::imprimeEstatisticasLQ(estatisticasLQ stats, int t, int numLQ)
{
    std::cout << std::fixed << std::setprecision(9);
    std::cout << "qs lq " << t << " cost " << stats.custoQS << " cmp " << stats.statsQS.cmp << " move " << stats.statsQS.move 
              << " calls " << stats.statsQS.calls << std::endl;
    std::cout << "in lq " << t << " cost " << stats.custoIN << " cmp " << stats.statsIN.cmp << " move " << stats.statsIN.move 
              << " calls " << stats.statsIN.calls << std::endl;
}