#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int n = atoi(argv[1]);
int a,b;

scanf("%d",&a);
int mdcAB=a;

scanf("%d",&b);

while(a%mdcAB!=0 || b%mdcAB!=0)
    mdcAB--;
// achamos o mdc que é o valor da variavel mdcAB//

int mdc = mdcAB;

for (int rep=n;rep>2;rep--){
    scanf("%d", &b);
    while(mdcAB%mdc!=0 || b%mdc!=0)
        mdc--;
}

printf("O mdc é %d\n", mdc);

}
