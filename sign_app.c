#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rsa_algorithm.h"

int main() {
    uint8_t message[2048]; // Buffer for the message
    uint16_t signature[2048]; // Buffer for the signature
    uint16_t d, n; // Private key components
    //size_t len; // Message length

// Prompt and read in the plaintext from the user
    printf("Enter the message (plaintext) to sign: ");
    fgets((char*)message, sizeof(message), stdin);
    // Remove trailing newline character if present
    size_t len = strlen((char*)message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
        len--; // Adjust length to exclude the newline
    }

    printf("Enter the private key (d): ");
    scanf("%hu", &d);
    printf("Enter the modulus (n): ");
    scanf("%hu", &n);
	
	printf("\n");
	// Print the plaintext in numeric form
    printf("message (numeric form):\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", message[i]); // Print each character's ASCII value
    }
    printf("\n");

    // Call rsa_sign to sign the message
    rsa_sign(message, signature, len, d, n);


    // Output the signature
    printf("Signature (numeric form):\n");
    for (size_t i = 0; i < len; i++) {
        printf("%hu ", signature[i]);
    }
    printf("\n");

    return 0;
}