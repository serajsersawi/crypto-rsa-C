#include <stdio.h>
#include "rsa_keygen.h"


void main() {

    uint16_t e;
    uint16_t d;
    uint16_t n;

    /* Generate the keys */
    rsa_generate_keys(&e, &d, &n);
	printf("\n____________________________________\n");
	printf("EE5001 -- CA2 -- Sarraj Alsersawi ");
	printf("\n____________________________________");
	printf("\n____________________________________\n");
	printf("RSA Encryption -- Key generation ");
	printf("\n____________________________________\n\n");
	
    /* Print the values */
    printf("Public key e = %d\n", e);
    printf("Private key d = %d\n", d);
    printf("Modulus n = %d\n", n);
	
	
	printf("\n\n____________________________________\n\n");
	printf("Now you can use those keys to launch encryption or signature validation test\n");
	printf("\n____________________________________\n\n");
	
	printf("It is recommended to keep this windows open to copy the keys\n"); 
	printf("Press ENTER key to Exit!\n");  
	getchar(); 
}