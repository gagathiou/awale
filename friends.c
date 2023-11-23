#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "friends.h"


Friends* friends_create(Player * player, List_P* list_of_friends){
    Friends* objet = (Friends*)malloc(sizeof(Friends));

    if (objet != NULL) {
        objet->player = player;
        objet->list_of_friends=list_of_friends;
    }

    return objet;
}
void friends_destroy(Friends* objet){
    free(objet);
}
void friends_print(Friends* objet){
    printf("Player : %s\n",objet->player->pseudo);
    printf("List of friends : \n");
    list_p_printPlayers(objet->list_of_friends);
}