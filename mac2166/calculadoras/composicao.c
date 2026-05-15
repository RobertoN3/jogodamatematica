// dados A e B e C, falar se existe xA+yB=C, se (x,y) esta nos naturais

#include <stdio.h>

int main(){

int a,b,c;
scanf("%d", &a);
scanf("%d", &b);
scanf("%d", &c);

int x = 0, y = 0;

while (x*a<=c){
    if (x*a + y*b==c){
        printf("%d moeda (s) de %d e %d moeda (s) de %d\n", x,a,y,b);
        return 0;}

y++;

    
    if (y*b>c){
        y=0;
        x++;
    }
}

printf("Não é possível trocar a cédula\n");
return 0;}
