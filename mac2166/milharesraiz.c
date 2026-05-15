#include <stdio.h>
#include <stdlib.h>

int main(){

int a = 32,q, xxoo, yy, xx;
while (a<100){
q = a*a;
yy = q%100;
xxoo = q - yy;
xx = xxoo/100;
if (xx+yy==a)
printf("%d ", q);

    a++;
}
printf("\n");
}