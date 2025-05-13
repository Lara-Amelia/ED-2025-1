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
    int lCusto, qtChaves;
    float A, B, C;
    //melhorar leitura
    arquivo >> lCusto >> A >> B >> C >> qtChaves;


    std::cout << "lCusto: " << lCusto << "\n";
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";
    std::cout << "C: " << C << "\n";
    std::cout << "qtChaves: " << qtChaves << "\n";
    ordUniversal ordUN(A, B, C, lCusto);

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
            }
        }
        else
        {
            //lançar exceção erro de leitura
            std::cerr << "Error: File has fewer vector lines than expected.\n";
            return 1;
        }
    }
    arquivo.close();
    ordUN.determinaLimiarParticao(vetor, qtChaves, lCusto);
    return 0;
}