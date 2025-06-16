#include "armazem.hpp"
#include "pilha.hpp"
#include "evento.hpp"
#include <iostream>

Secao::Secao()
{
    //o cosntrutor default das pilhas é chamado automaticamente
    destino = -1; //flag para destino ainda não definido
}

Secao::Secao(int dest)
{
    destino = dest;
}

void Secao::setDestino(int n)
{
    destino = n;
}

Armazem::Armazem()
{
    secoes = nullptr;
    vizinhos = nullptr;
    nroAdj = 0;
    idGrafo = 0;
    custoRemocao = 0;
}

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

Armazem::Armazem(int nAdj, int idG, int custo)
{
    nroAdj = nAdj;
    idGrafo = idG;
    secoes = new Secao[nAdj];
    vizinhos = new int[nAdj];
    custoRemocao = custo;
}

Armazem::~Armazem()
{
    delete[] secoes;
    delete[] vizinhos;
}

void Armazem::setVizinho(int vizinho, int posicao)
{
    if (posicao >= 0 && posicao < nroAdj) 
    {
        vizinhos[posicao] = vizinho;
    } 
    else 
    {
        // Talvez lançar uma exceção ou mensagem de erro
        throw std::out_of_range("Posição inválida em setVizinho");
    }
}

void Armazem::setDestinoSecao(int destino, int posicao)
{
    secoes[posicao].destino = destino;
}

int Armazem::encontraSecao(int destino)
{
    for(int i = 0; i < nroAdj; i++)
    {
        if(this->secoes[i].destino == destino)
            return i;
    }
    //throw "ERRO: secao não encontrada no armazém"   
    //solução temporária para evitar erros de compilação. assim que tivermos a estrutura correta
    //e soubermos onde o método será chamado para incluirmos o catch correspondente, implementaremos
    //o tratamento de exceções utilizando try-throw-catch
    return -1; 
}

bool Armazem::checaVazia(int posSecao)
{
    return secoes[posSecao].principal.Vazia();
}

bool Armazem::checaVaziaAux(int posSecao)
{
    return secoes[posSecao].auxiliar.Vazia();
}

//a seção passada será acessada no vetor secoes utilizando o índice fornecido pelo método encontraSecao
//para qualquer operação similar, essa será a abordagem empregada
void Armazem::armazenaPacote(Pacote item, int posSecao)
{
    secoes[posSecao].principal.Empilha(item);
    //insere o pacote na pilha principal da seção correspondente
    //secao.principal.Empilha(item);
    //antes deste tipo de mensagem, também temos de imprimir o tempo em que ocorreu
    //provavelmente faremos isso no próprio escalonador
    //std::cout << "pacote " << item.getId() << " armazenado em " << idGrafo << " na secao " << secao.destino << std::endl;       
}

int Armazem::tamSecaoPrincipal(int posSecao)
{
    return secoes[posSecao].principal.getTam();
}

int Armazem::tamSecaoAux(int posSecao)
{
    return secoes[posSecao].auxiliar.getTam();
}

void Armazem::esvaziaPrincipal(int posSecao)
{
    //enquanto a pilha principal da secao não estiver vazia
    //for(int j = 0; j < secoes[posSecao].principal.getTam(); j++)
    //{
        //passa todos os pacotes da pilha principal para a auxiliar
        //registrar o custo de retirada, que será a quantidade de pacotes movidos * custoRemocao
        //o valor de custo remocao deve ser incluído no CLK do sistema
        Pacote aux = secoes[posSecao].principal.Desempilha();
        secoes[posSecao].auxiliar.Empilha(aux);
        //talvez uma variável tempo para imprimir corretamente os tempos
        //o transporte só pode ocorrer após essa remoção
        //std::cout << "pacote " << aux.getId() << " removido de " << this->idGrafo << " na secao " << secao.destino << std::endl;
    //}
}

Pacote Armazem::carregaTransporte(int capacidade, int destino, int posSecao)
{
    //while(capacidade > 0)
    //{
        return secoes[posSecao].auxiliar.Desempilha();
        //capacidade--;
        //nesse método também devemos atualizar o estado do pacote
        //std::cout << "pacote " << aux.getId() << " em transito de " << this->idGrafo << " para " << secao.destino << std::endl;
    //}
}

//passa os pacotes que não puderam ser transportados de volta para a fila principal
Pacote Armazem::retornaPrincipal(int posSecao)
{
    //for(int i = 0; i < secoes[posSecao].auxiliar.getTam(); i++)
    //{
        Pacote aux = secoes[posSecao].auxiliar.Desempilha();
        secoes[posSecao].principal.Empilha(aux);
        return aux;
        //também devemos alterar o estado do pacote nesse método
        //std::cout << "pacote " << aux.getId() << "rearmazenado em " << this->idGrafo << " na secao " << secao.destino << std::endl;
    //}
}