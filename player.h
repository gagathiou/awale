#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <List.h>

// Définition de la structure représentant la "classe"
typedef struct {

    char* Pseudo;
    char* bio;
    int state;
    List friends;

    // Déclaration des membres de la classe
    
} Player;

// Déclaration des fonctions associées à la "classe"
Player* creer(char* pseudo);
void Player_detruire(Player* objet);
void Player_afficher(Player* objet);

#endif  // PLAYER_H
