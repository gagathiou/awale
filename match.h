#ifndef GAME_H
#define GAME_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "Server/client2.h"
#include "game.h"

typedef struct{
    Game* game;
    Client* c1;
    Client* c2;
} Match;

// Function prototypes related to Game
Match *match_create(Client *player1,Client *player2,Game* g);
void match_destroy(Match *object);


#endif // GAME_H
