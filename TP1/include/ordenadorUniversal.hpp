#ifndef ORDENADORUNIVERSAL_HPP
#define ORDENADORUNIVERSAL_HPP
#include "ordenadores.hpp"

typedef struct estatistica 
{
    double custo;
    int limParticao;
    contador_t stats;
} estatisticas_t;

typedef struct stat
{
    double custoIN;
    double custoQS;
    int limQuebras;
    double diffCusto;
    contador_t statsIN;
    contador_t statsQS;
} estatisticasLQ;

class ordUniversal
{
    private:
    double coefA; //comps - talvez voltar para double depois
    double coefB; //movs
    double coefC; //calls
    float limiarCusto;
    int nroQuebras;
    int limiarQuebras;
    int minTamParticao;
    int seed;

    public:
    void setnroQuebras(int qtQuebras);

    ordUniversal(double A, double B, double C, float limCusto, int seed); //os demais serão definidos depois
    void ordenadorUniversal(int* V, int tam, int MinTamParticao, int limiarQuebras, contador_t &s);
    int calculaQuebras(int* vetor, int tam);
    int determinaLimiarParticao(int* v, int tam, int limiarCusto);
    void calculaNovaFaixa(int limParticao , int &minMPS, int &maxMPS, int &passoMPS, int numMPS, estatisticas_t* stats);
    void registraEstatisticas(double &custo, contador_t &stats);
    void imprimeEstatisticas(double* custo, contador_t* stats, int t, int numMPS, double diffCusto);
    void imprimeEstatisticasLQ(estatisticasLQ stats, int t, int numLQ);
    //void imprimeEstatistica(double* custo, contador_t* stats, int t, int numMPS, double diffCusto);
    int menorCusto(estatisticas_t* stats);
    int getMPS(int indice, estatisticas_t* stats, int numMPS);
    //int encontraElemento(estatisticas_t* stats, int particao, int numMPS);
    void calculaNovaFaixaLQ(int limQB, int &minLQ, int &maxLQ, int &passoLQ, int numLQ, estatisticasLQ* stats);

    int determinaLimiarQuebras(int* v, int tam, int limiarCusto, int limTamParticao);

};

/* antes de invocar o ordenador universal, determinamos os limiares de quebras e tamanho de partição,
   que são passados como parâmetros para o ordenador (será um método da classe)
*/

/* 
   para obter o limiar de quebras, iremos simular os 2 algoritmos no meio do intervalo (0, n-1)
   e, a partir daí, checar se devemos, então, investigar a primeira ou a segunda metade do intervalo 
   (similar a uma busca binária). o custo será dado pela expressão de custo f dada na descrição do TP 
   consideramos que, se o vetor possui k quebras, então ordená-lo tem o mesmo custo de ordenar um vetor
   de k elementos com k-1 quebras
   um vetor com k quebras está dividido em k+1 segmentos já ordenados - podemos os ordenar cada segmento
   separadamente com cada um dos algoritmos e combinar os custos, como feito para o limiar de partição
   (é semelhante a simular a ordenação para um número x de quebras)
   para o limite de quebras, também faremos a divisão em 5 intervalos e, para cada um deles, 
   aplicaremos diretamente o qs e o is, comparando os custos obtidos e usando isso para o refinamento
*/

/*#include <iostream>
#include <vector>

// Função auxiliar para contar inversões usando Merge Sort
long long mergeAndCount(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += (mid - i + 1); // Contando quebras
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; ++i, ++k) arr[i] = temp[k];

    return count;
}

// Função principal de Merge Sort modificada para contar inversões
long long countBreaks(std::vector<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long count = 0;

    count += countBreaks(arr, left, mid);
    count += countBreaks(arr, mid + 1, right);
    count += mergeAndCount(arr, left, mid, right);

    return count;
}

int main() {
    std::vector<int> vetor = {3, 1, 2, 4};
    long long quebras = countBreaks(vetor, 0, vetor.size() - 1);

    std::cout << "Número de quebras: " << quebras << std::endl;
    return 0;
}*/


/*#include <iostream>
#include <chrono>

// Função para contar quebras (inversões) sem Merge Sort
long long countBreaks(int arr[], int n) {
    long long count = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) count++;
        }
    }
    return count;
}

// Função para o Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função para o Quicksort
void quicksort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[++i], arr[right]);

    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}

// Função para calibrar o limiar de quebras
int calibrateBreakThreshold(int arr[], int n) {
    int left = 0, right = n - 1, bestThreshold = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        int testArr1[n], testArr2[n];
        for (int i = 0; i < n; ++i) testArr1[i] = testArr2[i] = arr[i];

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(testArr1, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto insertionTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        quicksort(testArr2, 0, n - 1);
        end = std::chrono::high_resolution_clock::now();
        auto quickTime = std::chrono::duration<double>(end - start).count();

        if (insertionTime <= quickTime) {
            bestThreshold = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return bestThreshold;
}

int main() {
    int vetor[] = {3, 1, 2, 4, 5, 9, 8, 7, 6, 10};
    int n = sizeof(vetor) / sizeof(vetor[0]);

    long long quebras = countBreaks(vetor, n);
    std::cout << "Número de quebras: " << quebras << std::endl;

    int threshold = calibrateBreakThreshold(vetor, n);
    std::cout << "Limiar de quebras calibrado: " << threshold << std::endl;

    return 0;
}*/

/*#include <iostream>

// Variáveis globais para contar comparações, movimentações e chamadas de funções
long long cmp = 0, move = 0, calls = 0;

// Função de simulação do Insertion Sort
void simulateInsertionSort(int arr[], int n) {
    calls++;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            cmp++;  // Comparação
            j--;
            move++; // Movimento
        }
        if (j >= 0) cmp++;  // Caso a comparação final seja feita (onde arr[j] <= key)
    }
}

// Função de simulação do Quicksort
void simulateQuicksort(int arr[], int left, int right) {
    if (left >= right) return;
    calls++;
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        cmp++;  // Comparação
        if (arr[j] <= pivot) {
            i++;
            move++;  // Troca
            std::swap(arr[i], arr[j]);
        }
    }
    move++;  // Troca do pivô
    std::swap(arr[i + 1], arr[right]);

    simulateQuicksort(arr, left, i);
    simulateQuicksort(arr, i + 2, right);
}

int main() {
    int arr[] = {9, 7, 5, 11, 12, 2, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Simular Insertion Sort
    simulateInsertionSort(arr, n);
    std::cout << "Insertion Sort: Comparacoes = " << cmp << ", Movimentacoes = " << move << ", Chamadas = " << calls << std::endl;

    // Resetar as variáveis de contagem
    cmp = 0;
    move = 0;
    calls = 0;

    // Simular Quicksort
    simulateQuicksort(arr, 0, n - 1);
    std::cout << "Quicksort: Comparacoes = " << cmp << ", Movimentacoes = " << move << ", Chamadas = " << calls << std::endl;

    return 0;
}*/
#endif