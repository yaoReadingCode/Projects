#include "names.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {
  uint64_t players;
  printf("Number of players: ");
  if ((scanf("%" SCNu64, &players) != 1 || players < 2) || players > 10) {
    fprintf(stderr, "Invalid number of players.\n");
    return 1;
  }
  uint64_t seed;
  printf("Random seed: ");
  if (scanf("%" SCNu64, &seed) != 1 || seed > UINT32_MAX) {
    fprintf(stderr, "Invalid random seed.\n");
    return 1;
  }
  printf("seed = %" PRIu64 "\n", seed);
  srandom(seed);
  int lives[10] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
  uint64_t alive = players;
  uint64_t LN;
  LN = 0;
  uint64_t LR;
  LR = 0;
  uint64_t round;
  round = 1;
  while (alive > 1) {
    LN = 0;
    LR = 0;
    printf("Round %" PRIu64, round);
    for (uint64_t i = 0; i <= (players - 1); i = i + 1) {
      uint64_t first = (random() % 6);
      uint64_t second = (random() % 6);
      while (lives[i] == 0) {
        i += 1;
      }
      printf("\n - %s rolls %s...", names[i], rolls[first][second]);
      if (i == 0) {
        LR = 0;
        LN = first + second;
      }
      if (lives[0] == 0) {
        LN = first + second;
        LR = i;
      }
      if (LN > (first + second)) {
        printf("hi");
        LR = i;
        LN = first + second;
      }
      if ((first + second) == 10) {
        if (lives[(i + players - 1) % players] > 0) {
          printf("sparkles %s ", names[(i + players - 1) % players]);
        }
        if (lives[(i + players - 1) % players] == 0) {
          printf("resurrects %s ", names[(i + players - 1) % players]);
          alive += 1;
        }
        if (lives[(i + 1) % players] > 0) {
          printf("sparkles %s ", names[(i + 1) % players]);
        }
        if (lives[(i + 1) % players] == 0) {
          printf("resurrects %s ", names[(i + 1) % players]);
          alive += 1;
        }
        lives[(i + players - 1) % players] += 1;
        lives[(i + 1) % players] += 1;
      }
    }
    printf("\n%s is forced to eat garlic!\n", names[LR]);
    lives[LR] = lives[LR] - 1;
    if (lives[LR] == 1) {
      printf("%s has 1 life remaining.\n", names[LR]);
    }
    if (lives[LR] == 0) {
      printf("%s has died.\n", names[LR]);
      alive = alive - 1;
    }
    for (uint32_t i = 0; i <= (players - 1); i += 1) {
      if (alive > 1) {
        break;
      } else {
        if (lives[i] > 0) {
          printf("%s wins the garlic game!\n", names[i]);
          break;
        }
      }
    }
    if (lives[LR] > 1) {
      printf("%s has %d lives remaining.\n", names[LR], lives[LR]);
    }
    round = round + 1;
  }

  return 0;
}
