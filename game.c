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

<<<<<<< HEAD
void game_playMove(Game* game, int move) {
    // nb_seed=game->board[move];
    // for (int i=nb_seed;i>0;i--){
    //     game->board[(move+i)%12]+=1;
    // }
=======

//le player 1 joue toujours sur 0 1 2 3 4 5
void game_playMove(Game* game, int move, int playerId) {
    int nb_seed=game->board[move];
    bool get_seed=true;
    for (int i=nb_seed;i>0;i--){
        game->board[(move+i)%12]+=1;       

        if(get_seed==true&&(game->board[(move+i)%12]==2||game->board[(move+i)%12]==3)&&(((move+i)%6)!=playerId)){
            game->scores[move%6]+=game->board[(move+i)%12];
            game->board[(move+i)%12]=0;
        }
    }
>>>>>>> 6669e665a63fd7cf5e106eedab43b6abd88c545e
}

void game_printBoard(Game* game){
    char* boardDisplay=(char*)malloc(sizeof(char)*60);
    for(int j=1;j>=0;j--){

    
        for(int i=0;i<6;i++){
            strcat(boardDisplay," -");
        }
        strcat(boardDisplay," \n");
        for(int i=0;i<6;i++){
            strcat(boardDisplay,"|"+game->board[i+6*j]);
        }
        strcat(boardDisplay,"|\n");
    }
    for(int i=0;i<6;i++){
            strcat(boardDisplay," -");
        }
        strcat(boardDisplay," \n");
    printf("%s",boardDisplay);
    free(boardDisplay);

}

bool game_isLegalMove(Game* game, int move, int playerId){
    bool res;
    if (game->board[move]<0||move%6!=playerId){  //playerId == 0 pour le p1 et ==1 pour le p2
        res=false;
    }
    else{
        res=true;
    }
    return res;
}