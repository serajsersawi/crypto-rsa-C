#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "rsa_algorithm.h"

int main() {
    uint8_t message[2048]; // Buffer for the message
    uint16_t signature[2048]; // Buffer for the signature
    uint16_t e, n; // Public key components
    //int len = 0; // Counter for the length of the message/signature
	char inputLine[4096]; // Buffer to hold the input line for message and signature
    int messageLen = 0, signatureLen = 0; // Counters for the lengths

	printf("\n____________________________________\n");
	printf("EE5001 -- CA2 -- Sarraj Alsersawi ");
	printf("\n____________________________________");
	printf("\n____________________________________\n");
	printf("RSA Encryption -- Verification side ");
	printf("\n____________________________________\n\n");
	
    // Prompt and read the message as numeric values
    printf("Enter the message (numeric form, space-separated): ");
    fgets(inputLine, sizeof(inputLine), stdin);
    char *token = strtok(inputLine, " ");
    while (token != NULL && messageLen < 2048) {
        message[messageLen++] = (uint8_t)atoi(token);
        token = strtok(NULL, " ");
    }

    // Prepare to read the signature
    printf("Enter the signature (numeric form, space-separated): ");
    fgets(inputLine, sizeof(inputLine), stdin); // Reuse the inputLine buffer for signature input
    token = strtok(inputLine, " ");
    while (token != NULL && signatureLen < 2048) {
        signature[signatureLen++] = (uint16_t)atoi(token);
        token = strtok(NULL, " ");
    }
	printf("\n");
    printf("Enter the public key (e): ");
    scanf("%hu", &e);
    printf("Enter the modulus (n): ");
    scanf("%hu", &n);
	printf("\n");
    // Call rsa_verify to verify the signature
    if (rsa_verify(message, signature, signatureLen, e, n)) {
        printf("Verification successful: The message is authentic.\n");
    } else {
        printf("XX Verification failed: The message is not authentic.\n");
    }
	
	printf("Press ENTER key to Exit!\n"); 
	getchar(); 	
	getchar();

    return 0;
}
