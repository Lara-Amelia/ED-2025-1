#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include "evento.hpp"
#include "indiceCli.hpp"
#include "arvoreAVL.hpp"

int main(void)
{
    try
    {
        std::cout << "Digite o nome do arquivo de entrada: " << std::endl;
        std::string nomeArquivo;
        std::cin >> nomeArquivo;

        std::ifstream arquivo(nomeArquivo);
        if(!arquivo.is_open())
        {
            throw std::runtime_error("ERRO: não foi possível abrir o arquivo " + nomeArquivo);
        }

        //vetor de strings que armazenará as infos lidas do arquivo de entrada
        //serão colocadas no vetor e depois lidas sequencialmente, para facilitar consultas e 
        //reduzir o tempo gasto com operações de i/o em memória secundária
        std::string linhas[500];
        int nroLinhas = 0;
        std::string linha;

        while (std::getline(arquivo, linha) && nroLinhas < 500)   
        {
            linhas[nroLinhas++] = linha;
        }

        arquivo.close();
        //checando se os eventos foram inseridos corretamente no vetor a ser utilizado
        for (int i = 0; i < nroLinhas; ++i) 
        {
            std::cout << linhas[i] << std::endl;
        }

        arvoreAVL<std::string, indiceCli*> clientes;
        int nroArgs = 0;
        Evento* eventos[nroLinhas];
        int tipoEvento = -1;
        int qtEventos = 0;
        Pacote pacotes[50];
        int nroPacotes = 0;
        //para cada linha no vetor de linhas da entrada, separaremos cada informação presente neles 
        //e as utilizaremos para criar os eventos e inseri-los em um vetor de eventos
        for(int i = 0; i < nroLinhas; i++)
        {
            //faz o parsing das informações, cria eventos de acordo e os insere em um vetor de eventos
            //talvez separar a laitura e parsing, porque aqui todas as ações serão direcionadas 
            //optamos por realizar as inserções e consultas à medida que as infos. do vetor são processadas
            //se for um evento, o inserimos no devido lugar e, se for uma consulta, fazemos as ações necessárias para tanto
            //inicialmente, faremos as ações de consultas por clientes
            std::istringstream iss(linhas[i]);
            std::string token;
            std::string partes[8];
            int idx = 0;   

            //fazemos o parsing de todas as informações da linha
            while (iss >> token && idx < 8) 
            {
                partes[idx++] = token;
            }

            if(partes[2] == "RG")
            {
                tipoEvento = 1;
            }
            else if(partes[2] == "AR")
            {
                tipoEvento = 2;
            }
            else if(partes[2] == "RM")
            {
                tipoEvento = 3;
            }
            else if(partes[2] == "UR")
            {
                tipoEvento = 4;
            }
            else if(partes[2] == "TR")
            {
                tipoEvento = 5;
            }
            else if(partes[2] == "EN")
            {
                tipoEvento = 6;
            }

            //se a linha lida é de evento
            if(partes[1] == "EV")
            {
                qtEventos++;
                switch (tipoEvento)
                {
                    //se o evento for registro
                    case 1:
                    {
                        nroPacotes++;
                        int tempo = std::stoi(partes[0]);
                        std::cout << "tempo evento " << i << ": " << tempo << std::endl;
                        int idPac = std::stoi(partes[3]);
                        //partes[3] = remetente e partes[4] = destinatário
                        int origem = std::stoi(partes[6]);
                        int destino = std::stoi(partes[7]);
                        //FACILITAR A ATUALIZAÇÃO DE ULTIMO ESTADO DE PACOTES ASSOCIADOS A CLIENTES
                        pacotes[nroPacotes - 1].setPacote(idPac, partes[4], partes[5]);
                        Evento* novoEvento = new Evento(tempo, 1, idPac, partes[4], partes[5], origem, destino);
                        eventos[qtEventos-1] = novoEvento;
                        //PRIMEIRO ADICIONAR UMA CHECAGEM SE OS NOMES JÁ EXISTEM NA ÁRVORE DE ÍNDICES
                        //se o cliente ainda não existe na árvore, cria um novo e o insere
                        if(!clientes.existe(partes[4]))
                        {
                            indiceCli* novoCli1 = new indiceCli(partes[4]);
                            novoCli1->addPacote(idPac, qtEventos-1, qtEventos-1);
                            std::cout << "nome cliente add partes[4]: " << novoCli1->getNomeCli() << std::endl;
                            //novoCli1->incNroPacs(1);
                            clientes.insere(partes[4], novoCli1);
                        }    
                        //se o cliente já existe na árvore
                        else
                        {
                            indiceCli* mudaCli = clientes.busca(partes[4]);
                            std::cout << "nome dliente muda partes[4]: " << mudaCli->getNomeCli() << std::endl;
                            mudaCli->addPacote(idPac, qtEventos-1, qtEventos-1);
                            //mudaCli->incNroPacs(1);
                        }

                        //início e fim são os mesmos porque acabamos de adicionar o pacote
                        //ainda não há outros eventos associados a ele
                        //se o destinatário ainda não existe
                        if(!clientes.existe(partes[5]))
                        {
                            indiceCli* novoCli1 = new indiceCli(partes[5]);
                            novoCli1->addPacote(idPac, qtEventos-1, qtEventos-1);
                            std::cout << "nome cliente add partes[5]: " << novoCli1->getNomeCli() << std::endl;
                            //novoCli1->incNroPacs(1);
                            clientes.insere(partes[5], novoCli1);
                        }
                        else
                        {
                            indiceCli* mudaCli = clientes.busca(partes[5]);
                            std::cout << "nome cliente muda partes[5]: " << mudaCli->getNomeCli() << std::endl;
                            mudaCli->addPacote(idPac, qtEventos-1, qtEventos-1);
                            //mudaCli->incNroPacs(1);
                        }
                        //TAMBÉM TEMOS DE ADICIONAR A LÓGICA PARA INSERÇÃO DO EVENTO NOS DEMAIS ÍNDICES
                    }
                    break;
                    //evento de armazenamento
                    case 2:
                    {
                        int tempo = std::stoi(partes[0]);
                        int idPac = std::stoi(partes[3]);
                        int armDest = std::stoi(partes[4]);
                        int secaoDest = std::stoi(partes[5]);
                        Evento* novoEvento = new Evento(tempo, 2, idPac, armDest, secaoDest);
                        eventos[qtEventos - 1] = novoEvento;
                        
                        //atualiza o ponteiro fim dos pacotes nos clientes associados
                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli* cliente1 = clientes.busca(nome1);
                        indiceCli* cliente2 = clientes.busca(nome2);

                        cliente1->mudaPacote(idPac, qtEventos-1);
                        cliente2->mudaPacote(idPac, qtEventos-1);
                    }    
                    break;
                    case 3:
                    {
                        int tempo = std::stoi(partes[0]);
                        int idPac = std::stoi(partes[3]);
                        int armDest = std::stoi(partes[4]);
                        int secaoDest = std::stoi(partes[5]);
                        Evento* novoEvento = new Evento(tempo, 3, idPac, armDest, secaoDest);
                        eventos[qtEventos - 1] = novoEvento;

                        //atualiza o ponteiro fim dos pacotes nos clientes associados
                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli* cliente1 = clientes.busca(nome1);
                        indiceCli* cliente2 = clientes.busca(nome2);

                        cliente1->mudaPacote(idPac, qtEventos-1);
                        cliente2->mudaPacote(idPac, qtEventos-1);
                    }
                    break;
                    case 4:
                    {
                        //extrai infos do evento lido
                        int tempo = std::stoi(partes[0]);
                        int idPac = std::stoi(partes[3]);
                        int armDest = std::stoi(partes[4]);
                        int secaoDest = std::stoi(partes[5]);
                        //cria um novo evento e o insere no vetor principal de eventos
                        Evento* novoEvento = new Evento(tempo, 4, idPac, armDest, secaoDest);
                        eventos[qtEventos - 1] = novoEvento;

                        //atualiza o ponteiro fim dos pacotes nos clientes associados
                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli* cliente1 = clientes.busca(nome1);
                        indiceCli* cliente2 = clientes.busca(nome2);

                        cliente1->mudaPacote(idPac, qtEventos-1);
                        cliente2->mudaPacote(idPac, qtEventos-1);
                    }
                    break;
                    //evento de transporte
                    case 5:
                    {
                        int tempo = std::stoi(partes[0]);
                        int idPac = std::stoi(partes[3]);
                        int origem = std::stoi(partes[4]);
                        int destino = std::stoi(partes[5]);

                        Evento* novoEvento = new Evento(tempo, 5, idPac, origem, destino);
                        eventos[qtEventos - 1] = novoEvento;

                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli* cliente1 = clientes.busca(nome1);
                        indiceCli* cliente2 = clientes.busca(nome2);

                        cliente1->mudaPacote(idPac, qtEventos-1);
                        cliente2->mudaPacote(idPac, qtEventos-1);
                    }
                    break;
                    case 6:
                    {

                    }
                    break;
                    default:
                        break;
                }
            }
            //se for uma pesquisa por cliente
            else if(partes[1] == "CL")
            {
                std::string nomeCli = partes[2];
                indiceCli* cliBusca = clientes.busca(nomeCli);
                //se o cliente buscado não existe
                if(cliBusca == nullptr)
                {
                    std::cout << partes[0] << " " << partes[1] << " " << partes[2] << std::endl;
                    std::cout << "0" << std::endl;
                }
                else
                {
                    //std::cout << cliBusca->getNomeCli();
                    //cria um vetor de infoPacotes para armazenar os resultados obtidos ao percorrer a árvore
                    int nroPacotesCli = cliBusca->getNroPacotes();
                    infoPacotes** packages = new infoPacotes*[nroPacotesCli];
                    int tam = 0;
                    //obtem infos de todos os pacotes associados, ordenando pelo índice dos pacotes
                    cliBusca->pacotes.inOrderTraversal(packages, tam);
                    //imrpime a consulta sendo realizada
                    std::cout << partes[0] << " " << partes[1] << " " << partes[2] << std::endl;
                    //imprime o número de linhas no resultado da consulta
                    std::cout << nroPacotesCli*2 << std::endl;
                    //imrprime as infos iniciais dos pacotes 
                    for(int i = 0; i < nroPacotesCli; i++)
                    {
                        int indexInicio = packages[i]->getInicio();
                        //std::cout << "início " << indexInicio << std::endl;
                        //int indexFim = packages[i]->getFim();
                        //std::cout << "fim " << indexFim << std::endl;
                        //NÃO PODEMOS IMPRIMIR DIRETAMENTE A LINHA PORQUE HÁ LINHAS DE CONSULTAS
                        std::cout << std::setfill('0') << std::setw(7) << eventos[indexInicio]->getTempo() << " EV RG " << std::setw(3) << eventos[indexInicio]->getId() <<
                              " " << eventos[indexInicio]->getRemetente() << " " << eventos[indexInicio]->getDestinatario() << " " 
                                  << std::setw(3) << eventos[indexInicio]->getOrigem() << " " << std::setw(3) << eventos[indexInicio]->getDestino() << std::endl;
                        //std::cout<<linhas[indexInicio] << std::endl;
                    }
                    //TLAVEZ SEJA NECESSARIO ORDENAR O VETOR PELO TEMPO PARA OBTER A SAÍDA DESEJADA
                    for(int i = 0; i < nroPacotesCli; i++)
                    {
                        int indexFim = packages[i]->getFim();
                        //std::cout << indexFim << std::endl;
                        int tipo = eventos[indexFim]->getTipo();
                        //std::cout << tipo << std::endl;
                        //MODULARIZAR EM GERADOR DE RESPOSTAS NA CLASSE EVENTO
                        if(tipo == 1)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV RG " << std::setw(3) << eventos[indexFim]->getId() <<
                              " " << eventos[indexFim]->getRemetente() << " " << eventos[indexFim]->getDestinatario() << " " 
                                  << std::setw(3) << eventos[indexFim]->getOrigem() << " " << std::setw(3) << eventos[indexFim]->getDestino() << std::endl;
                        }
                        else if(tipo == 2)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV AR " << std::setw(3) << eventos[indexFim]->getId() <<
                                  " " << std::setw(3) << eventos[indexFim]->getDestino() << " " << std::setw(3) << eventos[indexFim]->getSecao() << std::endl;
                        }
                        else if(tipo == 3)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV RM " << std::setw(3) << eventos[indexFim]->getId() <<
                                  " " << std::setw(3) << eventos[indexFim]->getDestino() << " " << std::setw(3) << eventos[indexFim]->getSecao() << std::endl;
                        }
                        else if(tipo == 4)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV UR" << std::setw(3) << eventos[indexFim]->getId() <<
                                  " " << std::setw(3) << eventos[indexFim]->getDestino() << " " << std::setw(3) << eventos[indexFim]->getSecao() << std::endl;
                        }
                        else if(tipo == 5)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV TR " << std::setw(3) << eventos[indexFim]->getId() <<
                                  " " << std::setw(3) << eventos[indexFim]->getOrigem() << " " << std::setw(3) << eventos[indexFim]->getDestino() << std::endl;
                        }
                        else if(tipo == 6)
                        {
                            std::cout << std::setfill('0') << std::setw(7) << eventos[indexFim]->getTempo() << " EV EN " << std::setw(3) << eventos[indexFim]->getId() <<
                                  " " << std::setw(3) << eventos[indexFim]->getDestino() << std::endl;
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}