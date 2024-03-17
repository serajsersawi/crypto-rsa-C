#ifndef RSA_ALGORITHM_H
#define RSA_ALGORITHM_H

void rsa_encrypt(
        uint8_t  *plaintext,
        uint16_t *ciphertext,
        uint64_t len,
        uint16_t e,
        uint16_t n);

void rsa_decrypt(
        uint8_t  *plaintext,
        uint16_t *ciphertext,
        uint64_t len,
        uint16_t d,
        uint16_t n);

int rsa_verify(
        uint8_t  *message,   // The original message or its hash
        uint16_t *signature,  // The signature to verify
        uint64_t len,         // Length of the message
        uint16_t e,           // Public exponent
        uint16_t n);
		
void rsa_sign(
        uint8_t  *message,  // The message or hash to sign
        uint16_t *signature, // The resulting signature
        uint64_t len,        // Length of the message
        uint16_t d,          // Private exponent
        uint16_t n);		

#endif