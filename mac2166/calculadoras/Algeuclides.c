//dados 2 numeros na linha de comando devolver o mdc

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int x = atoi(argv[1]);
 int y = atoi(argv[2]);
int savex = x, savey = y;



int k, z;
if (y>x){
k = x;
x = y;
y = k;
}
if (x%y==0){
z = y;
}

 while (x%y != 0){
z = x%y;
printf("%d ", z);
x = y;
y = z;
if (x%y == 0){
    printf("\n");
}
 }

 printf("mdc(%d,%d) = %d\n", savex,savey ,z);
}