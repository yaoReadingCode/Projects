// Sriharsha Madala
// April 7 2021

#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// This program will implement a game called Left, Right, and Center.
// Each player will start with 3 dollars. They will each roll dice depending
// on how many dice they have, $1 = 1 dice. If they roll left, the player gives
// 1 dollar to the player on the left. If they roll right, the player will give
// 1 dollar to the player on the right. If they roll center, the player puts
// 1 dollar in the center "pot." If the player rolls a circle, nothing happens.
// This goes on until there is only 1 player left. The dice roll is based on a
// random seed.

typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces; // provided by instruction
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

static inline uint32_t right(uint32_t pos, uint32_t players) { //provided by teacher
    return ((pos + players + 1) % players);
}

static inline uint32_t left(uint32_t pos, uint32_t players) { //provided by teacher
    return ((pos + players - 1) % players);
}

static inline uint32_t roll() { //provided by teacher
    return random() % 6;
}

int main(void) {
    uint32_t seed;
    printf("Random seed: ");
    if (scanf("%" SCNu32, &seed) != 1 || seed > UINT32_MAX) { // scans for input for seed
        fprintf(stderr, "How many players? Number of players must be from 1 to 14.\n");
        return 1;
    }
    uint32_t players;
    printf("How many players? ");
    if (scanf("%" SCNu32, &players) != 1 || players < 1
        || players > 14) { // scans for input for players
        fprintf(stderr, "Number of players must be from 1 to 14.\n");
        return 1;
    }
    srandom(seed);
    uint32_t money[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3 }; // initalizes all possible players with 3 dollars
    uint32_t pot = 0; // initalizes pot to $0
    uint32_t in = players; // initalizes players that are in the game to players inputed
    while (in > 1) { // while there are more than 1 player in the game
        for (uint32_t i = 0; i < players; i += 1) { // loops through all players in the game
            if (money[i] >= 1) {
                printf("%s rolls... ", philosophers[i]);
                uint32_t rn = money[i];
                if (rn > 3) {
                    rn = 3;
                }
                for (uint32_t x = 0; (x < rn); x += 1) {
                    uint32_t r = roll();
                    if (die[r]
                        == LEFT) { // gives money to player on left and subtracts money from roller
                        if (money[left(i, players)]
                            == 0) { // if player on the left had no money, then this adds 1 to players left in the game
                            in += 1;
                        }
                        money[left(i, players)] += 1;
                        money[i] = money[i] - 1;
                        printf("gives $1 to %s ", philosophers[left(i, players)]);
                    }
                    if (die[r]
                        == RIGHT) { // gives money to player on right and subtracts money from roller
                        if (money[right(i, players)]
                            == 0) { // if player on right had no money, then this adds 1 to players left in the game
                            in += 1;
                        }
                        money[right(i, players)] += 1;
                        money[i] = money[i] - 1;
                        printf("gives $1 to %s ", philosophers[right(i, players)]);
                    }
                    if (die[r] == CENTER) { // gives money to pot and subtracts money from roller
                        pot += 1;
                        money[i] = money[i] - 1;
                        printf("puts $1 in the pot ");
                    }
                    if (die[r] == PASS) { // nothing happens but it prints "gets a pass"
                        printf("gets a pass ");
                    }
                }
                printf("\n");
                if (money[i]
                    == 0) { // if player has no money left then this subtracts 1 from players in the game
                    in = in - 1;
                }
            }
            if (in == 1) { // breaks if there is only 1 player left in game
                break;
            }
        }
    }
    for (uint32_t i = 0; i < players;
         i += 1) { // only the player left with money wins and takes money in pot
        if (money[i] > 0) {
            printf(
                "%s wins the $%d pot with $%d left in the bank!\n", philosophers[i], pot, money[i]);
        }
    }
    return 0;
}
