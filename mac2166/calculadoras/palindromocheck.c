#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int palindromo = atoi(argv[1]);

int salvarpalindromo = palindromo;
int grandeza = 1, casas = 0;

while (palindromo>grandeza){
    grandeza *= 10;
    casas ++;
}
grandeza /=10;

while (casas >0){

    if (palindromo/grandeza != salvarpalindromo%10){
        printf("não é palindromo\n");
        return 0;
    }


palindromo = palindromo - (palindromo/grandeza)*grandeza;
salvarpalindromo = (salvarpalindromo - (salvarpalindromo%10))/10;

grandeza /=10;
casas --;
}

 printf("é palindromo\n");

return 0;

}