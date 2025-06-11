#include "armazem.hpp"
#include "pilha.hpp"
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

//a seção passada será acessada no vetor secoes utilizando o índice fornecido pelo método encontraSecao
//para qualquer operação similar, essa será a abordagem empregada
void Armazem::armazenaPacote(Pacote item, Secao secao)
{
    //insere o pacote na pilha principal da seção correspondente
    secao.principal.Empilha(item);
    //antes deste tipo de mensagem, também temos de imprimir o tempo em que ocorreu
    //provavelmente faremos isso no próprio escalonador
    std::cout << "pacote " << item.getId() << " armazenado em " << idGrafo << " na secao " << secao.destino << std::endl;       
}


void Armazem::esvaziaPrincipal(Secao secao)
{
    //enquanto a pilha principal da secao não estiver vazia
    for(int j = 0; j < secao.principal.getTam(); j++)
    {
        //passa todos os pacotes da pilha principal para a auxiliar
        //registrar o custo de retirada, que será a quantidade de pacotes movidos * custoRemocao
        //o valor de custo remocao deve ser incluído no CLK do sistema
        Pacote aux = secao.principal.Desempilha();
        secao.auxiliar.Empilha(aux);
        //talvez uma variável tempo para imprimir corretamente os tempos
        //o transporte só pode ocorrer após essa remoção
        std::cout << "pacote " << aux.getId() << " removido de " << this->idGrafo << " na secao " << secao.destino << std::endl;
    }
}

void Armazem::carregaTransporte(int capacidade, int destino, Secao secao)
{
    while(capacidade > 0)
    {
        Pacote aux = secao.auxiliar.Desempilha();
        capacidade--;
        //nesse método também devemos atualizar o estado do pacote
        std::cout << "pacote " << aux.getId() << " em transito de " << this->idGrafo << " para " << secao.destino << std::endl;
    }
}

//passa os pacotes que não puderam ser transportados de volta para a fila principal
void Armazem::retornaPrincipal(Secao secao)
{
    for(int i = 0; i < secao.auxiliar.getTam(); i++)
    {
        Pacote aux = secao.auxiliar.Desempilha();
        secao.principal.Empilha(aux);
        //também devemos alterar o estado do pacote nesse método
        std::cout << "pacote " << aux.getId() << "rearmazenado em " << this->idGrafo << " na secao " << secao.destino << std::endl;
    }
}