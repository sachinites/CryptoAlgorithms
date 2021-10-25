/*
 * =====================================================================================
 *
 *       Filename:  crypto_math.c
 *
 *    Description: This file implements the general maths routines used un Cryptography 
 *
 *        Version:  1.0
 *        Created:  10/24/2021 01:01:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ABHISHEK SAGAR (), sachinites@gmail.com
 *   Organization:  Cisco Systems ( March 2021 - Present, Previous : Juniper Networks
 *
 * =====================================================================================
 */


#include <stdio.h>
#include "crypto_math.h"

uint64_t
gcd(int64_t a, int64_t b) {

    /* because
     * gcd (a,b) = gcd(-a, b) = gcd(a, -b) = gcd (-a, -b)*/
    if (a < 0) a = a * -1;
    if (b < 0) b = b * -1;

    if (a < b) {

        int64_t temp;
        temp = a;
        a = b;
        b = temp;
    }

    int64_t rem = (a % b);

    if (!rem) return b;

    return gcd(b, rem);
}

void print_bits32 (uint32_t n) {

    int i = 0;
    for (i = 0; i < 32; i++) {

        if (n & (1 << 31)) {
            printf ("1");
        }
        else {
            printf("0");
        }
        n = n << 1;
    }
}

void print_bits64 (uint64_t n) {

    int i = 0;
    for (i = 0; i < 64; i++) {

        if (n & (1 << 63)) {
            printf ("1");
        }
        else {
            printf("0");
        }
        n = n << 1;
    }
}

void  print_hex(uint32_t n) {

    printf ("%x", n);
}

#if 0
int
main(int argc, char **argv) {

    int64_t a = 1160718174;
    int64_t b = 316258250;

    uint64_t gcd_r = gcd(a, b);
    
    /*Expected answer is 1078*/
    printf("gcd(%ld, %ld) = %lu\n", a, b, gcd_r);

    return 0;
}
#endif