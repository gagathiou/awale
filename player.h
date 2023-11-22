#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "List.h"

// Définition de la structure représentant la "classe"
typedef struct {

    char* pseudo;
    char* password;
    char* bio;
    int state;
    List* friends;

    // Déclaration des membres de la classe
    
} Player;

// Déclaration des fonctions associées à la "classe"
Player* player_create(char* name, char* pw);
void player_destroy(Player* objet);
void player_print(Player* objet);

#endif  // PLAYER_H
