#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable)); // provided by teacher
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) { // free any lists that have a value
    for (uint32_t i = 0; i < ht_size(*ht); i++) {
        if ((*ht)->lists[i] != NULL) {
            ll_delete(&(*ht)->lists[i]);
        }
    } // free ht
    free(*ht);
    *ht = NULL;
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size; // return size
}

Node *ht_lookup(HashTable *ht, char *oldspeak) { // looks up if word is in hash table
    // if oldspeak is null, then return null
    if (oldspeak == NULL) {
        return NULL;
    }
    // get index by hashing word with salt
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    // if there is no list at that index, then return null because it is a false positive
    if (ht->lists[index] == NULL) {
        return NULL;
    }
    // else return the node
    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // insert list at index in hash table with the node created from oldspeak and newspeak
    // get index by hashing word with salt
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == NULL) {
        LinkedList *nl = ll_create(ht->mtf);
        ht->lists[index] = nl;
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            counter += 1;
        }
    }
    // returns number of lists in hash table
    return counter;
}

void ht_print(HashTable *ht) {
    // prints all lists in hash table
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            printf("Index ");
            printf("%" PRIu32, i);
            printf(" exists and is: \n");
            ll_print(ht->lists[i]);
        }
    }
    return;
}
