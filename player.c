#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour créer une instance de la "classe"
Player* creer(char* name, char* pw){
    Player* objet = (Player*)malloc(sizeof(Player));

    if (objet != NULL) {
        objet->pseudo = name;
        objet->password=pw;
        objet->state=0;
        objet->bio="";
        List l;
        objet->friends=l.createList();

    }

    return objet;
}

// Fonction pour détruire une instance de la "classe"
void detruire(Player* objet) {
    free(objet);
}

// Fonction pour afficher les membres de la "classe"
void afficher(Player* objet) {
    printf("Psuedo : %s\nPw : %s\nBio : %s\nState : %i\n",objet->pseudo,objet->password,objet->bio,objet->state);
}
