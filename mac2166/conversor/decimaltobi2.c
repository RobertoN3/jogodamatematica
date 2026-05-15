#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){


    int n = atoi(argv[1]);
int base = 1, contador=0;


while (n>=base){
    base *= 2;
    contador++;
}

base /= 2;

while (contador>0){
    if (n-base>=0){
        printf("1");
        n = n - base;
        base/=2;}
    
    else {
        printf("0");
        base /=2;
    }

    contador--;
}

printf("\n");
return 0;

}