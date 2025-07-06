#include "indiceCli.hpp"
#include "evento.hpp"
#include "arvoreAVL.hpp"

//construtor default para a classe infoPacotes
infoPacotes::infoPacotes()
{
    idPac = -1;
    inicio = -1;
    fim = -1;
}

//construtor com parâmetros para a classe infoPacotes
infoPacotes::infoPacotes(int id, int in, int fim)
{
    idPac = id;
    inicio = in;
    fim = fim;
}

//getters para a classe infoPacotes
int infoPacotes::getIdPac()
{
    return idPac;
}

int infoPacotes::getInicio()
{
    return inicio;
}

int infoPacotes::getFim()
{
    return fim;
}

//setters para a classe infoPacotes
void infoPacotes::setIdPac(int n)
{
    idPac = n;
}

void infoPacotes::setInicio(int comeco)
{
    inicio = comeco;
}

void infoPacotes::setFim(int novoFim)
{
    fim = novoFim;
}

//construtor default para a classe indiceCli
indiceCli::indiceCli()
{
    nomeCli = "";
    nroPacotes = 0;
}

//destrutor para a classe indiceCli
indiceCli::~indiceCli()
{
    int qtd = nroPacotes;
    infoPacotes** vetor = new infoPacotes*[qtd];
    int idx = 0;
    pacotes.percorreInOrder(vetor, idx);  // usa a versão modificada da AVL
    for (int i = 0; i < idx; i++) 
    {
        delete vetor[i];
    }
    delete[] vetor;
}

//construtor com parâmetros para a classe indiceCli
indiceCli::indiceCli(std::string nome)
{
    nomeCli = nome;
    nroPacotes = 0;
}

//getters para a classe indiceCli
int indiceCli::getNroPacotes()
{
    return nroPacotes;
}

std::string indiceCli::getNomeCli()
{
    return nomeCli;
}

//adiciona um pacote para um determinado cliente
bool indiceCli::addPacote(int idPacote, int indiceInicio, int indiceFim)
{
    //se o pacote que desejamos adicionar já foi adicionado
    if (pacotes.existe(idPacote)) 
        throw ("ERRO: o pacote ja foi inserido na árvore");

    infoPacotes* novo = new infoPacotes();
    novo->setIdPac(idPacote);
    novo->setInicio(indiceInicio);  // usamos diretamente os índices aqui
    novo->setFim(indiceFim);

    pacotes.insere(idPacote, novo);
    nroPacotes++;
    return true;
}

//encontra um pacote e altera  valor do "ponteiro" fim
bool indiceCli::mudaPacote(int idPacote, int indiceFim)
{
    infoPacotes* pacote = pacotes.busca(idPacote);
    if(pacote == nullptr)
        throw std::out_of_range("ERRO: pacote não encontrado na busca");

    pacote->setFim(indiceFim);
    return true;
}

//atualiza o "ponteiro" fim de um pacote quando é detectado um novo evento
//como o índice de clientes é instanciado na main, o passamos por parâmetro para o método
void indiceCli::atualizaFim(std::string nomeAtt, arvoreAVL<std::string, indiceCli*>& clientes, int idPac, int indexFim)
{
    indiceCli* clienteBusca = clientes.busca(nomeAtt);

    if(clienteBusca == nullptr)
    {
        throw std::out_of_range("ERRO: cliente" + nomeAtt + "não encontrado na árvore para atualização");
    }
    else
    {
        clienteBusca->mudaPacote(idPac, indexFim);
    }
}