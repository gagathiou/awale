#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "Server/client2.h"
#include <stdbool.h>

typedef struct {
    int board [12];
    Client* c1;
    Client* c2;
    int scores[2];
    int turn;
} Game;


Game* game_create(Player* player1,Player* player2);
void game_destroy(Game* objet);
void game_print(Game* objet);
void game_playMove(Game* game, int move);
bool game_isLegalMove(Game* game, int move);
char* game_printBoard(Game* game); 
int game_isFinished(Game* game);


#endif  // GAME_H

