#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rsa_algorithm.h"

int main() {
    // Sample plaintext to encrypt (ASCII values)
    //uint8_t plaintext[] = "seraj";
    // Determine the length of the plaintext
    //uint64_t len = sizeof(plaintext) - 1; // Exclude null terminator for string
	
	uint8_t plaintext[2048]; 
	// Allocate memory for ciphertext (should be the same size as plaintext length)
    uint16_t ciphertext[2048];
	printf("\n____________________________________\n");
	printf("EE5001 -- CA2 -- Sarraj Alsersawi ");
	printf("\n____________________________________");
	printf("\n____________________________________\n");
	printf("RSA Encryption -- Sender side ");
	printf("\n____________________________________\n\n");
	// Prompt and read in the plaintext from the user
    printf("Enter the message (plaintext) to encrypt: ");
    fgets((char*)plaintext, sizeof(plaintext), stdin);
    // Remove trailing newline character if present
    size_t len = strlen((char*)plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
        len--; // Adjust length to exclude the newline
    }
	
    // Public key components (example values, choose appropriate ones)
    //uint16_t e = 14783; // Common choice for e
    //uint16_t n = 23449; // Example modulus (n should be a product of two primes, p and q)
	// Variables for the public and private key components
    uint16_t e, n, d;

    // Ask the user to input the public key components (e and n) and the private key component (d)
    printf("\n");
	printf("Enter the public key (e): ");
    scanf("%hu", &e);
    printf("Enter the modulus (n): ");
    scanf("%hu", &n);



	
	printf("\n");
	// Print the plaintext in numeric form
    printf("Plaintext (numeric form):\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", plaintext[i]); // Print each character's ASCII value
    }
    printf("\n");

    // Encrypt the plaintext
    rsa_encrypt(plaintext, ciphertext, len, e, n);

    // Print the ciphertext
    printf("Ciphertext (numeric form):\n");
    for (int i = 0; i < len; i++) {
        printf("%hu ", ciphertext[i]); // Print each encrypted character's numerical value
    }
    printf("\n\n\n ____________________________________\n\n");
	printf("Now launch the receiver application (receiver_app.exe)\n");
	printf("and provide the private key (d) and copy paste the ciphertext you got here\n");
	printf("if you get the same plaintext back then the process is validated :)\n");
	printf("\n ____________________________________\n\n");

    return 0;
}