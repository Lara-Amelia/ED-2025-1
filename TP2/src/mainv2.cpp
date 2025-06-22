#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <limits>
#include <cctype>
#include <iomanip>
#include <chrono>

#include "pacote.hpp"
#include "armazem.hpp"
#include "transporte.hpp"
#include "escalonador.hpp"

int main(int argc, char** argv)
{
    int relogioSimulacao = 0; //relógio da simulação
    try
    {
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

        std::string linha; 
        int capacidadeTransp, latenciaTransp, intervaloTransp, custoRemocao, nroArmazens;
        
        //faz a leitura das linhas com dados sobre o arquivo 
        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> capacidadeTransp;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor capacidade de transporte");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> latenciaTransp;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor latência de transporte");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> intervaloTransp;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor intervalo de transporte");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> custoRemocao;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor custo de remoção");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> nroArmazens;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor número de armazéns");

        //cria uma instância de transporte, que é o representante do grafo de armazéns
        Transporte transporte(capacidadeTransp, latenciaTransp, intervaloTransp, nroArmazens);

        int matrizAdj[nroArmazens][nroArmazens];
        Armazem armazens[nroArmazens];

        //insere a nroArmazens qt. de vértices no grafo e inicializa um vetor de armazéns
        for(int i = 0; i < nroArmazens; i++)
        {
            transporte.InsereVertice();
        }

        std::string linha_matriz; //variável para ler cada linha da matriz
        
        for (int i = 0; i < nroArmazens; ++i) 
        {
            if (!std::getline(arquivo, linha_matriz)) 
            {
                throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " ausente na matriz de adjacência.");
            }

            std::stringstream ss(linha_matriz);
            int valor_celula;
            int col_count = 0;
            int qtAdj = 0;

            armazens[i].setArmazem(nroArmazens, i, custoRemocao);

            while (ss >> valor_celula) 
            {
                if (col_count >= nroArmazens) 
                {
                    throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " possui mais colunas do que o esperado (" + std::to_string(nroArmazens) + ").");
                }

                if (valor_celula == 1) 
                {
                    armazens[i].setVizinho(col_count, qtAdj);
                    armazens[i].setDestinoSecao(col_count, qtAdj);
                    qtAdj++;
                    transporte.InsereAresta(i, col_count);
                    matrizAdj[i][col_count] = 1;
                }
                else
                {
                    matrizAdj[i][col_count] = 0;
                }
                col_count++;
            }
            
            if (col_count < nroArmazens) 
            {
                throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " possui menos colunas do que o esperado (" + std::to_string(nroArmazens) + ").");
            }
        }
        int numeroPacotes;
        arquivo >> numeroPacotes;
        
        //consumir a quebra de linha pendente após a leitura de numeroPacotes
        arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        //cria um vetor com os pacotes inseridos no sistema
        Pacote pacotes[numeroPacotes]; 

        //variavel que contará quantos pacotes ainda estão no sistema
        //deve ser decrementada sempre que marcamos um pacote como "entregue", o que indica que ele saiu do sistema
        int tamPacotes = numeroPacotes;
        
        auto start1 = std::chrono::high_resolution_clock::now();

        Heap escalonador(500);
        escalonador.setMaxSize(500);

        for (int k = 0; k < numeroPacotes; ++k) 
        { 
            //loop para ler cada linha de pacote 
            std::string linha;
            if (!std::getline(arquivo, linha)) 
            {
                throw std::runtime_error("ERRO: linhas com infos. de pacotes insuficientes");
            }

            std::stringstream ss_pacote(linha);
            int tempoChegada, idPacote, armazemInicial, armazemFinal;
            std::string dummy_pac, dummy_org, dummy_dst; //para ler as strings "pac", "org", "dst" 

            //lê os detalhes do pacote conforme o formato 
            ss_pacote >> tempoChegada >> dummy_pac >> idPacote >> dummy_org >> armazemInicial >> dummy_dst >> armazemFinal;

            pacotes[k].setDados(k, tempoChegada, armazemInicial, armazemFinal, 1);
            
            if(k == 0) 
            {
                relogioSimulacao = tempoChegada;
            }
            else 
            {
                if(tempoChegada < relogioSimulacao) 
                {
                    relogioSimulacao = tempoChegada;
                }
            }
            //calcula e armazena a rota do pacote usando BFS no grafo de transporte 
            transporte.buscaLargura(armazemInicial, armazemFinal, pacotes[k].rota);
            pacotes[k].setArmAtual(armazemInicial);     
        }
        arquivo.close();

        for(int i = 0; i < nroArmazens; i++)
        {
            for(int j = 0; j < nroArmazens; j++)
            {
                if(matrizAdj[i][j] == 1)
                {
                    Evento* novoEvento = new Evento;
                    std::string chaveEvento = Evento::construirChaveTransporte(relogioSimulacao + intervaloTransp, i, j);
                    novoEvento->setEvento(chaveEvento, 2, 3, relogioSimulacao + intervaloTransp, -1, i, j, nullptr);
                    escalonador.Inserir(novoEvento);
                }
            }
        }

        //escalona os primeiros eventos de chegada de pacotes
        for(int i = 0; i < numeroPacotes; i++)
        {
            std::string chaveEvento = Evento::construirChavePacote(pacotes[i].getHora(), pacotes[i].getId());
            Evento* novoEvento = new Evento;
            novoEvento->setEvento(chaveEvento, 1, 1, pacotes[i].getHora(), i, pacotes[i].getArmOrigem(), pacotes[i].getArmDestino(), &pacotes[i]);
            escalonador.Inserir(novoEvento);
            pacotes[i].setArmAtual(pacotes[i].getArmOrigem());            
        }

        //condição de parada falsa quando não há mais eventos ou todos os pacotes já foram entregue
        while((!escalonador.Vazio()) && (tamPacotes > 0))
        {
            //obtem as informações sobre o evento retirado do escalonador
            Evento* proximoEvento = escalonador.Remover();
            relogioSimulacao = proximoEvento->getTempoInicio();
            int tipoEvento = proximoEvento->getTipoEvento();
            Pacote* pacoteEvento = proximoEvento->getPacotePtr();

            //se o evento for um transporte
            if(tipoEvento == 2)
            {
                //extrai as informações sobre o evento de transporte processado
                int tempoInicio = relogioSimulacao;
                int origem = proximoEvento->getArmazemOrigem();
                int destino = proximoEvento->getArmazemDestino();
                int posSecao = armazens[origem].encontraSecao(destino); 

                //se a seção correspondente não estiver vazia
                if(!armazens[origem].checaVazia(posSecao))
                {
                    //passa todos os pacotes da pilha principal para a auxiliar
                    while(!armazens[origem].checaVazia(posSecao))
                    {
                        Pacote* aux = armazens[origem].esvaziaPrincipal(posSecao);
                        relogioSimulacao =  relogioSimulacao + custoRemocao;
                        std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                  << aux->getId() << " removido de " << std::setw(3) << origem << " na secao " 
                                  << std::setw(3) << destino << std::endl;
                    }

                    //coloca a quantidade possível de pacotes no transporte
                    for(int i = 0; i < capacidadeTransp; i++)
                    {
                        if(armazens[origem].checaVaziaAux(posSecao)) 
                        {
                            break; 
                        }

                        Pacote* aux = armazens[origem].carregaTransporte(capacidadeTransp, destino, posSecao);
                        aux->setArmAtual(destino);
                        int proxRota = aux->getProximoRota();

                        //gera evento de chegada no próximo armazém para o pacote transportado
                        Evento* novoEvento = new Evento;
                        int tempoEvento = relogioSimulacao + latenciaTransp;
                        std::string chaveEvento = Evento::construirChavePacote(tempoEvento, aux->getId());
                        novoEvento->setEvento(chaveEvento, 1, 3, tempoEvento, aux->getId(), origem, proxRota, aux);
                        escalonador.Inserir(novoEvento);

                        std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                  << aux->getId() << " em transito de " << std::setw(3) << origem 
                                  << " para " << std::setw(3) << destino << std::endl;
                    }

                    //se a auxiliar não tiver ficado vazia, retira os pacotes nela e os retorna para a principal
                    if(!armazens[origem].checaVaziaAux(posSecao))
                    {
                        while(!armazens[origem].checaVaziaAux(posSecao))
                        {
                            Pacote* aux = armazens[origem].retornaPrincipal(posSecao);
                            std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                      << aux->getId() << " rearmazenado em " << std::setw(3) << origem
                                      << " na secao " << std::setw(3) << destino << std::endl;
                        }
                    }
                }

                //escalona o próximo evento de transporte do par origem - destino
                Evento* novoEvento = new Evento;
                int tempoEvento = tempoInicio + intervaloTransp;
                std::string chaveEvento = Evento::construirChaveTransporte(tempoEvento, origem, destino);
                novoEvento->setEvento(chaveEvento, 2, 3, tempoEvento, -1, origem, destino, pacoteEvento);
                escalonador.Inserir(novoEvento);
            }

            //se o evento é de pacote
            else if(tipoEvento == 1)
            {
                //se chegou no fim da rota/foi entregue
                if(proximoEvento->getArmazemOrigem() == pacoteEvento->getArmDestino() || (pacoteEvento->getProximoRota() == -1))
                {
                    std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                              << proximoEvento->getIdPacote() << " entregue em " << std::setw(3) << pacoteEvento->getArmDestino() << std::endl;
                    
                    //indica que o novo estado do pacote é entregue
                    pacoteEvento->setEstadoAtual(5);
                    tamPacotes--;
                }

                else
                {
                    //obtem informações sobre o evento de pacote processado
                    int armazemAtual = pacoteEvento->getArmAtual();
                    int armazemSeguinte = pacoteEvento->getProximoRota();
                    int posicaoSecao = armazens[armazemAtual].encontraSecao(armazemSeguinte);
                   
                    //MUDAR ESTADO DO PACOTE PARA 3
                    //armazena na secao correta do armazem atual
                    armazens[armazemAtual].armazenaPacote((pacoteEvento), posicaoSecao);
                    std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                              << proximoEvento->getIdPacote() << " armazenado em " << std::setw(3) << armazemAtual
                              << " na secao " << std::setw(3) << armazemSeguinte << std::endl;
                }
            }
            delete proximoEvento;
        }
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        std::cout << "Execution time: " << duration1.count() << " seconds" << std::endl;
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
        std::cout << "Execution time: " << duration_ms.count() << " ms" << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}