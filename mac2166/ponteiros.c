#include <stdio.h>
#include <stdlib.h>

int main(){

int a = 11, b = 22;

printf("a = %d, b = %d\n&a = %p, &b = %p\n", a, b, &a, &b);

int *pont_a;
int *pont_b;

pont_a = &a;
pont_b = &b;

printf("*pont_a = %d, *pont_b = %d\n", *pont_a, *pont_b);

printf("pont_a = %p, pont_b = %p\n", pont_a, pont_b);

printf("vai trocar: ");

*pont_a = 33; b = 44;

printf("*pont_a = %d, *pont_b = %d\n", *pont_a, *pont_b);
printf("a = %d, b = %d\n", a, b);

printf("&pont_a = %p, &pont_b = %p\n", &pont_a, &pont_b);
}
