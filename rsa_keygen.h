#ifndef RSA_KEYGEN_H
#define RSA_KEYGEN_H

#include <stdint.h>

//This macro is used to enable/disable the display of p,q and phi
#define DEBUG 0

void rsa_generate_keys(uint16_t *p_e, uint16_t *p_d, uint16_t *p_n);

#endif