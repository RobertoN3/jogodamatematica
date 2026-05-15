/*********************************************************************/
/** AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, **/
/** DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. **/
/** TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM **/
/** DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES **/
/** DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA **/
/** OU PLÁGIO. **/
/** DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS **/
/** DESSE PROGRAMA E QUE EU NÃO DISTRIBUÍ OU FACILITEI A **/
/** SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E **/
/** DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS **/
/** DIVULGADOS NA PÁGINA DA DISCIPLINA. **/
/** ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E, **/
/** AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA. **/
/** **/
/** Nome : Roberto Norio Kubo **/
/** NUSP : 17863189 **/
/** Turma: 01 - Eng. Computação **/
/** Prof.: Yoshiharu Kohayakawa **/
/** **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool comparacao_take(int taken, int takem, int nn, int nm);
bool comparacao_ntake(int nn, int nm);

int main(int argc, char *argv[]) {

int n1, n2, nx, take1, take2, takex, t1, t2, tx;

//n1 é o numero do piloto escaneado primeiro//
// take1 é a primeira tentativa dele, t1 é o tempo//

scanf("%d %d %d",&n1, &take1, &t1);

scanf("%d %d %d",&n2, &take2, &t2);

if ((t1>t2) || (t1 == t2 && n1>n2)){
// para deixar o numero 1 salvo como o melhor//
// só ocorre isso se o 2 for melhor que o 1 //
    int troca1, troca2, troca3;
    troca1 = n2;
    troca2 = take2;
    troca3 = t2;
    n2 = n1;
    take2 = take1;
    t2 = t1;
    n1 = troca1;
    take1 = troca2;
    t1 = troca3;
}


// evitar: se os primeiros 2 dados forem os melhores e do mesmo carro //
while (n1 == n2){
    scanf("%d %d %d",&n2, &take2, &t2);

    if ((t1>t2) || (t1 == t2 && take2<take1) || (t1==t2 && take2==take1 && n2<n1)){
// para deixar o numero 1 salvo como o melhor (de novo)//
    int troca1, troca2, troca3;
    troca1 = n2;
    troca2 = take2;
    troca3 = t2;
    n2 = n1;
    take2 = take1;
    t2 = t1;
    n1 = troca1;
    take1 = troca2;
    t1 = troca3;
}
}


while (scanf("%d %d %d",&nx, &takex, &tx) != EOF){

    if (nx != n1){ //O piloto a ser avaliado ñ estava em primeiro lugar//
        if (tx<t1){
            t2 = t1; t1 = tx; // transformando o placar, colocando x em//
            n2 = n1; n1 = nx; // primeiro, e o antigo primeiro em segundo//
            take2 = take1; take1 = takex;
            }

        else if (tx==t1 && comparacao_take(takex, take1, nx, n1)){
        // se o x for melhor q o primeiro por desempate//
            t2 = t1; // t1 = tx; //
            n2 = n1; n1 = nx;
            take2 = take1; take1 = takex;   
            }
        
        else if (tx<t2){
        //como chegamos aqui, x é pior que o primeiro //
        // entao comparamos tx com t2//
        //para ver se ele é melhor que t2 //

            t2 = tx; // substituindo o segundo pelo x//
            n2 = nx;
            take2 = takex;
            }

        else if (tx == t2 && comparacao_take( takex, take2, nx, n2)){
        // como chegamos nessa parte, tx >= t2, então podemos//
        // comparar os take se t2 == tx //
            n2 = nx;
            take2 = takex;
            }
        }

    else if (nx == n1 && tx<t1){
    // Caso específico: O piloto 1 superou o proprio recorde//
        t1 = tx;
        take1 = takex;
        }
    }

int seg1, seg2, min1, min2;
seg1 = t1/1000;
seg2 = t2/1000;
t1 = t1%1000;   // definindo os tempos em unidades//
t2 = t2%1000;
min1 = seg1/60;
min2 = seg2/60;
seg1 = seg1%60;
seg2 = seg2%60;

if (min1==1)
    printf("Pole position: Piloto %d, com tempo de %d minuto,", n1, min1);

else
    printf("Pole position: Piloto %d, com tempo de %d minutos,", n1, min1);

if (seg1==1)
    printf(" %d segundo e ", seg1);

else
printf(" %d segundos e ", seg1);

if (t1==1)
printf("%d milissegundo (tentativa %d).\n", t1, take1);

else
printf("%d milissegundos (tentativa %d).\n", t1, take1);



if (min2==1)
    printf("Segundo lugar: Piloto %d, com tempo de %d minuto,", n2, min2);

else
    printf("Segundo lugar: Piloto %d, com tempo de %d minutos,", n2, min2);

if (seg2==1)
    printf(" %d segundo e ", seg2);

else
printf(" %d segundos e ", seg2);

if (t2==1)
printf("%d milissegundo (tentativa %d).\n", t2, take2);

else
printf("%d milissegundos (tentativa %d).\n", t2, take2);

}




// função n // 
// se o n é melhor que o m, retorna true //
bool comparacao_ntake(int nn, int nm){

if (nn<nm){
    return true;
    }

if (nn>nm){
    return false;
    }

}



// função take // 
// usar quando os tn e tm são iguais
//retorna true se o n é melhor que o m//
bool comparacao_take(int taken, int takem, int nn, int nm){

if (taken<takem)
    return true;

if (taken>takem)
    return false;

if (comparacao_ntake(nn, nm))
    return true;

return false;
}