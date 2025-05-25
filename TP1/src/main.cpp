#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <chrono>

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
        int lCusto, qtChaves, seedArquivo;
        double A, B, C;
        

        //Faz a leitura das linhas com dados sobre o ordenador do arquivo 
        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> seedArquivo;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor de seed");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> lCusto;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor de Limiar de Custo");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> A;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor do coeficiente a");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> B;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor do coeficiente b");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> C;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor do coeficiente c");

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> qtChaves;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor do tamanho do vetor");

        ordUniversal ordUN(A, B, C, lCusto, seedArquivo);

        //Faz a leitura das qtChaves linhas do arquivo contendo os elementos do vetor
        int vetor[qtChaves];
        for(int i = 0; i < qtChaves; i++)
        {
            if (std::getline(arquivo, linha))
            {
                std::istringstream iss(linha);
                int value;
                if(iss >> value)
                {
                    vetor[i] = value;
                }
            }
            else
                throw std::runtime_error("ERRO: fim da leitura, não há linhas suficientes no arquivo de entrada");
        }

        //Imprime as infos necessárias e chama os métodos da classe ordenadorUniversal
        arquivo.close();
        std::cout << "size " << qtChaves << " seed " << seedArquivo << " breaks " << ordUN.calculaQuebras(vetor, qtChaves);
        std::cout << std::endl << std::endl;
        int qtQuebras = ordUN.calculaQuebras(vetor, qtChaves);
        ordUN.setnroQuebras(qtQuebras);

        int limtamParticao = ordUN.determinaLimiarParticao(vetor, qtChaves, lCusto);
        ordUN.setMinTamParticao(limtamParticao);
        int limQuebras = ordUN.determinaLimiarQuebras(vetor, qtChaves, lCusto, limtamParticao);
        ordUN.setLimiarQuebras(limQuebras);
        std::cout << "limtamParticao = " << limtamParticao << " limQuebras = " << limQuebras << std::endl;
        contador_t s;
        /*resetcounter(s);
        quickSort(vetor, 0, qtChaves - 1, s, 0);
        std::cout << " QS cmp: " << s.cmp << " move: " << s.move << " calls: " << s.calls << std::endl;*/

        int copiaord[qtChaves];
        for(int i = 0; i < qtChaves; i++)
        {
            copiaord[i] = vetor[i];
        }

        resetcounter(s);
        std::cout << "nro quebras QS: " << ordUN.calculaQuebras(vetor, qtChaves) << std::endl;
        
        auto start1 = std::chrono::high_resolution_clock::now();

        resetcounter(s);
        quickSort(vetor, 0, qtChaves - 1, s, 0);
        std::cout << "QS cmp: " << s.cmp << " move: " << s.move << " calls: " << s.calls << std::endl;
        std::cout << "QS custo = " << A*s.cmp + B*s.move + C*s.calls << std::endl;
        
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        std::cout << "Execution time QS: " << duration1.count() << " seconds" << std::endl;
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
        std::cout << "Execution time QS: " << duration_ms.count() << " ms" << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();

        resetcounter(s);
        ordUN.ordenadorUniversal(copiaord, qtChaves, limtamParticao, limQuebras, s);
        std::cout << "ordUN cmp: " << s.cmp << " move: " << s.move << " calls: " << s.calls << std::endl;
        std::cout << "ordUN custo = " << A*s.cmp + B*s.move + C*s.calls << std::endl;
        
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        std::cout << "Execution time ordUN: " << duration2.count() << " seconds" << std::endl;
        auto duration_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        std::cout << "Execution time ordUN: " << duration_ms2.count() << " ms" << std::endl;
    }    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}