#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void init_stats(unsigned char *players, unsigned short *won_games, unsigned short *lost_games) {
    *players = 0;
    *won_games = 0;
    *lost_games = 0;
}