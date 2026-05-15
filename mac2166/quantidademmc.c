#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int x = atoi(argv[1]);
 int y = atoi(argv[2]);
int z = atoi(argv[3]);
printf("0  ");
int k=2, l = 2;
int a = y, b = z;

while (x>1){
if (y>z){
printf("%d  ", z);
z = k*b;
k++;
}
else if (y<z){
printf("%d  ", y);
y = l*a;
l ++;
}
else if (y==z){
    printf("%d ", y);
   y = l*a;
    z = k*b;

    l ++;
    k ++;
    printf("é um multiplo comum  ");
}
x--;
}

printf("\n");
}


