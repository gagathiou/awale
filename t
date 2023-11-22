/ Fonction pour afficher les membres de la "classe"
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
