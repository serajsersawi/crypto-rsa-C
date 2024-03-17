#include <stdio.h>
#include "rsa_keygen.h"

/**
 * @brief Driver program which generates the public and private keys for RSA
 *        algorithm.
 *
 */
void main() {

    uint16_t e;
    uint16_t d;
    uint16_t n;

    /* Generate the keys */
    rsa_key_gen(&e, &d, &n);

    /* Print the values */
    printf("e = %d\n", e);
    printf("d = %d\n", d);
    printf("n = %d\n", n);
}