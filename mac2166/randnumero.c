#include <stdio.h>
#include <stdlib.h>

int main()
{

int seed, x, y, k;
scanf("%d %d %d", &x, &y, &seed);

srand(seed);

while (y>0){
y--;

k = rand()%x;

printf("%d ", k);
}

printf("\n");

}




