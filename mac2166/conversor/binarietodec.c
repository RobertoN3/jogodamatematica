#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int n = atoi(argv[1]);
int numeroconvertido =0, s=1;

while(n>0){

if( n%2 ==1){
numeroconvertido +=s;
n = (n-1)/10;
}

else
n = n/10;

s*=2;

}
printf("%d\n", numeroconvertido);

}