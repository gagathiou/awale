#ifndef GAME_H
#define GAME_H

#include <player.h>

typedef struct {
    int board [12];
    Player p1;
    Player p2;
    int scores[2];
} Game;

Game* creer(int valeur1, const char* valeur2);
void detruire(Game* objet);
void afficher(Game* objet);

#endif  // GAME_H

//test agathe, va te faire foutre victor