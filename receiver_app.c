#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "rsa_algorithm.h"

int main() {
	
	uint16_t ciphertext[2048]; // Adjust size as needed
    uint8_t plaintext[2048];   // Ensure this is large enough to hold the decrypted message
    uint16_t d, n;
    int len = 0;
	char inputLine[1024]; // Buffer to hold the input line

	printf("\n____________________________________\n");
	printf("RSA Encryption -- Receiver side ");
	printf("\n____________________________________\n\n");
    // Prompt for and read in the modulus (n) and the private exponent (d)
	printf("Enter the private key (d): ");
    scanf("%hu", &d);
    printf("Enter the modulus (n): ");
    scanf("%hu", &n);


    // Flush stdin to clear any leftover input
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Enter (Paste) the ciphertext (numeric form and space seperated), then press Enter:\n");
    if (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
        // Parse the ciphertext numbers from the input line
        char *token = strtok(inputLine, " ");
        while (token != NULL && len < 256) {
            ciphertext[len++] = (uint16_t)atoi(token);
            token = strtok(NULL, " ");
        }
    }

    // Decrypt the ciphertext
    rsa_decrypt(plaintext, ciphertext, len, d, n);
	printf("\n\n____________________________________\n");
    // Print the resulting plaintext
    printf("Decrypted plaintext:\n");
    for (int i = 0; i < len; i++) {
        printf("%c", plaintext[i]); // Print each decrypted character
    }
    printf("\n\n");

    return 0;
}