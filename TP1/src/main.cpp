#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>

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

        /*arquivo >> lCusto >> A >> B >> C >> qtChaves;*/

        ordUniversal ordUN(A, B, C, lCusto, seedArquivo);
        /*std::cout << "seed: " << seedArquivo << std::endl;
        std::cout << "lCusto: " << lCusto << "\n";
        std::cout << "A: " << A << "\n";
        std::cout << "B: " << B << "\n";
        std::cout << "C: " << C << "\n";
        std::cout << "qtChaves: " << qtChaves << "\n";*/

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
                    //fazer checagens extras de tamanho
                    vetor[i] = value;
                    //std::cout << "valor na posição i do vetor: " << vetor[i] << std::endl;
                }
            }
            else
                throw std::runtime_error("ERRO: fim da leitura, não há linhas suficientes no arquivo de entrada");
        }

        //Imprime as infos necessárias e chama os métodos da classe rdenadorUniversal
        arquivo.close();
        std::cout << "size " << qtChaves << " seed " << seedArquivo << " breaks " << ordUN.calculaQuebras(vetor, qtChaves);
        std::cout << std::endl << std::endl;
        int limtamParticao = ordUN.determinaLimiarParticao(vetor, qtChaves, lCusto);
        ordUN.determinaLimiarQuebras(vetor, qtChaves, lCusto, limtamParticao);
    }    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}