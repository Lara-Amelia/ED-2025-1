#include "armazem.hpp"
#include "pilha.hpp"
#include "evento.hpp"
#include <iostream>

//métodos para a classe Seção//////////////////////////////////////////////////////////////////////////////
//construtor default para a classe seção
Secao::Secao()
{
    //o cosntrutor default das pilhas é chamado automaticamente
    destino = -1; //flag para destino ainda não definido
}

//construtor user-defined para a classe seção
Secao::Secao(int dest)
{
    destino = dest;
}

void Secao::setDestino(int n)
{
    destino = n;
}

//métodos para a classe Armazem////////////////////////////////////////////////////////////////////////////////
//construtor default para a classe
Armazem::Armazem()
{
    secoes = nullptr;
    vizinhos = nullptr;
    nroAdj = 0;
    idGrafo = 0;
    custoRemocao = 0;
}

//insere vizinhos no vetor de vizinhos do armazém
void Armazem::setVizinho(int vizinho, int posicao)
{
    if (posicao >= 0 && posicao < nroAdj) 
    {
        vizinhos[posicao] = vizinho;
    } 
    else 
    {
        throw std::out_of_range("Posição inválida em setVizinho");
    }
}

//setter para o número de adjacentes
void Armazem::setAdj(int n)
{
    nroAdj = n;
}

//setor para o destino de uma certa seção
void Armazem::setDestinoSecao(int destino, int posicao)
{
    secoes[posicao].destino = destino;
}

//setter para atributos diversos do armazem
void Armazem::setArmazem(int nAdj, int idG, int custo)
{
    // se já tem alocação, libera para evitar vazamento
    if (secoes != nullptr)
    {
        delete[] secoes;
        secoes = nullptr;
    }
    if (vizinhos != nullptr)
    {
        delete[] vizinhos;
        vizinhos = nullptr;
    }

    nroAdj = nAdj;
    idGrafo = idG;
    custoRemocao = custo;

    secoes = new Secao[nAdj];
    vizinhos = new int[nAdj];

    for (int i = 0; i < nAdj; i++)
    {
        vizinhos[i] = -1;
    }
}

//construtor com parâmetros para a classe Armazem
Armazem::Armazem(int nAdj, int idG, int custo)
{
    nroAdj = nAdj;
    idGrafo = idG;
    secoes = new Secao[nAdj];
    vizinhos = new int[nAdj];
    custoRemocao = custo;
}

//destrutor para a classe Armazem
Armazem::~Armazem()
{
    delete[] secoes;
    delete[] vizinhos;
}

//retorna em qual índice do vetor seções a seção com o destino especificado se encontra
int Armazem::encontraSecao(int destino)
{
    for(int i = 0; i < nroAdj; i++)
    {
        if(this->secoes[i].destino == destino)
            return i;
    }
    throw std::out_of_range("ERRO: secao não encontrada no armazém");   
}

//checa se a pilha principal de uma seção está vazia
bool Armazem::checaVazia(int posSecao)
{
    return secoes[posSecao].principal.Vazia();
}

//checa se a pilha auxiliar de uma seção está vazia
bool Armazem::checaVaziaAux(int posSecao)
{
    return secoes[posSecao].auxiliar.Vazia();
}

//insere o pacote passado em uma seção específica do armazém
void Armazem::armazenaPacote(Pacote* item, int posSecao)
{
    secoes[posSecao].principal.Empilha(item);
}

//retorna o tamanho da pilha principal de uma determinada seção
int Armazem::tamSecaoPrincipal(int posSecao)
{
    return secoes[posSecao].principal.getTam();
}

//retorna o tamanho da pilha auxiliar de uma determinada seção
int Armazem::tamSecaoAux(int posSecao)
{
    return secoes[posSecao].auxiliar.getTam();
}

//retira pacotes da pilha principal na serção correspondente
Pacote* Armazem::esvaziaPrincipal(int posSecao)
{
    Pacote* aux = secoes[posSecao].principal.Desempilha();
    secoes[posSecao].auxiliar.Empilha(aux); 
    return aux;
}

//retira pacotes da pilha auxiliar para o transporte
Pacote* Armazem::carregaTransporte(int capacidade, int destino, int posSecao)
{
    return secoes[posSecao].auxiliar.Desempilha();
}

//passa os pacotes que não puderam ser transportados de volta para a pilha principal
Pacote* Armazem::retornaPrincipal(int posSecao)
{
    Pacote* aux = secoes[posSecao].auxiliar.Desempilha();
    secoes[posSecao].principal.Empilha(aux);
    return aux;
}