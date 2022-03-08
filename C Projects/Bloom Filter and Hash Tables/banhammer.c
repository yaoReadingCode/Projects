#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "ht:f:ms"
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_])*" // regex

int main(int argc, char **argv) {
    int opt = 0; // initalize filter size and table size
    uint32_t fsize = 1048576; // 2^20
    uint32_t tsize = 10000;
    bool mtf = false;
    bool stats = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -m           Enable move-to-front rule.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            return 0;
        case 't':
            tsize = atoi(optarg); // sets table size to inputed
            if (tsize == 0) {
                printf("Invalid hash table size.\n");
                return 0;
            }
            break;
        case 'f':
            fsize = atoi(optarg); // sets filter size to inputted
            if (fsize == 0) {
                printf("Invalid Bloom filter size.\n");
                return 0;
            }
            break;
        case 's': // prints out stats
            stats = true;
            break;
        case 'm': mtf = true; break;
        default:
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -m           Enable move-to-front rule.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            break;
        }
    }
    // create bloom filter and hash table
    BloomFilter *bf = bf_create(fsize);
    HashTable *ht = ht_create(tsize, mtf);
    // open badspeak and newspeak
    FILE *badspeak = fopen("badspeak.txt", "r");
    char bad[2048];
    char old[2048];
    char new[2048];
    // read in words from text file and put them into bf and ht
    while (fscanf(badspeak, "%s", bad) != EOF) {
        bf_insert(bf, bad);
        ht_insert(ht, bad, NULL);
    }
    FILE *newspeak = fopen("newspeak.txt", "r");
    // ^^
    while (fscanf(newspeak, "%s %s\n", old, new) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    }
    regex_t re;
    // create regex using regcomp
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        exit(1);
    }
    // create two linked lists to hold banned words onto and print at end
    LinkedList *ospk = ll_create(mtf);
    LinkedList *nspk = ll_create(mtf);
    char *word;
    while ((word = next_word(stdin, &re)) != NULL) {
        // check if word is in bf
        if (bf_probe(bf, word) == true) {
            // if it is, then make sure by checking in hash table
            Node *L = ht_lookup(ht, word);
            if (L != NULL) {
                // if it is a newspeak word, add to newspeak list
                if (L->newspeak) {
                    ll_insert(nspk, word, L->newspeak);
                } else { // else add to oldspeak list
                    ll_insert(ospk, word, NULL);
                }
            }
        }
    }
    if (stats) {
        // calculate average seek length, hash table load, and bloom filter load
        double asl = ((double) links / (double) seeks);
        double htl = 100 * (((double) ht_count(ht)) / ((double) ht_size(ht)));
        double bfl = 100 * (((double) bf_count(bf)) / ((double) bf_size(bf)));
        // print stats
        printf("Seeks: ");
        printf("%" PRIu64, seeks);
        printf("\nAverage seek length: ");
        printf("%lf", asl);
        printf("\nHash table load: ");
        printf("%lf%%", htl);
        printf("\nBloom filter load: ");
        printf("%lf%%", bfl);
        printf("\n");
        printf("ht size is:");
        printf("%" PRIu32, ht_size(ht));
        printf("\n");
        printf("bf size is: ");
        printf("%" PRIu32, bf_size(bf));
        printf("\n");
        printf("links: ");
        printf("%" PRIu64, links);
        printf("\n");
        ll_delete(&ospk);
        ll_delete(&nspk);
        ht_delete(&ht);
        bf_delete(&bf);
        return 0;
    }
    // if stats are not true
    // check if both oldspeak and newspeak words were used if so
    // print out corresponding message
    if ((ll_length(ospk) != 0) && (ll_length(nspk) != 0)) {
        printf("%s", mixspeak_message);
        ll_print(ospk);
        ll_print(nspk);
        ll_delete(&ospk);
        ll_delete(&nspk);
        ht_delete(&ht);
        bf_delete(&bf);
        return 0;
    }
    // if only either olspeak or newspeak were used
    // print corresponding message for each senario
    if (ll_length(ospk) != 0) {
        printf("%s", badspeak_message);
        ll_print(ospk);
        ll_delete(&ospk);
        ll_delete(&nspk);
        ht_delete(&ht);
        bf_delete(&bf);
        return 0;
    }
    if (ll_length(nspk) != 0) {
        printf("%s", goodspeak_message);
        ll_print(nspk);
        ll_delete(&ospk);
        ll_delete(&nspk);
        ht_delete(&ht);
        bf_delete(&bf);
        return 0;
    }
    // else return nothing and free memory
    ll_delete(&ospk);
    ll_delete(&nspk);
    ht_delete(&ht);
    bf_delete(&bf);
    return 0;
}
