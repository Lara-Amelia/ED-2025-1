/*#ifndef INDICECLI_HPP
#define INDICECLI_HPP

#include "evento.hpp"
#include "arvoreAVL.hpp"
#include <string>

//arquivo contendo o indice do cliente e a AVL que o utilizará
//os clientes estarão em uma AVL (de clientes) e cada nó terá sua própria AVL, com os pacotes associados 

//valor que será armazenado no node da árvore do índice
class infoPacotes
{
    private: 
    int idPac;
    //fazemos "ponteiro indiretos", armazenando as posições dos elementos no vetor principal de eventos
    int inicio; //armazena um ponteiro para o evento de registro do pacote
    int fim; //armazena um ponteiro para o último evento associado ao pacote
    
    public:
    infoPacotes();
    infoPacotes(int id, int in, int f);

    int getIdPac();
    void setIdPac(int n);

    int getInicio();
    void setInicio(int comeco);

    int getFim();
    void setFim(int novoFim);
};

//a arvore com nós indiceCli será instanciada na main
class indiceCli
{
    private: 
    int nomeCli;
    //deve ser incrementado sempre que inserimos um novo pacote associado ao cliente 
    //será utilizado para alocar o vetor que armazenará os dados coletados do índice de eventos
    int nroPacotes;

    public:
    indiceCli();
    indiceCli(int nome);
    ~indiceCli();
    arvoreAVL<int, infoPacotes*> pacotes;

    int getNroPacotes();
    int getNomeCli();
    //recebe infos de um pacote e o adiciona na AVL do cliente
    bool addPacote(int idPacote, int indiceInicio, int indiceFim);

    bool mudaPacote(int idPacote, int indiceFim);
    static void atualizaFim(int nomeAtt, arvoreAVL<int, indiceCli*>& clientes, int idPac, int indexFim);
};

#endif*/

#ifndef INDICECLI_HPP
#define INDICECLI_HPP

#include "evento.hpp"
#include "arvoreAVL.hpp"
#include <string>

//arquivo contendo o indice do cliente e a AVL que o utilizará
//os clientes estarão em uma AVL (de clientes) e cada nó terá sua própria AVL, com os pacotes associados 

//valor que será armazenado no node da árvore do índice
class infoPacotes
{
    private: 
    int idPac;
    //fazemos "ponteiro indiretos", armazenando as posições dos elementos no vetor principal de eventos
    int inicio; //armazena um ponteiro para o evento de registro do pacote
    int fim; //armazena um ponteiro para o último evento associado ao pacote
    
    public:
    infoPacotes();
    infoPacotes(int id, int in, int f);

    int getIdPac();
    void setIdPac(int n);

    int getInicio();
    void setInicio(int comeco);

    int getFim();
    void setFim(int novoFim);
};

//a arvore com nós indiceCli será instanciada na main
class indiceCli
{
    private: 
    std::string nomeCli;
    //deve ser incrementado sempre que inserimos um novo pacote associado ao cliente 
    //será utilizado para alocar o vetor que armazenará os dados coletados do índice de eventos
    int nroPacotes;

    public:
    indiceCli();
    indiceCli(std::string nome);
    ~indiceCli();
    arvoreAVL<int, infoPacotes*> pacotes;

    int getNroPacotes();
    std::string getNomeCli();
    //recebe infos de um pacote e o adiciona na AVL do cliente
    bool addPacote(int idPacote, int indiceInicio, int indiceFim);

    bool mudaPacote(int idPacote, int indiceFim);
    static void atualizaFim(std::string nomeAtt, arvoreAVL<std::string, indiceCli*>& clientes, int idPac, int indexFim);
};

#endif