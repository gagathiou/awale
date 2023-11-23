#ifndef FRIENDS_H
#define FRIENDS_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "List_P.h"
#include "player.h"

typedef struct {
    Player * player;
    List_P* list_of_friends;    
} Friends;

Friends * friends_create(Player * player, List_P* list_of_friends);
void friends_destroy(Friends* objet);
void friends_print(Friends* objet);

#endif  // FRIENDS_H
