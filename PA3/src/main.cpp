#include "heap.hpp"
#include <iostream>
#include <sstream>

int main(void)
{

    int tamanhoMax;
    std::cin >> tamanhoMax;
    Heap* novoHeap = new Heap(tamanhoMax);
    std::cin.ignore();
    std::string line;
    std::cout << "Digite os elementos na mesma linha: " << std::endl;
    std::getline(std::cin, line); // Lê toda a linha
    
    std::stringstream ss(line); // Transforma a linha em um fluxo de string
    int valor;
    while(ss >> valor)
    {
        novoHeap->Inserir(valor);
    }
    while (!novoHeap->Vazio()) 
    {
        std::cout << novoHeap->Remover() << " ";
    }
    std::cout << std::endl;

    return 0;
}