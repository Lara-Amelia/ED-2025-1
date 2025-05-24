#include "ordenadores.hpp"

/* 
   Arquivo contendo as implementações dos algoritmos de ordenação utilizados 
   (insertion sort e quicksort com mediana de 3 e insertion para partições pequenas)
   e os métodos/estruturas relacionados ao registro de estatísticas (cmp, mv, calls)
*/

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

void swap(inventado *xp, inventado *yp, contador_t &s)
{
    inventado temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s,3);
}

int median (inventado a, inventado b, inventado c) 
{
    if ((a.chave <= b.chave) && (b.chave <= c.chave)) return b.chave;  // a b c
    if ((a.chave <= c.chave) && (c.chave <= b.chave)) return c.chave;  // a c b
    if ((b.chave <= a.chave) && (a.chave <= c.chave)) return a.chave;  // b a c
    if ((b.chave <= c.chave) && (c.chave <= a.chave)) return c.chave;  // b c a
    if ((c.chave <= a.chave) && (a.chave <= b.chave)) return a.chave;  // c a b
    return b.chave;                            // c b a
}

void partition3(inventado *A, int l, int r, int *i, int *j, contador_t &s) 
{
    inccalls(s, 1);    
    *i = l;
    *j = r;
    int meio = (l+r)/2;
    int valorPivo = median(A[l], A[r], A[meio]);
    int pivo;
    for(int k = l; k <= r; k++)
    {
        if (A[k].chave == valorPivo)
        {
            pivo = A[k].chave;
        }
    }
    do
    {
        while(A[*i].chave < pivo)
        {
            inccmp(s,1);
            (*i)++;
        }
        inccmp(s,1);
        
        while(A[*j].chave > pivo)
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

void quickSort(inventado *A, int l, int r, contador_t &s, int limTamParticao) 
{
    //l = limite inferior = 0; r = limite superior = tam-1
    int i, j;
    inccalls(s,1); 
    partition3(A, l, r, &i, &j, s);
    if(l < j)
    {
        if((j-l) < limTamParticao)
        {
            insercao(A, l, j+1, s);
        }  
        else
        {
            quickSort(A, l, j, s, limTamParticao); 
        }  
    }    
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

void insercao(inventado v[], int tam, int r, contador_t &s) 
{
    int i, j, comparado;
    inccalls(s,1);
    for(i = tam+1; i < r; i++)
    {
        comparado = v[i].chave;
        j = i - 1; 
        while((j >= tam) && (comparado < v[j].chave)) 
        {
            inccmp(s,1);
            v[j+1] = v[j];
            incmove(s, 1);
            j--;
        }
        inccmp(s,1);
        v[j+1].chave = comparado;
        incmove(s,2);
    }
  return;
}