#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player* player_create(char* name, char* pw){
    Player* objet = (Player*)malloc(sizeof(Player));

    if (objet != NULL) {
        objet->pseudo = name;
        objet->password=pw;
        objet->state=0;
        objet->bio="";
        //objet->friends=list_p_create();
    }

    return objet;
}

void player_destroy(Player* objet) {
    free(objet);
}

void player_print(Player* objet) {
    printf("Pseudo : %s\nPw : %s\nBio : %s\nState : %i\n",objet->pseudo,objet->password,objet->bio,objet->state);
}
