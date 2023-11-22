#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour créer une instance de la "classe"
Player* player_create(char* name, char* pw){
    Player* objet = (Player*)malloc(sizeof(Player));

    if (objet != NULL) {
        objet->pseudo = name;
        objet->password=pw;
        objet->state=0;
        objet->bio="";
        objet->friends=createList();

    }

    return objet;
}

// Fonction pour détruire une instance de la "classe"
void player_destroy(Player* objet) {
    free(objet);
}

// Fonction pour afficher les membres de la "classe"
void player_print(Player* objet) {
    printf("Psuedo : %s\nPw : %s\nBio : %s\nState : %i\n",objet->pseudo,objet->password,objet->bio,objet->state);
}
