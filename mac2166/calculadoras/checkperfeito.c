#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int n = atoi(argv[1]);

int a =1, s=0;
printf("Os divisores de %d são: ", n);
while (a<n){
if (n%a==0){
    printf("%d ", a);
    s +=a;
}
a++;
}

if (s==n){
    printf("\nComo a soma dos divisores é %d, %d é perfeito\n", s,n);
}
else 
printf("\nComo a soma dos divisores é %d, %d não é perfeito\n",s,n);


}