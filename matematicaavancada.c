#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void main()
{
    int acertos = 0;
    int erros = 0;
    int continuar = 1;
   
srand(time(NULL));  /*srand(semente que muda a cada segundo)*/
     while(continuar == 1){
 
    int sorteio = (rand() % 4) + 1;  /*resto desse numero varia de 0 a 3( dividido por 4), somando um o sorteio varia
     de 1 a 4*/
    
    


    if( sorteio == 1){
        
    printf("Qual a raiz quadrada de:\n");
    int nraiz = (rand() % 1000) + 1;  
double raiz = sqrt(nraiz);         

while((int)raiz * (int)raiz != nraiz){
    nraiz = (rand() % 1000) + 1;   /*atualiza o valor dentro até a resposta ser um inteiro*/
    raiz = sqrt(nraiz);
}
    printf(" %d\n", nraiz);
    int resposta1;
    scanf("%d", &resposta1);
    if(resposta1== raiz){
    printf("Acertou, a raiz de %d é igual a %d\n", nraiz, resposta1);
    acertos++;
    }else{
    printf("Errou, a raiz de %d é igual a %lg\n", nraiz, raiz);
    erros++;
    
    } 
    

} /*fim do código de raiz quadrada*/
if(sorteio == 2){
    
    printf("Qual o resultado da operação:\n");
    int npotencia = (rand() % 30) + 1;  
    int expoente;
    if(npotencia <= 10){
expoente = (rand() % 3) + 1; 
    }else{
     expoente = (rand() % 2) + 1;  
    }
int operação = pow(npotencia, expoente);
printf("%d elevado a %d\n", npotencia, expoente);
int resposta2;
    scanf("%d", &resposta2);
    if(resposta2 == operação){
    printf("Acertou, %d elevado a %d é igual a %d\n", npotencia, expoente, operação);
    acertos++;
    }else{
    printf("Errou, %d elevado a %d é igual a %d\n", npotencia, expoente, operação);
    erros++;
    
}


}/*fim do código para potenciação*/
if( sorteio == 3){
    printf("Qual o resultado da operação:\n");
    int base = (rand() % 10) + 1;
    while(base != 2 && base != 3 && base != 5 && base != 10){
        base = (rand() % 10) + 1;
    }
    int logaritimando = (rand() % 1000) + 1;
    double logaritimo = log(logaritimando) / log(base);
    while((int)logaritimo != logaritimo){
        logaritimando = (rand() % 1000) + 1;
        logaritimo = log(logaritimando) / log(base);
    }

    printf("Log_%d(%d)\n", base, logaritimando);
    int resposta3;
    scanf("%d", &resposta3);
    if(resposta3 == logaritimo){
        printf("Acertou, Log_%d(%d) = %lg\n", base, logaritimando, logaritimo);
        acertos++;
    }else{
        printf("Errou, Log_%d(%d) = %lg\n", base, logaritimando, logaritimo);
        erros++;
    }
    
}/*fim do código para log*/
if(sorteio == 4){
     printf("Qual o resultado de:\n");
    int nfatorial = (rand() % 7) + 1;
    int fatorial = nfatorial;
    int proximo = nfatorial - 1;
    for(; proximo > 1; proximo--){
        fatorial = fatorial * proximo;
    }
   printf("%d!\n", nfatorial);
   int resposta4;
   scanf("%d", &resposta4);
   if(resposta4 == fatorial){
    printf("Acertou, %d! = %d\n", nfatorial, fatorial);
    acertos++;
    }else{
    printf("Errou, %d! = %d\n", nfatorial, fatorial);
    erros++;
}
   



}






printf("Deseja continuar? (1 = sim) (0 = não)\n");
scanf("%d", &continuar);

}





double porcentagem;
porcentagem = (100) * (acertos) / (acertos + erros);

if(porcentagem >= 70){
printf("Parabéns!\n Você acertou %lg%% das questões\n", porcentagem);
}
if(porcentagem >= 50 && porcentagem < 70){
printf("Está quase lá!\n Você acertou %lg%% das questões\n", porcentagem);
}
if(porcentagem < 50){
printf("Você pode melhorar!\n Você acertou %lg%% das questões\n", porcentagem);
}
}
