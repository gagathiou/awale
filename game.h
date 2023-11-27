#ifndef GAME_H
#define GAME_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


typedef struct{
    int board[12];
    int scores[2];
    int turn;
} Game;

// Function prototypes related to Game
Game *game_create();
void game_destroy(Game *object);
void game_print(Game *object);
void game_playMove(Game *game, int move);
bool game_isLegalMove(Game *game, int move);
char *game_printBoard(Game *game);
int game_isFinished(Game *game);
int game_biggestScore(Game* g);

#endif // GAME_H
