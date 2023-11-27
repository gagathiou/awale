#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "Chat.h"

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 256
#define MAX_PLAYERS 2


Chat* chat_create(Player* player1, Player* player2) {
    Chat* chat = malloc(sizeof(Chat));
    chat->players[0] = player1;
    chat->players[1] = player2;
    chat->messageCount = 0;
    return chat;
}

void chat_destroy(Chat* chat) {
    free(chat);
}

void sendMessage(Chat* chat, Player* sender, const char* message) {
    if (chat->messageCount < MAX_MESSAGES) {
        sprintf(chat->messages[chat->messageCount], "%s: %s", sender->pseudo, message);
        chat->messageCount++;
    } else {
        printf("La boîte de messages est pleine. Impossible d'envoyer le message.\n");
    }
}

void displayMessages(Chat* chat) {
    printf("Affichage des messages :\n");
    for (int i = 0; i < chat->messageCount; ++i) {
        printf("%s\n", chat->messages[i]);
    }
}