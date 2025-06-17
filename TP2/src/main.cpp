#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <limits>
#include <cctype>
#include <iomanip>

#include "pacote.hpp"
#include "armazem.hpp"
#include "transporte.hpp"
#include "escalonador.hpp"

std::string trimRight(const std::string& s) {
    int end = s.length() - 1;
    while (end >= 0 && std::isspace(s[end])) {
        --end;
    }
    return s.substr(0, end + 1);
}

int main(int argc, char** argv)
{
    int relogioSimulacao = 0; // O relógio da simulação
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
        
        //Faz a leitura das linhas com dados sobre o ordenador do arquivo 
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

        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //cria uma instância de transporte, que é o nosso grafo de armazéns
        Transporte transporte(capacidadeTransp, latenciaTransp, intervaloTransp, nroArmazens);

        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "Parametros Lidos:" << std::endl;
        std::cout << "  Capacidade de Transporte: " << capacidadeTransp << std::endl;
        std::cout << "  Latencia de Transporte: " << latenciaTransp << std::endl;
        std::cout << "  Intervalo entre Transportes: " << intervaloTransp << std::endl;
        std::cout << "  Custo de Remocao: " << custoRemocao << std::endl;
        std::cout << "  Numero de Armazens: " << nroArmazens << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;

        Armazem armazens[nroArmazens];
        //insere a nroArmazens qt. de vértices no grafo e incializa um vetor de ponteiros para armazéns
        for(int i = 0; i < nroArmazens; i++)
        {
            transporte.InsereVertice();
            //armazens[i].setArmazem(nroArmazens, i, custoRemocao);
        }

        std::string linha_matriz; // Variável para ler cada linha da matriz
        
        std::cout << "\nLendo Matriz de Adjacencia..." << std::endl;

        for (int i = 0; i < nroArmazens; ++i) 
        {
            if (!std::getline(arquivo, linha_matriz)) 
            {
                throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " ausente na matriz de adjacência.");
            }

            std::cout << "Linha " << i << ": [" << linha_matriz << "]\n";
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
                }
                col_count++;
            }
            
            //armazens[i].setAdj(qtAdj);
            if (col_count < nroArmazens) 
            {
                throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " possui menos colunas do que o esperado (" + std::to_string(nroArmazens) + ").");
            }
        }
        int numeroPacotes;
        arquivo >> numeroPacotes;
        std::cout << "\nLendo " << numeroPacotes << " Pacotes..." << std::endl;
        // Consumir a quebra de linha pendente após a leitura de numeroPacotes
        arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        Pacote pacotes[numeroPacotes]; 
        //variavel que contará quantos pacotes ainda estão no sistema
        //deve ser decrementada sempre que marcamos um pacote como "entregue", o que indica que ele saiu do sistema
        int tamPacotes = numeroPacotes;
        
        //Heap escalonador(numeroPacotes * 5); // Ex: 5 vezes o num de pacotes para começar
        
        /*for(int i = 0; i < nroArmazens; i++) 
        {
            //transporte.InsereVertice(); // Insere o vértice (ID) no grafo (ListaAdjacencia)
            // Cria o objeto Armazem. O construtor Armazem deve receber nAdj, idG, custo.
            // Para nAdj, podemos usar o grau do vértice 'i' se a matriz já foi lida,
            // ou passar o nroArmazens como um máximo.
            armazens[i] = new Armazem(nroArmazens, i, custoRemocao);
        }*/

        Heap escalonador(200);
        for (int k = 0; k < numeroPacotes; ++k) 
        { 
            // Loop para ler cada linha de pacote 
            std::string linha;
            if (!std::getline(arquivo, linha)) 
            {
                throw std::runtime_error("ERRO: linhas com infos. de pacotes insuficientes");
                //for(int pk = 0; pk < k; ++pk) delete pacotes[pk];
                //delete[] pacotes; 
            }

            std::stringstream ss_pacote(linha);
            int tempoChegada, idPacote, armazemInicial, armazemFinal;
            std::string dummy_pac, dummy_org, dummy_dst; // Para ler as strings "pac", "org", "dst" 

            // Lê os detalhes do pacote conforme o formato (ex: 9 pac 0 org 1 dst 0) 
            ss_pacote >> tempoChegada >> dummy_pac >> idPacote >> dummy_org >> armazemInicial >> dummy_dst >> armazemFinal;

            // Cria a instância do Pacote
            //estado 1 para ainda não postado
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

            // Calcula e armazena a rota do pacote usando BFS no grafo de transporte 
            transporte.buscaLargura(armazemInicial, armazemFinal, pacotes[k].rota);



            //cria os eventos de chegada/postagem dos pacotes no armazém
            std::string chave_evento_chegada = Evento::construirChavePacote(tempoChegada, idPacote); 
            
            Evento* novo_evento = new Evento; 
            novo_evento->setEvento(chave_evento_chegada, 1, 1, tempoChegada, k, armazemInicial, armazemFinal, &pacotes[k]);
            escalonador.Inserir(novo_evento);
            pacotes[k].setArmAtual(armazemInicial);

            std::cout << "  Pacote lido: Tempo=" << tempoChegada << ", ID=" << pacotes[k].getId() << ", Origem=" << armazemInicial << ", Destino=" << armazemFinal << ". Chave: " << chave_evento_chegada << std::endl;
            std::cout << "  Rota calculada para Pacote " << idPacote << ": ";
            pacotes[k].rota.Imprime(); // Imprime a rota do pacote para verificação.
            //delete[] pacotes;

            int tempoTransp = relogioSimulacao + intervaloTransp;
            int destino = pacotes[k].getProximoRota();
            std::string chaveTransporte = Evento::construirChaveTransporte(tempoTransp, armazemInicial, destino);
            Evento* novoTransp = new Evento;
            novoTransp->setEvento(chaveTransporte, 2, 2, tempoTransp, pacotes[k].getId(), armazemInicial, destino, &pacotes[k]);
            escalonador.Inserir(novoTransp);
        }
        arquivo.close();

        std::cout << "\n--- INICIO DA SIMULACAO ---" << std::endl;
        int iteracoes = 1;
        //condição de parada falsa - só será T quando a heap estiver vazia (não há mais eventos)
        //ou enquanto tamPacotes aina não tiver sido zerado, o que indica que nem todos os pacotes foram entregues
        while((/*(!escalonador.Vazio()) ||*/ (tamPacotes > 0)) /*&& (iteracoes <= numeroPacotes)*/)
        {
            //std::cout << "tam. escalonador " << escalonador.getTam() << std::endl;
            if(escalonador.Vazio())
                break;
            Evento* proximoEvento = escalonador.Remover();
            relogioSimulacao = proximoEvento->getTempoInicio();
            //proximoEvento->what();
            iteracoes++;

            //os subtipos de evento são: 1.armazenamento, 2.remoção, 3.transporte, 4.rearmazenamento, 5.entrega
            //os possíveis estados de um pacote são: 1.não postado, 2.chegada escalonada a um armazém, 
            //3.armazenado na seção do próximo destino em lagum armazém, 4.removido da seção para transporte
            //5.entregue
            //TENHO QUE ESCALONAR OS PRIMEIROS TRANSPORTES DOS PACOTES FORA DO LOOP, OU NÃO SERÃO GERADOS NOVOS TRANSPORTES
            int tipoEvento = proximoEvento->getTipoEvento();
            //int subtipo = proximoEvento->getSubtipoEvento();
            Pacote* pacoteEvento = proximoEvento->getPacotePtr();
            //se for um evento de transporte
            if(tipoEvento == 2)
            {
                int inicioTransp = relogioSimulacao;
                int destino = proximoEvento->getArmazemDestino();
                int origem = proximoEvento->getArmazemOrigem();
                //int subtipo = proximoEvento->getSubtipoEvento();
                int posSecao = armazens[origem].encontraSecao(destino);
                int proxRota = pacoteEvento->getProximoRota();
                
                //checar se a secao de destino do armazém de origem está ou não vazia
                if(!armazens[origem].checaVazia(posSecao))
                {
                    //int tempoAntes = relogioSimulacao;
                    //passa os lementos da pilha principal para a auxiliar
                    while(!armazens[origem].checaVazia(posSecao))
                    {    
                        //remove os elementos da principal e passa para a auxiliar na seção correspondente
                        Pacote* aux = armazens[origem].esvaziaPrincipal(posSecao);
                        //Evento* novoEvento = new Evento;
                        relogioSimulacao = relogioSimulacao + custoRemocao;
                        //int tempoEvento = tempoAntes + (i*custoRemocao);
                        //std::string chaveEvento = Evento::construirChaveTransporte(relogioSimulacao, origem, destino);
                        //novoEvento->setEvento(chaveEvento, 2, 4, relogioSimulacao, aux->getId(), origem, destino, pacoteEvento);
                        //escalonador.Inserir(novoEvento);
                        std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                  << aux->getId() << " removido de " << std::setw(3) << origem << " na secao " 
                                  << std::setw(3) << destino << std::endl;
                    }
                    //escalonar a chegada
                    for(int i = 0; i < capacidadeTransp; i++)
                    {
                        if(armazens[origem].checaVaziaAux(posSecao)) 
                        {
                            break; // No more packages in the auxiliary stack to transport
                        }

                        //remove quantos pacotes for possível da pila auxiliar e já os coloca na seção de destino
                        //do armazém seguinte
                        Pacote* aux = armazens[origem].carregaTransporte(capacidadeTransp, destino, posSecao);
                        //armazens[destino].armazenaPacote(aux, proxRota);
                        aux->setArmAtual(destino);
                        int proximaRota = aux->getProximoRota();

                        //escalona o evento de chegada
                        Evento* novoEvento = new Evento;
                        int tempoEvento = relogioSimulacao + latenciaTransp;
                        std::string chaveEvento = Evento::construirChavePacote(tempoEvento, aux->getId());
                        novoEvento->setEvento(chaveEvento, 1, 1, tempoEvento, aux->getId(), origem, proximaRota, aux);
                        escalonador.Inserir(novoEvento);

                         std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                   << aux->getId() << " em transito de " << std::setw(3) << origem 
                                   << " para " << std::setw(3) << proxRota << std::endl;

                        /*Evento* novo_Evento = new Evento;
                        int tempo_Evento = inicioTransp + intervaloTransp;
                        origem = aux->getArmAtual();
                        destino = aux->getProximoRota();
                        //origem == destino -> evento é entrega 
                        std::string chave_Evento = Evento::construirChaveTransporte(tempo_Evento, origem, destino);
                        //pacoteEvento->setArmAtual(destino);
                        novo_Evento->setEvento(chave_Evento, 2, 3, tempo_Evento, aux->getId(), origem, destino, aux);
                        escalonador.Inserir(novo_Evento);   */        
                    }
                    
                    //se a pilha auxiliar não ficou vazia após as movimentações para transporte
                    if(!armazens[origem].checaVaziaAux(posSecao))
                    {
                        for(int i = 0; i < armazens[origem].tamSecaoAux(posSecao); i++)
                        {
                            Pacote* aux = armazens[origem].retornaPrincipal(posSecao);
                            //Evento* novoEvento = new Evento;
                            //int tempoEvento = tempoAntes;
                            //std::string chaveEvento = Evento::construirChaveTransporte(tempoAntes, origem, destino);
                            //novoEvento->setEvento(chaveEvento, 2, 4, tempoEvento, aux->getId(), origem, destino, aux);
                            //escalonador.Inserir(novoEvento);
                            aux->setEstadoAtual(3);
                            std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                                      << aux->getId() << " rearmazenado em " << std::setw(3) << origem
                                      << " na secao " << std::setw(3) << destino << std::endl;
                            
                        }
                    }

                }
                //escalona o próximo evento de transporte
                //int tempoAntes = relogioSimulacao;

                //TENTANDO CONSERTAR O PROBLEMA COM REARMAZENADOS 
                Evento* novoEvento = new Evento;
                int tempoEvento = inicioTransp + intervaloTransp;
                origem = pacoteEvento->getArmAtual();
                destino = pacoteEvento->getProximoRota();
                //origem == destino -> evento é entrega 
                std::string chaveEvento = Evento::construirChaveTransporte(tempoEvento, origem, destino);
                //pacoteEvento->setArmAtual(destino);
                novoEvento->setEvento(chaveEvento, 2, 3, tempoEvento, pacoteEvento->getId(), origem, destino, pacoteEvento);
                escalonador.Inserir(novoEvento);
            }

            else if(tipoEvento == 1)
            {
                //se chegou no fim da rota/foi entregue
                //std::cout << proximoEvento->getArmazemOrigem() << pacoteEvento->getArmDestino() << pacoteEvento->getProximoRota() << std::endl;
                if(proximoEvento->getArmazemOrigem() == pacoteEvento->getArmDestino() || (pacoteEvento->getProximoRota() == -1))
                {
                    std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                              << proximoEvento->getIdPacote() << " entregue em " << std::setw(3) << pacoteEvento->getArmDestino() << std::endl;
                    //indica que o novo estado do pacote é entregue
                    pacoteEvento->setEstadoAtual(5);
                    tamPacotes--;
                    //std::cout << "qt pacotes não entregues " << tamPacotes << std::endl;
                }

                else
                {
                    //teremos que atualizar o armazematual para o seguinte quando fizermos o escalonamento do transporte para que funcione
                    
                    
                    int armazemAtual = pacoteEvento->getArmAtual();
                    int armazemSeguinte = pacoteEvento->getProximoRota();
                    int posicaoSecao = armazens[armazemAtual].encontraSecao(armazemSeguinte);
                   
                    //MUDAR ESTADO DO PACOTE PARA 3

                    //CHECAR ISSO AQUI QUE PROVAVELMENTE VAI DAR PROBLEMA
                    armazens[armazemAtual].armazenaPacote((pacoteEvento), posicaoSecao); 
                    //pacoteEvento->setArmAtual(proximoEvento->getArmazemDestino());
                    //armazena na secao correta do armazem atual
                    //logica para encontrar qual é o próximo armazem na rota
                    //logica para armazenar o pacote na seção correta (a do próximo destino) do armazem atual
                    std::cout << std::setfill('0') << std::setw(7) << relogioSimulacao << " pacote " << std::setw(3) 
                              << proximoEvento->getIdPacote() << " armazenado em " << std::setw(3) << armazemAtual
                              << " na secao " << std::setw(3) << armazemSeguinte << std::endl;
                }
            }
            delete proximoEvento;
        }
        //assim que sair do while, temos de liberar os vetores que foram armazenados e fazer outras "limpezas" que sejam necessárias
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}