#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <limits>
#include <cctype>

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

        //insere a nroArmazens qt. de vértices no grafo
        for(int i = 0; i < nroArmazens; i++)
        {
            transporte.InsereVertice();
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

            while (ss >> valor_celula) 
            {
                if (col_count >= nroArmazens) 
                {
                    throw std::runtime_error("ERRO: Linha " + std::to_string(i) + " possui mais colunas do que o esperado (" + std::to_string(nroArmazens) + ").");
                }

                if (valor_celula == 1) 
                {
                    transporte.InsereAresta(i, col_count);
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
        std::cout << "\nLendo " << numeroPacotes << " Pacotes..." << std::endl;
        // Consumir a quebra de linha pendente após a leitura de numeroPacotes
        arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        Pacote** pacotes = new Pacote*[numeroPacotes]; 
        //Heap escalonador(numeroPacotes * 5); // Ex: 5 vezes o num de pacotes para começar

        for (int k = 0; k < numeroPacotes; ++k) 
        { // Loop para ler cada linha de pacote 
            std::string linha;
            if (!std::getline(arquivo, linha)) 
            {
                throw std::runtime_error("ERRO: linhas com infos. de pacotes insuficientes");
                delete[] pacotes; 
            }

            std::stringstream ss_pacote(linha);
            int tempoChegada, idPacote, armazemInicial, armazemFinal;
            std::string dummy_pac, dummy_org, dummy_dst; // Para ler as strings "pac", "org", "dst" 

            // Lê os detalhes do pacote conforme o formato (ex: 9 pac 0 org 1 dst 0) 
            ss_pacote >> tempoChegada >> dummy_pac >> idPacote >> dummy_org >> armazemInicial >> dummy_dst >> armazemFinal;

            // Cria a instância do Pacote
            pacotes[k] = new Pacote(idPacote, tempoChegada, armazemInicial, armazemFinal);
            
            // Calcula e armazena a rota do pacote usando BFS no grafo de transporte 
            transporte.buscaLargura(armazemInicial, armazemFinal, pacotes[k]->rota);
            //pacotes[k]->setRota(aux); 

            // --- Crie e Agende o Evento Inicial de Chegada do Pacote (Postagem) ---
            // A chave de prioridade é crucial para a ordem na heap. 
            //long long chave_evento_chegada = construirChavePacote(tempoChegada, idPacote); 
            
            // Cria um objeto Evento. Para um Escalonador que armazena Evento*.
            // (Se seu Heap::Inserir espera apenas int, você precisaria adaptar a Heap
            //  ou usar um mapa para recuperar o Evento* a partir da chave).
            // Para simplicidade, vamos inserir a chave e teremos que decodificá-la.
            // O ideal seria que a Heap armazenasse Evento* diretamente.
            // Por simplicidade, vamos inserir a chave numérica, e a decodificação será feita ao remover.
            //escalonador.Inserir(static_cast<int>(chave_evento_chegada)); // Inserindo a chave como int (PODE TRUNCAR se long long)
            // Para evitar truncamento, Heap::Inserir(long long) e adaptar a classe Heap para long long.

            //std::cout << "  Pacote lido: Tempo=" << tempoChegada << ", ID=" << idPacote << ", Origem=" << armazemInicial << ", Destino=" << armazemFinal << ". Chave: " << chave_evento_chegada << std::endl;
            std::cout << "  Rota calculada para Pacote " << idPacote << ": ";
            pacotes[k]->rota.Imprime(); // Imprime a rota do pacote para verificação.
        }
        arquivo.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}