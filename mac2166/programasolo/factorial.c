#include <stdio.h>
#include <stdlib.h>

int main (){

int x,y,k = 1;

scanf("%d", &x);

y = x;

if (x<1){
x = x*-1;

if (x==1){
printf("-1! = -1\n");

exit(0);
}}

while (x!=1){

k = k*x;

x--;
}

if (y<0){

if (y%2 == -1){

    k = -1 * k;
}

}

printf("%d! = %d\n", y, k);
}