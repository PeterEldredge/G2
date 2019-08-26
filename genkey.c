#include<stdio.h> 
#include<math.h> 
#include<stdbool.h>
#include<string.h> 
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"miniRSA.h"
#define MAXNUMS 1000

int calcKeys(int a, int b) 
{ 
    srand(time(0));

    int primes[200];

    int p = getPrimes(MAXNUMS)[a-1];
    int q = getPrimes(MAXNUMS)[b-1];

    printf("%d\n", p);
    printf("%d\n", q);

    long N = p*q;
    //printf("%ld\n", n);

    //This should be the "totient"
    //AKA r from the RSA Worksheet
    long phi = (p-1)*(q-1);

    //Like in Popyack's RSA Worksheet, we calculate K
    //Start with the first possible K by adding one as the
    //candidates are found by (1 mod r) or in this case (1 mod phi)
    long K = 1 + (fmod(rand(), 20)*phi);
    long* factors = (long*)malloc(5*sizeof(long));
    while (primeFactors(K, &factors) != 2)  
    {
        K = K + phi;   
    }

    long e, d;

    e = factors[0];
    d = factors[1];

    printf("Your Public key is (%ld, %ld)\n", e, N);
    printf("Your Private key is (%ld, %ld)\n", d, N);


}

int main(int argc, char* argv[]){
    
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    
    calcKeys(a, b);

}