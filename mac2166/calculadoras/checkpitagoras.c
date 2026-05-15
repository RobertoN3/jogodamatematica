#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int a = atoi(argv[1]);
 int b = atoi(argv[2]);
 int c = atoi(argv[3]);

 int x,y,z;

 if (a>b && a>c){
 x = a;
 y = b;
 z = c;
}

  else if (b>a && b>c){
  x = b;
  y = a;
  z = c;
}

   else if (c>b && c>a){
   x = c;
   y = a;
   z = b;
   }

else 
printf("não é pitagórico\n");

if (x*x==y*y+z*z)
printf("é pitagórico\n");

   else
   printf("não é pitagórico\n");
}