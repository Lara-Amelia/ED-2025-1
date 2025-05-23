#include <iostream>
#include <fstream>

void escrever_vetor_inverso(const std::string& nome_arquivo, int tamanho)
{
    std::ofstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    arquivo << tamanho << "\n";  // primeira linha: tamanho do vetor
    for (int i = tamanho; i >= 1; --i) {
        arquivo << i << "\n";  // cada elemento por linha
    }

    arquivo.close();
}

int main() 
{
    int tamanho;
    std::cout << "digite o tamanho do vetor a ser criado";
    std::cin >> tamanho;// exemplo de tamanho
    escrever_vetor_inverso("vetor.txt", tamanho);
    std::cout << "Vetor escrito no arquivo 'vetor.txt' com sucesso." << std::endl;
    return 0;
}