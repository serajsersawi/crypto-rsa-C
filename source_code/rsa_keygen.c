#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "rsa_keygen.h"



/**
 * Implement the iterative version of the Extended Euclidean Algorithm.
 * This function calculates the greatest common divisor (gcd) of two integers `a` and `b`,
 * and finds integers `x` and `y` such that `ax + by = gcd(a, b)`.
 * 
 * The calculation is performed iteratively, making the function memory efficient by avoiding recursion.
 * 
 */
void extended_euclid_iterative(int a, int b, int *x, int *y) {
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    int q, r, x2, y2;

    while (b != 0) {
        q = a / b;
        r = a % b;
        x2 = x0 - q * x1;
        y2 = y0 - q * y1;
        
        // Update a and b for the next iteration
        a = b;
        b = r;
        
        // Shift the coefficients for the next iteration
        x0 = x1;
        x1 = x2;
        y0 = y1;
        y1 = y2;
    }

    *x = x0;
    *y = y0;
}

/**
 * Check if two integers are coprime.
 * Two numbers are considered coprime if their greatest common divisor (GCD) is 1.
 * This function utilizes the Euclidean algorithm to find the GCD of x and y.
 * If the GCD is 1, it returns true, indicating the numbers are coprime.
 * Otherwise, it returns false.
 *
 */
bool coprime_check(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x == 1; // If GCD is 1, numbers are coprime
}

/**
 * Compute the modular multiplicative inverse of an integer 'a' modulo 'm'.
 * The modular inverse is an integer 'x' such that (a * x) % m = 1. This function
 * uses an iterative version of the Extended Euclidean Algorithm to find such an 'x',
 * if it exists. If 'a' and 'm' are not coprime (i.e., their GCD is not 1), then the
 * modular inverse does not exist, which is indicated by returning 0 when 'm' equals 1.
 * 
 * Note: The function assumes 'a' and 'm' are positive, and 'm' is greater than 1.
 *
 */
int mod_inverse_iterative(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0; // No inverse exists

    // Apply extended Euclid Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}

/**
 * Generate a pair of prime numbers from a predefined list of 8-bit prime numbers.
 * This function is designed to ensure that the product of the two primes is at least 256,
 * making it suitable for demonstrations or educational purposes where small primes can be used.
 * The primes are selected randomly from the list until a valid pair is found, where validity
 * is determined by their product meeting the specified minimum value. The selected prime numbers
 * are then assigned to the provided pointers.
 *
 */
void generate_prime_pq(uint8_t *p, uint8_t *q) {
    // Define a static array of 8-bit prime numbers
    static uint8_t primes[] = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
            47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
            107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
            167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
            229, 233, 239, 241, 251
        };
		
	// Calculate the total number of primes in the array
	size_t prime_count = sizeof(primes) / sizeof(uint8_t);
	// Continuously attempt to select a valid pair of primes
	do {
		// Randomly select indices for two potential prime numbers
        int p_idx = rand() % prime_count;
        int q_idx = rand() % prime_count;

		// Check if the product of the two primes is at least 256
        // This ensures the RSA modulus n = p*q will have a minimum value
        if (((uint16_t)primes[p_idx] * (uint16_t)primes[q_idx]) >= 256u) {
            *p = primes[p_idx];
            *q = primes[q_idx];
            return;
        }
		// If the pair is not valid, the loop continues to select a new pair
    } while (1); // Loop until a valid pair is found
}

/**
 * Generate a pair of public and private keys for RSA encryption.
 * 
 * This function selects two random prime numbers p and q, computes their product n = pq,
 * and calculates the totient (phi = (p-1)(q-1)). It then selects an encryption exponent e
 * that is coprime with phi and calculates the decryption exponent d as the modular inverse of e mod phi.
 * The public key is {e, n} and the private key is {d, n}.
 * 
 */
void rsa_generate_keys(uint16_t *ptr_e, uint16_t *ptr_d, uint16_t *ptr_n) {

    uint8_t p, q;
    uint16_t n, phi;
    uint16_t e, d;

    // Initialize random number generator with process ID as the seed for reproducibility
    srand((unsigned int)getpid());

    // Generate two distinct prime numbers p and q for RSA
    generate_prime_pq(&p, &q);
    
    #if DEBUG 
    printf("p = %u, q = %u\n", p, q);
    #endif

    // Compute n = p * q, which will serve as the modulus for both keys
    n = (uint16_t)p * (uint16_t)q;

    // Compute Euler's totient function phi(n) = (p-1) * (q-1), necessary for e and d
    phi = (uint16_t)(p - 1) * (uint16_t)(q - 1);

    // Select an encryption exponent e from [2, phi(n)-1] that is coprime with phi(n)
    e = rand() % (phi - 2) + 2; // Ensures 1 < e < phi and coprime with phi

    // Ensure e is coprime with phi, if not, find the next coprime number
    while (!coprime_check(e, phi)) {
        e = (e == (phi - 1)) ? 2 : (e + 1);
    }

    // Compute d, the modular multiplicative inverse of e modulo phi
    d = mod_inverse_iterative(e, phi);

    // Output the generated keys
    *ptr_e = e;
    *ptr_d = d;
    *ptr_n = n;
}