#include "ordenadorUniversal.hpp"
#include "ordenadores.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <chrono>
#include <cstdint>

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
        inventado vetor[qtChaves];
        for(int i = 0; i < qtChaves; i++)
        {
            if (std::getline(arquivo, linha))
            {
                std::istringstream iss(linha);
                long int value;
                if(iss >> value)
                {
                    //fazer checagens extras de tamanho
                    vetor[i].chave = value;
                    //vetor[i].nada = 0;
                    //vetor[i].nadashort = 0;
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

        
        //quickSort(vetor, 0, qtChaves - 1, s, 40);
        /*for(int i = 0; i < qtChaves/2; i++)
        {
            int aux = vetor[i];
            vetor[i] = vetor[qtChaves - 1 - i];
            vetor[qtChaves - 1- i] = aux;
        } */

        //srand48(seedArquivo);
        //ordUN.shuffleVector(vetor, qtChaves, 6000);
        //resetcounter(s);
        /*for(int i = 0; i < qtChaves; i++)
        {
            std::cout << vetor[i] << " ";
        }
        std::cout << std::endl;*/

        //TESTES EM QUE ordUN é melhor: 10, 2, 4, 5
        int qtQuebras = ordUN.calculaQuebras(vetor, qtChaves);
        ordUN.setnroQuebras(qtQuebras);
        std::cout << "número de quebras " << qtQuebras << std::endl;

        //auto start = std::chrono::high_resolution_clock::now();

        int limtamParticao = ordUN.determinaLimiarParticao(vetor, qtChaves, lCusto);
        ordUN.setMinTamParticao(limtamParticao);
        int limQuebras = ordUN.determinaLimiarQuebras(vetor, qtChaves, lCusto, limtamParticao);
        ordUN.setLimiarQuebras(limQuebras);
        std::cout << "limParticao: " << limtamParticao << std::endl;
        std::cout << "limQuebras: " << limQuebras << std::endl;

        auto start1 = std::chrono::high_resolution_clock::now();

        //resetcounter(s);
        contador_t s1;
        resetcounter(s1);
        ordUN.ordenadorUniversal(vetor, qtChaves, limtamParticao, limQuebras, s1);
        std::cout << "ord UN cmp: " << s1.cmp << " move: " << s1.move << " calls: " << s1.calls << std::endl;
        double custo1 = (0.0056893702)*s1.cmp + (-0.0021398390)*s1.move + (-0.0021398390)*s1.calls;
        std::cout << "custo ord UN: " << custo1 << std::endl;
        custo1 = 0;
        resetcounter(s1);

        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        std::cout << "Execution time ordUN: " << duration1.count() << " seconds" << std::endl;
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
        std::cout << "Execution time ordUN: " << duration_ms.count() << " ms" << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();

        //resetcounter(s);
        contador_t s;
        resetcounter(s);
        quickSort(vetor, 0, qtChaves - 1, s, 0); //otimizado somente com mediana de 3
        std::cout << "QS cmp: " << s.cmp << " move: " << s.move << " calls: " << s.calls << std::endl;
        double custo2 = (0.0056893702)*s.cmp + (-0.0021398390)*s.move + (-0.0021398390)*s.calls;
        std::cout << "custo QS: " << custo2 << std::endl;
        resetcounter(s);
        custo2 = 0;

        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        std::cout << "Execution time QS: " << duration2.count() << " seconds" << std::endl;
        auto duration_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        std::cout << "Execution time QS: " << duration_ms.count() << " ms" << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();

        //resetcounter(s);
        contador_t s2;
        resetcounter(s2);
        insercao(vetor, 0, qtChaves-1, s2);
        std::cout << "INS cmp: " << s2.cmp << " move: " << s2.move << " calls: " << s2.calls << std::endl;
        double custo3 = (0.0056893702)*s2.cmp + (-0.0021398390)*s2.move + (-0.0021398390)*s2.calls;
        std::cout << "custo INS: " << custo3 << std::endl;
        custo3 = 0;
        resetcounter(s2);

        auto end3 = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> duration3 = end3 - start3;
        std::cout << "Execution time QS: " << duration3.count() << " seconds" << std::endl;
        auto duration_ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
        std::cout << "Execution time QS: " << duration_ms.count() << " ms" << std::endl;        
    }    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}