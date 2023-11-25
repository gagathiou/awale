#ifndef CLIENT_H
#define CLIENT_H


struct Client;  // Forward declaration

#include "server.h"
#include "../player.h"



typedef struct
{
   SOCKET sock;
   char name[BUF_SIZE];
   int state;
   struct Client* opponent;
   int index_actual_game;
   Player player;
}Client;

#endif /* guard */
