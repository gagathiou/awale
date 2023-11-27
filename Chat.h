#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "player.h"

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 256
#define MAX_PLAYERS 2


typedef struct {
    Player* players[MAX_PLAYERS];
    char messages[MAX_MESSAGES][MAX_MESSAGE_LENGTH];
    int messageCount;
} Chat;


Chat* chat_create(Player* player1, Player* player2);
void chat_destroy(Chat* chat);
void sendMessage(Chat* chat, Player* sender, const char* message);
void displayMessages(Chat* chat);


#endif  // CHAT_H
