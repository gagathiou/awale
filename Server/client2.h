#ifndef CLIENT_H
#define CLIENT_H

#include "server2.h"

typedef struct Client
{
   SOCKET sock;
   char name[BUF_SIZE];
   int state;
   struct Client* opponent;
   int index_actual_game;
}Client;

#endif /* guard */
