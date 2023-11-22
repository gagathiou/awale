#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Fonction pour créer une instance de la "classe"
Game* game_create(Player* player1,Player* player2){
    Game* objet = (Game*)malloc(sizeof(Game));

    //génération de la seed en fonction de l'heure actuelle
    srand(time(NULL));

    if (objet != NULL) {
        //tirage au sort, le p1 est toujours premier à jouer
        if(rand()%2==0){
            objet->p1=player1;
            objet->p2=player2;
        }else{
            objet->p2=player1;
            objet->p1=player2;
        }
        
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
    game->board[move]=0;
}

void game_printBoard(Game* game){
    char* boardDisplay=(char*)malloc(sizeof(char)*70);
    for(int j=1;j>=0;j--){

    
        for(int i=0;i<6;i++){
            strcat(boardDisplay," -");
        }
        strcat(boardDisplay," \n");
        for(int i=0;i<6;i++){
            strcat(boardDisplay,"|");
            char* nb_seed=(char*)malloc(sizeof(char)*5);
            sprintf(nb_seed,"%d",game->board[i+6*j]);
            strcat(boardDisplay,nb_seed);
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



bool game_isLegalMove(Game* game, int move, int playerId) { //playerId à 0 si p1 et 1 si p2
    bool res = true; // Initialisez res à true par défaut

    // Vérifiez si la case spécifiée par le mouvement est valide
    if (game->board[move] <= 0 || move % 6 != playerId) {
        res = false;
    } else {
        // Vérifiez si la ligne est vide
        bool lineEmpty = true;
        for (int i = 0; i < 6; i++) {
            if (game->board[i + ((playerId + 1) % 2) * 6] != 0) {
                lineEmpty = false;
                break; // Aucune nécessité de continuer si la ligne n'est pas vide
            }
        }

        // Vérifiez si la ligne est vide et si le mouvement est valide pour une ligne vide
        if (lineEmpty && (move % 6) + game->board[move] >= 6) {
            res = false;
        }
    }

    return res;
}



int game_isFinished(Game* game,int playerId){ //retourne 0 si la partie n'est pas finie, 1 si p1 a gagné et 2 si p2 a gagné et 3 si égalité, playerId correspond au joueur qui va jouer
    bool lineEmpty=true;
    int res=0;

    if(game->scores[(playerId+1)%2]>=25){
        res=((playerId+1)%2)+1;
    }else{
        for(int i=0;i<6;i++){
            if (game->board[i+((playerId+1)%2)*6]!=0){
                lineEmpty=false;
            }
        }

        

        if(lineEmpty){
            bool famine=true;
            for(int i=0;i<6;i++){
                if(game->board[i+playerId*6]+i>=6){
                    famine=false;
                }
            }
            if(famine){
                int total=0;
                for(int i=0;i<6;i++){
                    total+=game->board[i+playerId*6];
                }
                game->scores[playerId]+=total;

                if(game->scores[0]>game->scores[1]){
                    res=1;
                }else if (game->scores[0]<game->scores[1]){
                    res=2;

                }else{
                    res=3;
                }
            }
        }
    }

    return res;
}

    


