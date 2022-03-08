#include "bf.h"

#include "speck.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        //  Grimm's Fairy  Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The  Adventures  of  Sherlock  Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The  Strange  Case of Dr. Jekyll  and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    if (bf) {
        free(*bf);
        bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    // sets bits using all three salts with hash function
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // checks if bits at three salt hash locations are set
    bool first = bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bool second = bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bool third = bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
    if (first && second && third) {
        return true;
    } else {
        return false;
    }
}

uint32_t bf_count(BloomFilter *bf) {
    // counts how many bits are set
    int counter = 0;
    for (uint32_t i = 0; i < bf_size(bf); i += 1) {
        if (bv_get_bit(bf->filter, i) == 1) {
            counter += 1;
        }
    }
    return counter;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
    return;
}
