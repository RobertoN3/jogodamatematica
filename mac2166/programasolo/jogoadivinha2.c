// termo de numeros

//dada seed e x, gera-se um numero de x digitos, o jogador chuta um numero de x digitos, se acertar, ganha
// se errar, se algum numero bater com o numero secreto, é avisado que acertou a posiçao e o numero.
// se errar, e algum numero bater, mas está fora da ordem de grandeza, é avisado que acertou o numero, mas não a posiçao
// se errar, e nenhum numero bater, é avisado que errou tudo

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int seed, x, ordem = 1;
    scanf("%d %d", &seed, &x);
    srand(seed);

    for (int i = 0; i < x; i++){
ordem *= 10;
    }

    // Gera o número secreto de x dígitos
    int numero_secreto = rand() % ordem;
    int salva_numero_secreto = numero_secreto; // Salva o número secreto para comparação posterior

    int a[x], b[x];
    for (int i = x - 1; i>=0 ; i--){
        a[i] = numero_secreto % 10;
        numero_secreto /= 10;
    }

    int chute;
    scanf("%d", &chute);

    while (chute != salva_numero_secreto){

        for (int i = x - 1; i>=0 ; i--){
            b[i] = chute % 10;
            chute /= 10;
        }

        for (int i = 0; i < x; i++){

            bool errototal = true;

            if (b[i] == a[i]){
                printf("(%d) ", a[i]);
                errototal = false;
            }

            else {
                for (int j = 0; j < x; j++){
                    if (b[i] == a[j]){
                        printf("<%d> ", a[j]);
                        errototal = false;
                        break;
                    }
                }
            }
            if (errototal)
                printf("x%dx ", b[i]);
        }

        printf("\n");
        scanf("%d", &chute);
    }
printf("parabens, voce acertou o numero secreto! %d\n", salva_numero_secreto);
}