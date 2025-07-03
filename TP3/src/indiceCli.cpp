#include "indiceCli.hpp"
#include "evento.hpp"
#include "arvoreAVL.hpp"

infoPacotes::infoPacotes()
{
    idPac = -1;
    inicio = -1;
    fim = -1;
}

infoPacotes::infoPacotes(int id, int in, int fim)
{
    idPac = id;
    inicio = in;
    fim = fim;
}

int infoPacotes::getIdPac()
{
    return idPac;
}

//provavelmnet nem será necessário
void infoPacotes::setIdPac(int n)
{
    idPac = n;
}

int infoPacotes::getInicio()
{
    return inicio;
}

void infoPacotes::setInicio(int comeco)
{
    inicio = comeco;
}

int infoPacotes::getFim()
{
    return fim;
}

void infoPacotes::setFim(int fim)
{
    fim = fim;
}

indiceCli::indiceCli()
{
    nomeCli = "";
    nroPacotes = 0;
}

/*
indiceCli::~indiceCli()
{
    int qtd = nroPacotes;
    infoPacotes** vetor = new infoPacotes*[qtd];
    int idx = 0;
    pacotes.inOrderTraversal(vetor, idx);  // usa a versão modificada da AVL
    for (int i = 0; i < idx; i++) 
    {
        delete vetor[i];
    }
    delete[] vetor;
}*/

indiceCli::indiceCli(std::string nome)
{
    nomeCli = nome;
    nroPacotes = 0;
}

int indiceCli::getNroPacotes()
{
    return nroPacotes;
}

bool indiceCli::addPacote(int idPacote, int indiceInicio, int indiceFim)
{
    //se o pacote que desejamos adicionar já foi adicionado
    //talvez utilizar tratamento de exceções oa invés de apenas retornar falso
    if (pacotes.existe(idPacote)) return false;

    infoPacotes* novo = new infoPacotes();
    novo->setIdPac(idPacote);
    novo->setInicio(indiceInicio);  // usamos diretamente os índices aqui
    novo->setFim(indiceFim);

    pacotes.insere(idPacote, novo);
    nroPacotes++;
    return true;
}

//a cada vez que inserimos um novo evento, temos de checar onde o pacote associado está (em termos de clientes)
//e atualizar o atributo fim do índice de pacotes do cliente
//já sabemos em quais clientes as atualizações devem ocorrer devido aos atributos de remetente e destinatário do pacote
//para fazer essa atualização, temos, antes, de realizar a busca no índice de clientes pelos clientes desejados
//isso será feito na main, que é onde iremos instanciar a avl com índice de clientes
bool indiceCli::mudaPacote(int idPacote, int indiceFim)
{
    //talvez alterar para tratamento de exceções ao invés de apenas retornar verdadeiro ou falso
    infoPacotes* pacote = pacotes.busca(idPacote);
    if (!pacote) return false;

    pacote->setFim(indiceFim);
    return true;
}

void indiceCli::incNroPacs(int n)
{
    nroPacotes += n;
}

std::string indiceCli::getNomeCli()
{
    return nomeCli;
}