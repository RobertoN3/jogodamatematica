#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int x = atoi(argv[1]);
int k = 2;

while (k +1 != x/2 +1 && x%k!=0){
 k++;
}

if (k==x){
    printf("%d é primo\n", x);
    return 0;
}


if (x%k==0){
    printf("%d não é primo, pois %d é divisor\n", x,k);
}

else{
 printf("%d é primo\n", x);}
}