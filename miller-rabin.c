#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/* Global basename */
char *BASENAME = "miller-rabin";

/* Usage */
void usage(int status) {
    fprintf(stderr, "usage: %s -n NUM -k ROUNDS\n", BASENAME);
    fprintf(stderr, "\tNUM    - odd integer to be tested\n");
    fprintf(stderr, "\tROUNDS - number of rounds of testing\n");
    exit(status);
}

/* Compute power */
long power(long x, unsigned int y, long p) {
    long res = 1;
    x = x % p;

    while (y > 0) {
        if (y & 1)
            res = (res*x) % p;

        y = y >> 1;
        x = (x*x) % p;
    }
    return res;
}

/* Miller Rabin */
bool miller_rabin_test(long d, long n) {
    /* Randomly choose a value */
    long a = 2 + rand() % (n - 4);
    /* Compute x = a^(2^) */
    long x = power(a, d, n);
    /* If this result is 1 or n - 1, it is probably prime */
    if (x == 1 || x == n - 1) return true;

    /* Repeat r - 1 times  */
    while (d != n - 1) {
        /* Compute x^2 mod n */
        x = (x * x) % n;
        d *= 2;

        /**/
        if (x == 1) return false;
        /* */
        if (x == n - 1) return true;
    }
    return false;
}

/* Test primality for an input */
bool test_primality(long n, int k) {

    if (n <= 1 || n == 4 )  return false;
    if (n <= 3)             return true;

    /* In the case that n is prime, n - 1 must be even.
     * So we can write:
     * n = 2^d * r + 1
     */
    long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    /* Perform Miller-Rabin up to k times */
    for (int i = 0; i < k; i++)
        if (!miller_rabin_test(d, n))
            return false;

    /* Return true if none of the Miller-Rabin tests fail
     * It is therefore probably prime
     */
    return true;
}

/* Main */
int main(int argc, char **argv) {

    /* Time */
    time_t t;
    srand((unsigned) time(&t));

    /*  */
    char *nvalue = NULL;
  	char *kvalue = NULL;
  	int c;
  	opterr = 0;
  	while ((c = getopt (argc, argv, "n:k:")) != -1)
        switch (c) {
            case 'n':
                nvalue = optarg;
                break;
            case 'k':
                kvalue = optarg;
                break;
            case '?':
                if (optopt == 'n' || optopt == 'k')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                usage(1);
            default:
                abort();
        }

    if (!kvalue || !nvalue) {
        fprintf(stderr, "N and K values are required.\n");
        usage(1);
    }

    /* Convert input */
    long num = atol(nvalue); 
    int rounds = atoi(kvalue);
    if (num == 0 || rounds == 0) {
        fprintf(stderr, "Invalid values.\n");
        exit(1);
    }

    /* Run primality test */
    bool result = test_primality(num, rounds);

    /* Output */
    if (result) {
        printf("probably prime\n");
    } else {
        printf("composite\n");
    }

    return 0;
}
