#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int n = atoi(argv[1]);
int a=1,b=1,c,s;
for (int i=0;i<n;i++){
c = a+b;
s = a;
a=b;
b=c;

}
 printf("%d\n",s);

}