#include"miniRSA.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    long phi;
    long K;

    long* factors = (long*)malloc(5 * sizeof(long));

    if(argc != 3)
    {
        printf("Input as: keycracker.exe public-key modulus(N)\n");
        return 0;
    }

    long public = atoi(argv[1]);
    long N = atoi(argv[2]);

    if(primeFactors(N, &factors) != 2)
    {
        printf("Invalid modulus(N)\n");
        return -1;
    }

    phi = (factors[0] - 1) * (factors[1] - 1);
    K = 1 + phi;

    while(1)  
    {
        if(primeFactors(K, &factors) == 2)
        {
            if(factors[0] == public)
            {
                printf("Private Key: %ld\n", factors[1]);
                return 0;
            }
            else if(factors[1] == public)
            {
                printf("Private Key: %ld\n", factors[0]);
                return 0;
            }  
        }

        K = K + phi; 
    }
}