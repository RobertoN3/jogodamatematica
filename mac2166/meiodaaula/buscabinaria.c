#include <stdio.h>
#include <stdlib.h>

int buscabinaria(int procura, int lista[], int n); // procura é q procuramos, n é o numero
// de elementos da lista, sendo a lista crescente

int buscabinaria(int procura, int lista[], int n){
    int k = n/2;
    n = n/2;

    while (lista[k] != procura){
        if (procura < lista[k]){
            k = k-n/2;
            n = n/2;
        }
        if (procura > lista[k]){
            k = k + n/2;
            n = n/2;
        }
    }

    return k;
}