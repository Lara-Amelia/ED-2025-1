#ifndef INDICECLI_HPP
#define INDICECLI_HPP

#include "evento.hpp"
#include "arvoreAVL.hpp"
#include <string>

//arquivo contendo o indice do cliente e a AVL que o utilizará
//não é necessário criar uma nova árvore para o índice de pacotes dentro do índice de clientes
//podemos apenas utilizar um vetor ou algo do tipo para armazenar os índices, que serão, por sua vez,
//outra estrutura separada

//a quantidade de linhas em uma saída de consulta de clientes é
//o número de pacotes associados ao cliente multiplicador por 2 (1 linha para registros e 1 para últimos estados)

//os clientes estarão em uma AVL (de clientes) e cada nó terá sua própria AVL, com os pacotes associados 

class infoPacotes
{
    private: 
    int idPac;
    //fazemos "ponteiro indiretos", armazenando as posições dos elementos no vetor principal de eventos
    //terá de haver um mecanismo na main que acompanhe o tamanho atual do vetor e atualize este item e outros com base nele
    int inicio; //armazena um ponteiro para o evento de registro do pacote
    int fim; //armazena um ponteiro para o último evento associado ao pacote
    //utilizar os índices é válido, já que não fazemos remoções no vetor de eventos e ele é "naturalmente" ordenado pelo tempo

    public:
    infoPacotes();
    infoPacotes(int id, int in, int f);

    int getIdPac();
    void setIdPac(int n);

    int getInicio();
    void setInicio(int comeco);

    //sempre que identificamos um novo evento para um pacote, devemos atualizar
    //o ponteiro para fim
    int getFim();
    void setFim(int novoFim);
};

//a arvore com nós indiceCli será instanciada na main
class indiceCli
{
    private: 
    //chave na árvore
    std::string nomeCli;
    //árvore com indice de pacotes
    //inicializada pelo construtor padrão automaticamente
    
    //deve ser incrementado sempre que inserimos um novo pacote associado ao cliente 
    //será utilizado para alocar o vetor que armazenará os dados coletados do índice de eventos
    int nroPacotes;

    public:
    indiceCli();
    indiceCli(std::string nome);
    arvoreAVL<int, infoPacotes*> pacotes;

    void incNroPacs(int n);


    ~indiceCli();

    //será chamado para alocar um vetor do tamanho correto para armazenar as informações
    int getNroPacotes();
    //recebe infos de um pacote e o adiciona na AVL do cliente
    bool addPacote(int idPacote, int indiceInicio, int indiceFim);

    std::string getNomeCli();

    //atualiza o "ponteiro" fim caso seja registrado um novo evento para o pacote
    //será necessário percorrer a AVL interna buscando o pacote desejado e, após encontrá-lo,
    //alterar o valor de seu ponteiro fim utilizando algum dos outros métodos (provavelmente setter)
    bool mudaPacote(int idPacote, int indiceFim);

    //pega as informações de um pacote específico
    //provavelmente não será necessário - podemos apenas percorrer a árvore in-order para
    //obter as infos de pacotes na ordem correta
    infoPacotes* getInfoPacote(int idPacote);

    //podemos adicionar um contador que registra quantos pacotes foram associados ao cliente até o momento, 
    //de forma que passamos um vetor com esse tamanho na chamada de função para armazenar as informações 
    //dos pacotes através do percorrimento da AVL 
    //aparentemente a AVL de pacotes é organizada/impressa pelo tempo e não pelos ids dos pacotes


};

#endif