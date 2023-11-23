#ifndef LISTE_P_H
#define LISTE_P_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "player.h"

typedef struct Node_P {
    Player data;
    struct Node_P* next;
} Node_P;

typedef struct {
    Node_P* head;
} List_P;


List_P* list_p_create();
void list_p_destroy(List_P* list);
void list_p_insertFront(List_P* list, Player player);
void list_p_printPlayers(List_P* list);

#endif