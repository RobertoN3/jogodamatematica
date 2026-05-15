#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int x = atoi(argv[1]);
 int y = atoi(argv[2]);
int p=1;
while (y>0){
p = p*x;

    y --;
}
printf("%d\n", p);
}