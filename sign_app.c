#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rsa_algorithm.h"

int main() {
    uint8_t message[2048]; // Buffer for the message
    uint16_t signature[2048]; // Buffer for the signature
    uint16_t d, n; // Private key components
    //size_t len; // Message length
	printf("\n____________________________________\n");
	printf("EE5001 -- CA2 -- Sarraj Alsersawi ");
	printf("\n____________________________________");
	printf("\n____________________________________\n");
	printf("RSA Encryption -- Signature side ");
	printf("\n____________________________________\n\n");
	//Prompt and read in the plaintext from the user
    printf("Enter the message (plaintext) to sign: ");
    fgets((char*)message, sizeof(message), stdin);
    // Remove trailing newline character if present
    size_t len = strlen((char*)message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
        len--; // Adjust length to exclude the newline
    }
	printf("\n");
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
    printf("\n\n");

    // Call rsa_sign to sign the message
    rsa_sign(message, signature, len, d, n);


    // Output the signature
    printf("Signature (numeric form):\n");
    for (size_t i = 0; i < len; i++) {
        printf("%hu ", signature[i]);
    }
	
    printf("\n\n\n ____________________________________\n\n");
	printf("Now launch the verification application (verify_app.exe)\n");
	printf("and provide the public key (e) and copy paste the message and signature you got here\n");
	printf("the program will get back to you whether the message is authentic ot not :)\n");
	printf("\n ____________________________________\n\n");

    return 0;
}