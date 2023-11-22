#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour créer une instance de la "classe"
Game* game_create(Player* player1,Player* player2){
    Game* objet = (Game*)malloc(sizeof(Game));

    if (objet != NULL) {
        objet->p1=player1;
        objet->p2=player2;
        for (int i=0;i<12;i++){
            objet->board[i]=4;
        }
        objet->scores[0]=0;
        objet->scores[1]=0;
    }

    return objet;
}

// Fonction pour détruire une instance de la "classe"
void game_destroy(Game* objet) {
    free(objet);
}

// Fonction pour afficher les membres de la "classe"
void game_print(Game* objet) {
    printf("Player 1 :\n");
    player_print(objet->p1);
    printf("Score : %i\n",objet->scores[0]);
    printf("Player 2 :\n");
    player_print(objet->p2);
    printf("Score : %i\n",objet->scores[1]);
}

void game_playMove(Game* game, int move) {
    nb_seed=game->board[move];
    for (int i=nb_seed;i>0;i--){
        game->board[(move+i)%12]+=1;
    }
}
