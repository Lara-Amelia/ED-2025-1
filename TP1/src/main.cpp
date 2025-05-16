#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>

int main(int agrc, char** argv)
{
    std::string nomeArquivo = argv[1];
    //adicionar exceção para caso argv < 1
    std::ifstream arquivo(nomeArquivo);
    //adicionar exceção caso o arquivo não seja aberto
    std::string linha; 
    int lCusto, qtChaves, seedArquivo;
    double A, B, C;
    //melhorar leitura
     if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> seedArquivo;
    }


    if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> lCusto;
    }

    if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> A;
    }

    if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> B;
    }

    if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> C;
    }

    if (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        iss >> qtChaves;
    } 


    /*arquivo >> lCusto >> A >> B >> C >> qtChaves;*/

    ordUniversal ordUN(A, B, C, lCusto, seedArquivo);
    /*std::cout << "seed: " << seedArquivo << std::endl;
    std::cout << "lCusto: " << lCusto << "\n";
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";
    std::cout << "C: " << C << "\n";
    std::cout << "qtChaves: " << qtChaves << "\n";*/

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
    }
    std::cout << "size " << qtChaves << " seed " << seedArquivo << " breaks " << ordUN.calculaQuebras(vetor, qtChaves);
    std::cout << std::endl << std::endl;
    arquivo.close();
    int limtamParticao = ordUN.determinaLimiarParticao(vetor, qtChaves, lCusto);
    ordUN.determinaLimiarQuebras(vetor, qtChaves, lCusto, limtamParticao);
    return 0;
}