#ifndef GAME_H
#define GAME_H

#include <player.h>

typedef struct {
    int board [12];
    Player* p1;
    Player* p2;
    int scores[2];
} Game;

Game* game_create(Player* player1,Player* player2);
void game_destroy(Game* objet);
void game_print(Game* objet);
void game_playMove(Game* objet, int move);

#endif  // GAME_H

