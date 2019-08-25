#include<stdio.h> 
#include<math.h> 
#include<stdbool.h>
#include<string.h> 
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"miniRSA.h"

// Returns gcd of a and b 
int gcd(int a, int h) 
{ 
    int temp; 
    while (1) 
    { 
        temp = a%h; 
        if (temp == 0) 
          return h; 
        a = h; 
        h = temp; 
    } 
} 

// long coprime(long x){
//     int cPrime = (srand(time(0)) % (1024 - 2 + 1)) + 2;
//     while (1) {
//         if (gcd(cPrime, x) == 1) {
//             return cPrime;
//         } else {
//             cPrime = (rand() % (1024 - 2 + 1)) + 2;
//         }
//     }
// }

//Creating a sieve with the code from
//as the base
int * getPrimes(int n) 
{ 
    // Create a boolean array "prime[0..n]" and initialize 
    // all entries it as true. A value in prime[i] will 
    // finally be false if i is Not a prime, else true. 
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    for (int p=2; p*p<=n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p greater than or  
            // equal to the square of it 
            // numbers which are multiple of p and are 
            // less than p^2 are already been marked.  
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
  
    int* primes = (int*)malloc(200*sizeof(int));
    int i = 0;
    // Print all prime numbers 
    for (int p=2; p<=n; p++){
       if (prime[p]){
            //printf("%d\n", p);
            primes[i] = p;
            i++;
       } 

    } 

    return primes;
} 
  
// Code to demonstrate RSA algorithm 

// long mod_inverse(int a, int b){

// }

long modExp(long a, unsigned long b, long c){
    //return fmod(pow(a,b),c);
    int res = 1;      // Initialize result 
  
    a = a % c;  // Update x if it is more than or  
                // equal to p 
  
    while (b > 0) 
    { 
        // If y is odd, multiply x with result 
        if (b & 1) 
            res = (res*a) % c; 
  
        // y must be even now 
        b = b>>1; // y = y/2 
        a = (a*a) % c;   
    } 
    return res; 
}

//Based on code from https://www.geeksforgeeks.org/prime-factor/
//Modified to return the number of prime factors found to ensure it's 2
//Also modified to take in an array of ints and bring them out of the function
int primeFactors(int n, long** factors) 
{ 
    int numOfFactors = 0;

    // Print the number of 2s that divide n 
    while (n%2 == 0) 
    { 
        //printf("%d ", 2); 
        n = n/2; 
        (*factors)[numOfFactors] = n;
        numOfFactors++;
    } 
  
    // n must be odd at this point.  So we can skip  
    // one element (Note i = i +2) 
    for (int i = 3; i <= sqrt(n); i = i+2) 
    { 
        // While i divides n, print i and divide n 
        while (n%i == 0) 
        { 
            //printf("%d ", i);
            n = n/i; 
            (*factors)[numOfFactors] = i;
            numOfFactors++;
        } 
    } 
  
    // This condition is to handle the case when n  
    // is a prime number greater than 2 
    if (n > 2) {
        //printf ("%d ", n);
        (*factors)[numOfFactors] = n; 
        numOfFactors++;
    }
    //printf("%d", numOfFactors);
    return numOfFactors;
} 

long encrypt(char msg, unsigned long e, long N){
    long value = msg;
    return modExp(value, e, N);
}

char decrypt(long code, long d, long N){
    char msg = modExp(code, d, N);
    return msg;
}
