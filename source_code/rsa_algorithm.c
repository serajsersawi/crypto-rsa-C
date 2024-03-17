
#include <stdint.h>
#include "rsa_algorithm.h"

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

void rsa_sign(
        uint8_t  *message,  // The message or hash to sign
        uint16_t *signature, // The resulting signature
        uint64_t len,        // Length of the message
        uint16_t d,          // Private exponent
        uint16_t n) {        // Modulus
    // Sign each block of the message
    for (int i = 0; i < len; i++) {
        signature[i] = mod_exp(message[i], d, n);
    }
}

// Function to verify a signature
int rsa_verify(
        uint8_t  *message,   // The original message or its hash
        uint16_t *signature,  // The signature to verify
        uint64_t len,         // Length of the message
        uint16_t e,           // Public exponent
        uint16_t n) {         // Modulus
    uint16_t verification[len];
    // "Decrypt" the signature to recover the original message/hash
    for (int i = 0; i < len; i++) {
        verification[i] = mod_exp(signature[i], e, n);
    }
    
    // Check if the verified message/hash matches the original message/hash
    for (int i = 0; i < len; i++) {
        if (message[i] != verification[i]) {
            return 0; // Verification failed
        }
    }
    return 1; // Verification successful
}