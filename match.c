#include "match.h"


// Fonction pour créer une instance de la "classe"
Match* game_create(Client* client1,Client* client2,Game* game){
    Match* objet = (Match*)malloc(sizeof(Match));

    //assignation aléatoire, c1 est le premier à jouer

    if(objet!=NULL){

        srand(time(NULL));
        if(rand()%2==0){
            objet->c1=client1;
            objet->c2=client2;
        }else{
            objet->c2=client1;
            objet->c1=client2;
        }

        objet->g=game;


    }
    
    return objet;
}

// Fonction pour détruire une instance de la "classe"
void game_destroy(Game* objet) {
    free(objet);
}


    


