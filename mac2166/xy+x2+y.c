#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char *argv[]){

int m = atoi(argv[1]);
int n = atoi(argv[2]);
int max=0, bet;

while (m>0){
bet = m*(n-m)+n;

if (bet>= max){
    max = bet;}

//printf("%d ",bet);//
m--;
}

printf("o max é %d\n", max);
return 0;


}