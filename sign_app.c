#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rsa_algorithm.h"

int main() {
    uint16_t message[2048]; // Buffer for the message
    uint16_t signature[2048]; // Buffer for the signature
    uint16_t d, n; // Private key components
    size_t len; // Message length

    printf("Enter the message to sign: ");
    fgets((char*)message, sizeof(message), stdin);
    len = strlen((char*)message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
        --len;
    }

    printf("Enter the private key (d): ");
    scanf("%hu", &d);
    printf("Enter the modulus (n): ");
    scanf("%hu", &n);

    // Call rsa_sign to sign the message
    rsa_sign(message, signature, len, d, n);

    // Output the original message
    printf("Message (numeric form):\n");
    for (size_t i = 0; i < len; i++) {
        printf("%d ", message[i]);
    }
    printf("\n");

    // Output the signature
    printf("Signature (numeric form):\n");
    for (size_t i = 0; i < len; i++) {
        printf("%hu ", signature[i]);
    }
    printf("\n");

    return 0;
}