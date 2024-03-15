
#include <stdint.h>
#include "rsa_algorithm.h"
/**
 * @brief Finds the value of a^b (mod m)
 *
 * @param a
 * @param b
 * @param m
 * @return uint16_t
 */
 
/*calculates the modular exponentiation of a raised to the power of b modulo m.*/
uint16_t mod_exp(uint16_t a, uint16_t b, uint16_t m) {

    /* Set the result to 1 */
    uint16_t ans = 1;

    /* Bring the value of base withing the modulo range */
    a = a % m;

    /* Stop if the value of base is 0 */
    if (a == 0) {

        return 0;
    }

    while (b > 0) {
        /* If b is even, then update the answer */
        if (b & 1) {
            ans = (ans * a) % m;
        }

        /* Update the exponent */
        b = b >> 1;

        /* Update the multiplier */
        a = (a * a) % m;
    }

    return ans;
}

/**
 * @brief Encrypts the given message using the given public key components
 *
 * @param plaintext
 * @param ciphertext
 * @param len
 * @param e
 * @param n
 */
void rsa_encrypt(
        uint8_t  *plaintext,
        uint16_t *ciphertext,
        uint64_t len,
        uint16_t e,
        uint16_t n) {

    /* Encrypt the plaintext message block by block */
    for (int i = 0; i < len; i++) {
        ciphertext[i] = mod_exp((uint16_t)plaintext[i], e, n);
    }
}

/**
 * @brief Decrypts the given cipher using the given private key components
 *
 * @param plaintext
 * @param ciphertext
 * @param len
 * @param d
 * @param n
 */
void rsa_decrypt(
        uint8_t  *plaintext,
        uint16_t *ciphertext,
        uint64_t len,
        uint16_t d,
        uint16_t n) {

    /* Decrpyt the ciphertext message block by block */
    for (int i = 0; i < len; i++) {
        plaintext[i] = (uint8_t)mod_exp(ciphertext[i], d, n);
    }
}