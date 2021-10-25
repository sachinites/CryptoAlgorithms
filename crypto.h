/*
 * =====================================================================================
 *
 *       Filename:  crypto.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/24/2021 10:52:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ABHISHEK SAGAR (), sachinites@gmail.com
 *   Organization:  Cisco Systems ( March 2021 - Present, Previous : Juniper Networks
 *
 * =====================================================================================
 */

#ifndef __CRYPTO__
#define __CRYPTO__

#include "crypto_math.h"

#define FEISTEL_ROUNDS   20

typedef uint32_t (*round_fn) (uint32_t *input, uint32_t key) ;

typedef struct feistel_cipher_ {
    struct {
        uint32_t key;
        /* 64 bit Encryption output */
        uint32_t LE;
        uint32_t RE;
        /* 64 bit Decryption output */
        uint32_t LD;
        uint32_t RD;
    } round[FEISTEL_ROUNDS];
    /* Round function ptr */
    round_fn round_fn_ptr;

    uint32_t FE_OUT[2];
    uint32_t FD_OUT[2];

} feistel_cipher_t;

/* An Encryption fn to convert 64 bit plain txt to 64 bit 
    cipher txt using feistel cipher Algorithm */
void
feistel_encrypt (feistel_cipher_t *f_cipher, uint64_t *plain_txt);

/* A Decryption fn to convert a  64 bit cipher text to 64 bit 
plain text */
void
feistel_decrypt (feistel_cipher_t *f_cipher, uint64_t *cipher_txt);

void
feistel_cipher_instance_init (feistel_cipher_t *f_cipher, 
                                               round_fn round_fn_ptr,
                                               uint32_t keys[FEISTEL_ROUNDS]);

void
feistel_print (feistel_cipher_t *f_cipher);

#endif 
