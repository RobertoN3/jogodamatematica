#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int x = atoi(argv[1]);

int a = 1,b=2,c=3;

while (a*b*c<x){
a++;
b ++;
c ++;
}
if (a*b*c== x){
printf("%d é um número triangular\n", x);
}
else {
    printf("%d não é um número triangular\n", x);
}
}