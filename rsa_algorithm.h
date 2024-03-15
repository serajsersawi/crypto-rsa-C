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



#endif