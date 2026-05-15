#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int numerodecompor = atoi(argv[1]);
int divisor = 2;
int expoente=0;

while (numerodecompor !=1){
    if (numerodecompor%divisor==0){
        while (numerodecompor%divisor==0){
            expoente++;
            numerodecompor = numerodecompor/divisor;
        }
    
        printf("%d^%d ", divisor, expoente);
        expoente = 0;
    }
    if (numerodecompor%divisor !=0)
        divisor ++;

    }
}
