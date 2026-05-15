#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int n = atoi(argv[1]);

 int x=1, Binario=0, casas =0;

 while (x<=n){
    x *=2;
casas ++;}
x /=2;

while (casas>0){
    
if (n-x>=0){

    Binario *=10;
    Binario = Binario + 1;
    n -=x;
}
else{
    
    Binario *=10;
}
x/=2;
casas --;
}

printf("%d\n", Binario);

return 0;
}