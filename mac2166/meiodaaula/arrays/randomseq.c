#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int seed = atoi(argv[3]);

    // largest multiple of M < 2^{31} = 2147483648
    int MM = (2147483647 / M) * M;
    
    srand(seed);
    for (int i = 0; i < N; ++i) {
        int x = rand();
        while (x >= MM) 
            x = rand();
        printf("%d ", x % M);  
    }
    printf("\n");

    return 0;
}