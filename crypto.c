#include <stdio.h>
#include <memory.h>
#include <arpa/inet.h>
#include "crypto.h"

/* An Encryption fn to produce 64 bit cipher text from 64 bit 
    plain txt using feistel cipher Algorithm */
void
feistel_encrypt (feistel_cipher_t *f_cipher, uint64_t *plain_txt) {

    uint8_t i;
    uint32_t *LE_OLD, *RE_OLD;
    uint32_t *LE_NEW, *RE_NEW;
    uint32_t key, temp;
    uint32_t rnd_fn_output;

    LE_OLD = (uint32_t *)plain_txt;
    RE_OLD = (uint32_t *)plain_txt + 1;

    LE_NEW = LE_OLD;
    RE_NEW = RE_OLD;

    printf ("\n");
    printf ("Input ::  ");
    print_hex(*LE_OLD);
    printf ("  ");
    print_hex(*RE_OLD);
    printf ("\n");

    for (i = 0; i < FEISTEL_ROUNDS; i++) {

        key = f_cipher->round[i].key;
        printf ("Round No : %d, key = %x\n", i, key);
        rnd_fn_output = f_cipher->round_fn_ptr(RE_OLD, key);
        printf ("rnd_fn_output :: ");
        print_hex(rnd_fn_output);
        printf ("\n");
        temp = *RE_OLD;
        *RE_NEW = rnd_fn_output ^ (*LE_OLD);
        printf ("*RE_NEW = rnd_fn_output ^ (*LE_OLD) = ");
        print_hex(rnd_fn_output);
        printf (" ^ ");
        print_hex(*LE_OLD);
        printf (" = ");
        print_hex(*RE_NEW);
        printf ("\n");
        *LE_NEW = temp;
        printf ("*LE_NEW = RE_OLD = ");
        print_hex(*LE_NEW);
        printf ("\n");

        /* Save the output for record */
        f_cipher->round[i].LE = *LE_NEW;
        f_cipher->round[i].RE = *RE_NEW;
    }

    /* now SWAP LE_NEW and RE_NEW */
    temp = *LE_NEW;
    *LE_NEW = *RE_NEW;
    *RE_NEW = temp;

    f_cipher->FE_OUT[0] = *LE_NEW;
    f_cipher->FE_OUT[1] = *RE_NEW;

    printf ("Final Cipher = ");
    print_hex(f_cipher->FE_OUT[0]);
    printf ("  ");
    print_hex(f_cipher->FE_OUT[1]);
    printf ("\n");
}

/* A Decryption fn to produce 64 bit plain text from 64 bit 
cipher text */
void
feistel_decrypt (feistel_cipher_t *f_cipher, uint64_t *cipher_txt) {

    int8_t i;
    uint32_t *LD_OLD, *RD_OLD;
    uint32_t *LD_NEW, *RD_NEW;
    uint32_t key;
    uint32_t rnd_fn_output;
    uint32_t temp;

    LD_OLD = (uint32_t *)cipher_txt;
    RD_OLD = (uint32_t *)cipher_txt + 1;

    LD_NEW = LD_OLD;
    RD_NEW = RD_OLD;

    printf ("\n");
    printf ("Input ::  ");
    print_hex(*LD_OLD);
    printf ("  ");
    print_hex(*RD_OLD);
    printf ("\n");
    
    for (i = FEISTEL_ROUNDS -1; i >= 0; i--) {

        key = f_cipher->round[i].key;
        printf ("Round No : %d, key = %x\n", i, key);
        rnd_fn_output = f_cipher->round_fn_ptr(RD_OLD, key);
        printf ("rnd_fn_output :: ");
        print_hex(rnd_fn_output);
        printf ("\n");
        temp = *RD_OLD;
        *RD_NEW = rnd_fn_output ^ (*LD_OLD);
        printf ("*RD_NEW = rnd_fn_output ^ (*LD_OLD) = ");
        print_hex(rnd_fn_output);
        printf (" ^ ");
        print_hex(*LD_OLD);
        printf (" = ");
        print_hex(*RD_NEW);
        printf ("\n");
        *LD_NEW = temp;
        printf ("LD_NEW = RD_OLD = ");
        print_hex(*LD_NEW);
        printf ("\n");
        /* Save the output for record */
        f_cipher->round[i].LD = *LD_NEW;
        f_cipher->round[i].RD = *RD_NEW;
    }

    /* now SWAP LD_NEW and RD_NEW */
    temp = *LD_NEW;
    *LD_NEW = *RD_NEW;
    *RD_NEW = temp;

    f_cipher->FD_OUT[0] = *LD_NEW;
    f_cipher->FD_OUT[1] = *RD_NEW;

    printf ("Final De Cipher = ");
    print_hex(f_cipher->FD_OUT[0]);
    printf ("  ");
    print_hex(f_cipher->FD_OUT[1]);
    printf ("\n");
}

void
feistel_cipher_instance_init (feistel_cipher_t *f_cipher, 
                                               round_fn round_fn_ptr,
                                               uint32_t keys[FEISTEL_ROUNDS]) {

    uint8_t i = 0;

    memset (f_cipher, 0 , sizeof (feistel_cipher_t));
    f_cipher->round_fn_ptr = round_fn_ptr;

    for (i = 0; i < FEISTEL_ROUNDS; i++) {

        f_cipher->round[i].key = keys[i];
        f_cipher->round[i].LE = 0;
        f_cipher->round[i].RE = 0;
        f_cipher->round[i].LD = 0;
        f_cipher->round[i].RD = 0;
    }

    f_cipher->FE_OUT[0] = 0;
    f_cipher->FE_OUT[1] = 0;
    f_cipher->FD_OUT[0] = 0;
    f_cipher->FD_OUT[1] = 0;
}

void
feistel_print (feistel_cipher_t *f_cipher) {

    uint8_t i = 0;

    for (i = 0; i < FEISTEL_ROUNDS - 1; i++) {

        printf ("Rnd %d.  LE : %-8x RE : %-8x LD : %-8x RD : %-8x\n", 
            i, f_cipher->round[i].LE, f_cipher->round[i].RE,
            f_cipher->round[ i + 1].LD,
            f_cipher->round[i + 1].RD);
    }    
}


/* Driver program to test Feistel Cipher Implemtation */
uint32_t 
feistel_cipher_round_test_fn (uint32_t *input, uint32_t key) {
    printf ("%s() ::  ", __FUNCTION__);
    print_hex(*input);
    printf (" xor ");
    print_hex(key);
    printf("\n");
    return (*input) ^ key;
}

/* Keys for each round, taken randomly*/
static uint32_t keys[] = {0xccd5, 0x1e240, 0x9fbf1}; 

static void
feistel_cipher_driver_program () {

    feistel_cipher_t f_cipher;
    feistel_cipher_instance_init (&f_cipher, feistel_cipher_round_test_fn, keys);

    uint64_t input = 9686081839;
    printf ("Original Input plain text = %lu\n", input);

    feistel_encrypt (&f_cipher, &input);
    printf ("Cipher = %lu %lu\n", input, *(uint64_t *)f_cipher.FE_OUT);
    feistel_print  (&f_cipher);

    feistel_decrypt (&f_cipher, &input);
    printf ("Recovered plain txt = %lu %lu\n",  input,  *(uint64_t *)f_cipher.FD_OUT);

    feistel_print  (&f_cipher);
}

int
main(int argc, char **argv) {

    feistel_cipher_driver_program();
    return 0;
}