#ifndef GAME_H
#define GAME_H

#include <player.h>
#include <stdbool.h>

typedef struct {
    int board [12];
    Player* p1;
    Player* p2;
    int scores[2];
} Game;


Game* game_create(Player* player1,Player* player2);
void game_destroy(Game* objet);
void game_print(Game* objet);
void game_playMove(Game* game, int move, int playerId);
bool game_isLegalMove(Game* game, int move, int playerId);
void game_printBoard(Game* game); 
int game_isFinished(Game* game,int playerId);


#endif  // GAME_H

