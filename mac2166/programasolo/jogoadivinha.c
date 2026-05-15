//dada seed, o programa gera de 1 a 100, o jogador tenta adivinhar o numero
// ao errar, recebe uma dica de ser maior ou menor

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

    int seed;
    scanf("%d", &seed);
    srand(seed);

    int numero_secreto = rand()%1000000 + 1; //gera um numero de 1 a 100
    int chute;
    bool acertou = false;

    while (!acertou){
        printf("Digite seu chute: ");
        scanf("%d", &chute);

        if (chute == numero_secreto){
            printf("Parabéns! Você acertou o número secreto!\n");
            acertou = true;
        } else if (chute < numero_secreto){
            printf("Tente um número maior!\n");
        } else {
            printf("Tente um número menor!\n");
        }
    }

    return 0;
}
