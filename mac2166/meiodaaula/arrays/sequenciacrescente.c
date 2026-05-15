//Dados dois inteiros positivos M e N, 
// e duas sequências crescentes com M e N números inteiros, obter
//uma única sequência crescente contendo todos os elementos das
// sequências originais (esta sequência deve portanto ter M + N
// elementos)

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int M = atoi(argv[1]);
int N = atoi(argv[2]);

int listaM[M];
int listaN[N];
int listaMN[M+N];

for (int i=0; i<M; i++){
listaM[i] = -1;              //deixar cada termo -1
}

for (int i=0; i<N; i++){
listaN[i] = -1;              //deixar cada termo -1
}


for (int i=0; i<M; i++){
scanf("%d", &listaM[i]);    //ler cada termo de M
}

for (int i=0; i<N; i++){
scanf("%d", &listaN[i]);    //ler cada termo de N
}

int a = 0, b = 0;

for (int i=0; i<M+N; i++){

if (M == a){
    listaMN[i] = listaN[b];
    b++;
}

else if (N == b){
    listaMN[i] = listaM[a];
    a++;
}

else if (listaM[a] <= listaN[b]){
    listaMN[i] = listaM[a];
    a ++;
}

else {
    listaMN[i] = listaN[b];
    b ++;
}
}


for (int i = 0; i<M+N; i++){
printf("%d ", listaMN[i]);
}
printf("\n");
}