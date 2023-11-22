#ifndef GAME_H
#define GAME_H

#include <player.h>

typedef struct {
    int board [12];
    Player* p1;
    Player* p2;
    int scores[2];
} Game;

<<<<<<< HEAD
Game* create(int valeur1, const char* valeur2);
void destroy(Game* objet);
void print(Game* objet);
=======
Game* game_create(Player* player1,Player* player2);
void game_destroy(Game* objet);
void game_print(Game* objet);
>>>>>>> d3eb2503a2cc2b06f24cb805cccc374b3076bb08

#endif  // GAME_H

