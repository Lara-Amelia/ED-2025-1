#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <chrono>
#include "ordenadores.hpp"
#include "ordenadorUniversal.hpp"
#include <cstdlib>

/*typedef struct contador
{
  int cmp;
  int move;
  int calls;
} contador_t;

void resetcounter(contador_t &s)
{
    s.cmp = 0;  
    s.move = 0;
    s.calls = 0;
}

void inccmp(contador_t &s, int num)
{
    s.cmp += num;
}

void incmove(contador_t &s, int num)
{
    s.move += num;
}

void inccalls(contador_t &s, int num)
{
    s.calls += num;
}

void swap(int *xp, int *yp, contador_t &s)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s,3);
}

int median (int a, int b, int c) 
{
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

void insertionSort(int v[], int l, int r, contador_t &s) 
{
    //l = 0 (limite inferior) e r = v.size - 1 (limite superior)
    int i, j, comparado;
    inccalls(s,1);
    for(i = l + 1; i <= r; i++)
    {
        comparado = v[i];
        j = i - 1; //percorremos o subarray de 0 a i - 1
        while((j >= l) && (comparado < v[j])) 
        {
            inccmp(s,1);
            v[j+1] = v[j];
            incmove(s, 1);
            //"abrimos espaço" ao longo do vetor
            j--;
        }
        inccmp(s,1);
        v[j+1] = comparado;
        incmove(s,2);
    }
  return;
}

void partition3(int * A, int l, int r, int *i, int *j, contador_t &s) 
{
  inccalls(s, 1);    
  *i = l;
  *j = r;
  int meio = (l+r)/2;
  int valorPivo = median(A[l], A[r], A[meio]);
  int pivo;
  for(int k = l; k <= r; k++)
  {
      if (A[k] == valorPivo)
      {
          pivo = A[k];
      }
  }
  do
  {
    while(A[*i] < pivo)
    {
      inccmp(s,1);
      (*i)++;
    }
    inccmp(s,1);
    
    while(A[*j] > pivo)
    {
      inccmp(s,1);    
      (*j)--;
    }
    inccmp(s,1);
    
    if((*j) >= (*i))
    {
      swap(&A[*j], &A[*i], s);
      (*i)++;
      (*j)--;
    }    
  } while ((*j) >= (*i));
  
}

void quickSort3Ins(int * A, int l, int r, contador_t &s) 
{
  inccalls(s, 1);    
  int i, j;
  partition3(A, l, r, &i, &j, s);
  if(l < j)
  {
    if(j-l <= 50)
    {
      insertionSort(A, l, j, s);
    }  
    else
    {
      quickSort3Ins(A, l, j, s); 
    }  
  }  
  if(i < r)
  {
    if(r-i <= 50)
    {
      insertionSort(A, i, r, s);
    }  
    else  
    {
      quickSort3Ins(A, i, r, s); 
    }  
  }   
}

int calculaQuebras(int* vetor, int tam)
{
    int nroQuebras = 0;
    for(int i = 1; i < tam; i++)
    {
        if(vetor[i] < vetor[i-1]) //se o atual for menor que o seu antecessor
            nroQuebras++;
    }
    return nroQuebras;
}*/

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
        int qtChaves;

        if (std::getline(arquivo, linha)) 
        {
            std::istringstream iss(linha);
            iss >> qtChaves;
        }
        else
            throw std::runtime_error("ERRO: não foi possível ler o valor do tamanho do vetor");

        
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

        arquivo.close();
        //int qtChaves, qtQuebras;
        /*std::cout << "digite qt chaves: ";
        std::cin >> qtChaves; std::cout << "qtChaves: " << qtChaves << std::endl;
        std::cout << "digite qt quebras: "; 
        std::cin >> qtQuebras;
        std::cout << "qtQuebtas: " << qtQuebras << std::endl;*/

        //int* vetor = new int[qtChaves]; // aloca vetor dinâmico

        //srand48(48);          // inicializa seed

        /*int intervalo_max = 100;      // intervalo: 0 a 99

        for (int i = 0; i < qtChaves; i++) {
            vetor[i] = static_cast<int>(drand48() * intervalo_max);
        }*/

        // Imprime o vetor
        /*for (int i = 0; i < qtChaves; i++) 
        {
            std::cout << vetor[i] << " ";
        }
        std::cout << std::endl;*/

        ordUniversal ordUN(1, 1, 1, 0, 0);
        //quickSort(vetor, 0, qtChaves - 1, s, 50);
        //ordUN.shuffleVector(vetor, qtChaves, qtQuebras);
        std::cout << "size " << qtChaves << " breaks " << ordUN.calculaQuebras(vetor, qtChaves) << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        contador_t s;
        resetcounter(s);
        //resetcounter(s);
        //quickSort(vetor, 0, qtChaves - 1, s, 50);
        //quickSort3Ins(vetor, 0, qtChaves-1, s);
        //std::cout << "cmp: " << s.cmp << " moves: " << s.move << " calls: " << s.calls << std::endl;
        ordUN.ordenadorUniversal(vetor, qtChaves, 50, -1, s);
        std::cout << "cmp: " << s.cmp << " moves: " << s.move << " calls: " << s.calls << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << duration_ms.count() << " ms" << std::endl;

        //delete[] vetor;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}