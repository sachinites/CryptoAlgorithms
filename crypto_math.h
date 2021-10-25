/*
 * =====================================================================================
 *
 *       Filename:  crypto_math.h
 *
 *    Description: This file defines the routines for general math used in Cryptography 
 *
 *        Version:  1.0
 *        Created:  10/24/2021 12:25:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ABHISHEK SAGAR (), sachinites@gmail.com
 *   Organization:  Cisco Systems ( March 2021 - Present, Previous : Juniper Networks
 *
 * =====================================================================================
 */

#ifndef __CRYPTO_MATH__
#define __CRYPTO_MATH__

#include <stdint.h>

/*
 * Return a GCD of two integers a and b, where
 * a and b could be any inegers ( -ve, 0, or +ve).
 * Assume
 * gcd (0, 0) = 0
 * gcd (a, 0) = a
 * gcd (0, b) = b
 */
uint64_t
gcd(int64_t a, int64_t b);

void print_bits32 (uint32_t n);
void print_bits64 (uint64_t n);
void  print_hex(uint32_t n);

#endif 
