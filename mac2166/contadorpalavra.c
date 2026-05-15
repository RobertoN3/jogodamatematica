#include <stdio.h>
#include <stdbool.h>


bool isalnum(char ch);

int main(void){

bool in_word = false;
int caracter = 0, palavraa = 0;

char CHAR;
scanf("%c", &CHAR);

while (CHAR != '.'){
    caracter ++;

    if (in_word){
        if (CHAR == ' '){
            in_word = false;
        }
    }

else if (isalnum(CHAR)){
    in_word = true;
    palavraa ++;
}
scanf("%c", &CHAR);
}

printf("tem %d palavras e %d caracters", palavraa, caracter);
}



bool isalnum(char ch){
if ('a' <= ch && ch <= 'z') return true;
if ('A' <= ch && ch <= 'Z') return true;
if ('0' <= ch && ch <= '9') return true;

return false;
}