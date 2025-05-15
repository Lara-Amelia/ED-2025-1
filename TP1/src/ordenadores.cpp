#include "ordenadores.hpp"

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

void partition3(int *A, int l, int r, int *i, int *j, contador_t &s) 
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

void quickSort(int *A, int l, int r, contador_t &s, int limTamParticao) 
{
    //l = limite inferior = 0; r = limite superior = tam-1
    int i, j;
    inccalls(s,1); 
    partition3(A, l, r, &i, &j, s);
    if(l < j)
    {
        if((j-l) < limTamParticao)
        {
            //checar se é isso mesmo e talvez adaptar para receber limites left e right
            insercao(A, l, j+1, s); //foi alterado chat - voltar para j+1 se piorar
        }  
        else
        {
            quickSort(A, l, j, s, limTamParticao); 
        }  
    }    
    //voltar a ins original
    if(i < r)
    {
        if((r-i) < limTamParticao)
        {
            insercao(A, i, r+1, s);
        }  
        else  
        {
            quickSort(A, i, r, s, limTamParticao); 
        }  
    }
    return;  
}

void insercao(int v[], int tam, int r, contador_t &s) 
{
    //l = 0 (limite inferior) e r = v.size - 1 (limite superior)
    int i, j, comparado;
    inccalls(s,1);
    for(i = tam+1; i < r; i++)
    {
        comparado = v[i];
        j = i - 1; //percorremos o subarray de 0 a i - 1
        while((j >= tam) && (comparado < v[j])) 
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