#include <stdio.h>
#include <stdlib.h>

int main(){
int a,b,c,segmento=0;

scanf("%d", &a);
scanf("%d",&b);
int i = 0;

while (i<a){

scanf("%d", &c);

if (b!=c)
segmento +=1;

b = c;
i ++;
}

printf("%d\n", segmento);
return 0;
}