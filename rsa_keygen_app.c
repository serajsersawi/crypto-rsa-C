#include <stdio.h>
#include "rsa_keygen.h"


void main() {

    uint16_t e;
    uint16_t d;
    uint16_t n;

    /* Generate the keys */
    rsa_generate_keys(&e, &d, &n);

    /* Print the values */
    printf("Public key e = %d\n", e);
    printf("Private key d = %d\n", d);
    printf("Modulus n = %d\n", n);
}