#ifndef GAME_H
#define GAME_H

#include <player.h>

typedef struct {
    int board [12];
    Player p1;
    Player p2;
    int scores[2];
} Game;

Game* create(int valeur1, const char* valeur2);
void destroy(Game* objet);
void print(Game* objet);

#endif  // GAME_H

