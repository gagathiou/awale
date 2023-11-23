#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
//#include "List_P.h"

typedef struct {
    char* pseudo;
    char* password;
    char* bio;
    int state;
    //List_P* friends;    
} Player;

Player* player_create(char* name, char* pw);
void player_destroy(Player* objet);
void player_print(Player* objet);

#endif  // PLAYER_H
