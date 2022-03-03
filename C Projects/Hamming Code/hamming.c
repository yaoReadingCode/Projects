#include "hamming.h"

#include "bm.h"
#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int lookup[16] = { 0, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, 1, 0,
    HAM_ERR }; // lookup table

int uc; // stats counters
int crr;

uint8_t ham_encode(BitMatrix *G, uint8_t msg) { // encodes msg
    BitMatrix *m = bm_from_data(msg, 4); // gets message matrix from msg
    BitMatrix *c = bm_multiply(
        m, G); // gets hamming code for message by multipliying message matrix with generator matrix
    uint8_t code = bm_to_data(c); // gets uint8 code back from matrix c
    bm_delete(&m); // free memory allocated for matrix m and c
    bm_delete(&c);
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, 8); // creates matrix out of code
    BitMatrix *e
        = bm_multiply(c, Ht); // gets error matrix by multiplying hamming code with h transpose
    uint8_t err = bm_to_data(e); // gets error uint8 from error matrix
    if (err == 0) {
        bm_delete(&c); // free memory if no error
        bm_delete(&e);
        return HAM_OK;
    } else {
        if (lookup[err]
            == HAM_ERR) { // if err syndrome points to ham err, more than 1 error to correct
            uc += 1; // adds 1 to uncorrected
            bm_delete(&c); // free memory
            bm_delete(&e);
            return HAM_ERR;
        } else {
            uint8_t eb = bm_get_bit(c, 0,
                lookup
                    [err]); // sets eb to bit that is incorrect (i.e if bit is supposed to be 0 and is 1, then it gets flipped vise versa as well
            if (eb == 0) { // if 0 then gets flipped to 1
                bm_set_bit(e, 0, lookup[err]); // sets bit to 1
                *msg = bm_to_data(e); // return corrected msg
                crr += 1; // adds 1 to corrected counter
                bm_delete(&c); // free memory
                bm_delete(&e);
                return HAM_CORRECT;
            } else {
                bm_clr_bit(e, 0, lookup[err]); // if 1 then gets flipped to 0
                *msg = bm_to_data(e); // returns corrected message
                crr += 1; // adds 1 to corrected counter
                bm_delete(&c); // frees memory
                bm_delete(&e);
                return HAM_CORRECT;
            }
        }
    }
}
