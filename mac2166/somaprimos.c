#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int n = atoi(argv[1]);
int a;
int somaprimo = 0;

while (n!=0){

    scanf("%d", &a);

    for (int d=2; d<=(a/2)+1; d++){
        if (a==2){
            printf("2 ");
            somaprimo +=a;
            break;}

        if (a%d==0)
            break;

        if (d== (a/2)+1){
            printf("%d ",a);
            somaprimo +=a;}
    }

    n--;
}


 printf("%d\n", somaprimo);
return 0;

}