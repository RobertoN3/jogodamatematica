#include <stdio.h>
#include <stdlib.h>

void ler(int a[], int n); //função q le o vetor

void imprime(int a[], int n); //funcao q imprime o vetor


int main(){

int a[10];

ler(a, 10);

imprime(a, 10);
}


void ler(int a[], int n){
for (int i = 0; i < n; i++){
    scanf("%d", &a[i]);
}
}

void imprime(int a[], int n){

for (int i = 0; i < n; i++){
    printf("%d", a[i]);
}
}