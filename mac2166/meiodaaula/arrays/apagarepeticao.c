// Problema extra.  Dados um inteiro positivo N e uma sequência de N
// números inteiros, imprimir a sequência eliminando as repetições.


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void ler(int a[], int n); //função q le o vetor

void imprime(int a[], int n); //funcao q imprime o vetor


int main(int argc, char *argv[]){

int N = atoi(argv[1]);
int a[N];  
int b[N];        
int dist = 0;
bool repetiu = false;

ler(a, N);

for (int i = 0; i < N; i++){
    repetiu = false;

    for (int j = 0; j <= dist && repetiu == false; j++){ //verifica se o termo na posicao i é repetido
        if (a[i] == b[j])
            repetiu = true;
    }

if (!repetiu){
    b[dist] = a[i];
    dist++;
}
}

imprime(b,dist);

}




void ler(int a[], int n){
for (int i = 0; i < n; i++){
    scanf("%d", &a[i]);
}
}

void imprime(int a[], int n){

for (int i = 0; i < n; i++){
    printf("%d ", a[i]);
}
}