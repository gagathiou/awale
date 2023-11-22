#ifndef HISTORY_H
#define HISTORY_H

#include <List.h>
#include <game.h>
typedef struct {
    List * moves;
    Game * game;
    int state; // 0 en cours, 1 terminé
} History;

History* history_create(Game * game);
void history_destroy(History* objet);
void history_print(History* objet);

#endif  // HISTORY_H
