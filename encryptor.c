#include<stdio.h> 
#include<math.h> 
#include<stdbool.h>
#include<string.h> 
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"miniRSA.h"

int main(int argc, char* argv[]){
    
    char msg = (argv[1])[0];
    long E = atoi(argv[2]);
    long C = atoi(argv[3]);
    long D = atoi(argv[4]);
    long DC = atoi(argv[5]);
    
    long code = encrypt(msg, E, C);

    printf("%ld is the encrypted message\n", code);

    long value = decrypt(code, D, DC);
    char decodedMsg = decrypt(code, D, DC);
    printf("%ld is the decrypted value\n", value);
    printf("%c is the decrypted message\n", decodedMsg);
}