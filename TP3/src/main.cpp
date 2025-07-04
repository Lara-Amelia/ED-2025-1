#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <exception>
#include <stdexcept>

#include "evento.hpp"
#include "indiceCli.hpp"
#include "arvoreAVL.hpp"
#include "indicePacs.hpp"
#include "indicePacTempo.hpp"

int main(int argc, char** argv)
{
    try
    {
        //std::cout << "Digite o nome do arquivo de entrada: " << std::endl;
        if(argc < 2)
        {
            throw std::invalid_argument("ERRO: o nome do arquivo não foi fornecido na linha de comando");
        }
        std::string nomeArquivo = argv[1];
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
       
        //instancia os índices que serão utilizados e o vetor de eventos
        arvoreAVL<std::string, indiceCli*> clientes;
        indicePacs indexPacs;
        indicePacTempo indexPacTempo;
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

            tipoEvento = Evento::defineTipo(partes[2]);
            
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
                        int idPac = std::stoi(partes[3]);
                        int origem = std::stoi(partes[6]);
                        int destino = std::stoi(partes[7]);

                        pacotes[nroPacotes - 1].setPacote(idPac, partes[4], partes[5]);
                        Evento* novoEvento = new Evento(tempo, 1, idPac, partes[4], partes[5], origem, destino);
                        eventos[qtEventos-1] = novoEvento;
                        
                        //se o cliente ainda não existe na árvore, cria um novo e o insere
                        if(!clientes.existe(partes[4]))
                        {
                            indiceCli* novoCli1 = new indiceCli(partes[4]);
                            novoCli1->addPacote(idPac, qtEventos-1, qtEventos-1);
                            clientes.insere(partes[4], novoCli1);
                        }    

                        //se o cliente já existe na árvore
                        else
                        {
                            indiceCli* mudaCli = clientes.busca(partes[4]);
                            mudaCli->addPacote(idPac, qtEventos-1, qtEventos-1);
                        }

                        //início e fim são os mesmos porque acabamos de adicionar o pacote
                        //ainda não há outros eventos associados a ele

                        //se o destinatário ainda não existe
                        if(!clientes.existe(partes[5]))
                        {
                            indiceCli* novoCli1 = new indiceCli(partes[5]);
                            novoCli1->addPacote(idPac, qtEventos-1, qtEventos-1);
                            clientes.insere(partes[5], novoCli1);
                        }
                        else
                        {
                            indiceCli* mudaCli = clientes.busca(partes[5]);
                            mudaCli->addPacote(idPac, qtEventos-1, qtEventos-1);
                        }
                        
                        indexPacs.registraPacote(idPac, tempo);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento,novoEvento);
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

                        indiceCli::atualizaFim(nome1, clientes, idPac, qtEventos-1);
                        indiceCli::atualizaFim(nome2, clientes, idPac, qtEventos-1);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento, novoEvento);
                    }    
                    break;

                    //evento de remoção
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

                        indiceCli::atualizaFim(nome1, clientes, idPac, qtEventos-1);
                        indiceCli::atualizaFim(nome2, clientes, idPac, qtEventos-1);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento, novoEvento);
                    }
                    break;

                    //evento de rearmazenamento
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

                        indiceCli::atualizaFim(nome1, clientes, idPac, qtEventos-1);
                        indiceCli::atualizaFim(nome2, clientes, idPac, qtEventos-1);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento, novoEvento);
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

                        //atualização de ponteiros fim em clientes
                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli::atualizaFim(nome1, clientes, idPac, qtEventos-1);
                        indiceCli::atualizaFim(nome2, clientes, idPac, qtEventos-1);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento, novoEvento);
                    }
                    break;

                    //evento de entrega
                    case 6:
                    {
                        int tempo = std::stoi(partes[0]);
                        int idPac = std::stoi(partes[3]);
                        int destino = std::stoi(partes[4]);
                        
                        Evento* novoEvento = new Evento(tempo, 6, idPac, destino);
                        eventos[qtEventos - 1] = novoEvento;

                        //atualização de ponteiros fim dos clientes associados ao pacote
                        int indexPac = Pacote::encontraPacote(pacotes, nroPacotes, idPac);
                        std::string nome1 = pacotes[indexPac].getRem();
                        std::string nome2 = pacotes[indexPac].getDest();

                        indiceCli::atualizaFim(nome1, clientes, idPac, qtEventos-1);
                        indiceCli::atualizaFim(nome2, clientes, idPac, qtEventos-1);

                        indexPacTempo.registraEvento(idPac, tempo, tipoEvento, novoEvento);
                    }
                    break;

                    default:
                        throw std::runtime_error("ERRO: tipo inválido de evento");
                    break;
                }
            }

            //se for uma pesquisa por cliente
            else if(partes[1] == "CL")
            {
                //ORDENAR RESULTADOS DOS CLIENTES PELO TEMPO
                int tempo = std::stoi(partes[0]);
                std::string nomeCli = partes[2];
                indiceCli* cliBusca = clientes.busca(nomeCli);
                //se o cliente buscado não existe
                if(cliBusca == nullptr)
                {
                    std::cout << std::setfill('0') << std::setw(6) << tempo << " " << partes[1] << " " << partes[2] << std::endl;
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
                    std::cout << std::setfill('0') << std::setw(6) << tempo << " " << partes[1] << " " << partes[2] << std::endl;
                    //imprime o número de linhas no resultado da consulta
                    std::cout << nroPacotesCli*2 << std::endl;
                    //imrprime as infos iniciais dos pacotes 

                    // Ordena os pacotes pelo tempo de início e, em caso de empate, pelo idPacote
                    for (int i = 1; i < nroPacotesCli; ++i) 
                    {
                        infoPacotes* key = packages[i];
                        int j = i - 1;

                        int tempoKey = eventos[key->getInicio()]->getTempo();
                        int idKey = eventos[key->getInicio()]->getId();

                        while (j >= 0) 
                        {
                            int tempoJ = eventos[packages[j]->getInicio()]->getTempo();
                            int idJ = eventos[packages[j]->getInicio()]->getId();

                            if (tempoJ > tempoKey || (tempoJ == tempoKey && idJ > idKey)) 
                            {
                                packages[j + 1] = packages[j];
                                j--;
                            } 
                            else 
                            {
                                break;
                            }
                        }
                        packages[j + 1] = key;
                    }

                    for(int i = 0; i < nroPacotesCli; i++)
                    {
                        int indexInicio = packages[i]->getInicio();
                        Evento::geraResposta(eventos[indexInicio]);
                    }

                    // Ordena os pacotes pelo tempo de fim e, em caso de empate, pelo idPacote
                    for (int i = 1; i < nroPacotesCli; ++i) 
                    {
                        infoPacotes* key = packages[i];
                        int j = i - 1;

                        int tempoKey = eventos[key->getFim()]->getTempo();
                        int idKey = eventos[key->getFim()]->getId();

                        while (j >= 0) 
                        {
                            int tempoJ = eventos[packages[j]->getFim()]->getTempo();
                            int idJ = eventos[packages[j]->getFim()]->getId();

                            if (tempoJ > tempoKey || (tempoJ == tempoKey && idJ > idKey)) 
                            {
                                packages[j + 1] = packages[j];
                                j--;
                            } 
                            else 
                            {
                                break;
                            }
                        }
                        packages[j + 1] = key;
                    }

                    for(int i = 0; i < nroPacotesCli; i++)
                    {
                        int indexFim = packages[i]->getFim();
                        Evento::geraResposta(eventos[indexFim]);
                    }
                }
            }
            //se for uma pesquisa por pacote
            else if(partes[1] == "PC")
            {
                int idPac = std::stoi(partes[2]);
                //se o pacote com o id desejado existe na árvore
                if(indexPacs.existePac(idPac))
                {
                    //passamos 1 porque os eventos sempre são do tipo 1 registro
                    std::string chaveBusca = indexPacs.geraChaveParaBuscaTempo(idPac, 1);
                    //std::cout << "chave gerada indicePacs: " << chaveBusca << std::endl;
                    int nroEventos = 0;
                    int tempoLim = std::stoi(partes[0]);
                    Evento** eventosPac = new Evento*[500];
                    //indexPacTempo.inOrderPrint(eventosPac, nroEventos);

                    indexPacTempo.eventosDoPacoteAteTempo(chaveBusca, idPac, tempoLim, eventosPac, nroEventos);

                    std::cout << std::setfill('0') << std::setw(6) << tempoLim << " " << partes[1] << " " << partes[2] << std::endl;
                    std::cout << nroEventos << std::endl;

                    // Ordena os eventos do pacote por tempo e, em caso de empate, por idPacote
                    /*for (int i = 1; i < nroEventos; ++i) 
                    {
                        Evento* key = eventosPac[i];
                        int j = i - 1;

                        int tempoKey = key->getTempo();
                        int idKey = key->getId();

                        while (j >= 0) 
                        {
                            int tempoJ = eventosPac[j]->getTempo();
                            int idJ = eventosPac[j]->getId();

                            if (tempoJ > tempoKey || (tempoJ == tempoKey && idJ > idKey)) 
                            {
                                eventosPac[j + 1] = eventosPac[j];
                                j--;
                            } 
                            else 
                            {
                                break;
                            }
                        }
                        eventosPac[j + 1] = key;
                    }*/

                    for(int i = 0; i < nroEventos; i++)
                    {
                        Evento::geraResposta(eventosPac[i]);
                    }
                }
                else
                    throw std::runtime_error("ERRO: pacote não encontrado no índice de pacotes");
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}