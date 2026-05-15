#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool prime(int x);
bool decomposição(int x);


int main(){
int x;


while (scanf("%d", &x)==1){

    if (prime(x))
        printf("%10d é primo\n", x);

    else if (x>1){
        printf("%10d não é primo e pode ser escrito como: ", x);
        decomposição(x);
        printf("\n");
    }


    else if (x==1 || x ==0){
        printf("%10d não é primo\n", x);
    }

    else{
        printf("%10d é negativo, e negativos são primos\n",x);
    }





}


return 0;











}


bool prime(int x){
int k = 2;

if (x<2)
return false;


while (k +1 != x/2 +1 && x%k!=0){
 k++;
}

if (k==x){
    return true;
}

if (x%k==0){
    return false;
}

else{
 return true;}
}

bool decomposição(int x){

int divisor = 2;
int expoente=0;

while (x !=1){
    if (x%divisor==0){
        while (x%divisor==0){
            expoente++;
            x = x/divisor;
        }
    
        printf("%d^%d ", divisor, expoente);
        expoente = 0;
    }
    if (x%divisor !=0)
        divisor ++;

    }



}






