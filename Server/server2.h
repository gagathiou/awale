#ifndef SERVER_H
#define SERVER_H

#ifdef WIN32

#include <winsock2.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define CRLF        "\r\n"
#define PORT         1977
#define MAX_CLIENTS     100

#define BUF_SIZE    1024

#include "client2.h"
#include "../game.h"

typedef struct{
    Game* g;
    Client* c1;
    Client* c2;
    Client* spectators[MAX_CLIENTS];
    int nb_spectators;

} Match;

static void init(void);
static void end(void);
static void app(void);
static int init_connection(void);
static void end_connection(int sock);
static int read_client(SOCKET sock, char *buffer);
static void write_client(SOCKET sock, const char *buffer);
static void send_message_to_all_clients(Client *clients, Client client, int actual, const char *buffer, char from_server);
static void remove_client(Client *clients, int to_remove, int *actual);
static void clear_clients(Client *clients, int actual);
void show_menu(Client* client);
void defy(Client* clients,Client* c, const char* buffer, int actual);
Match* match_create(Client* client1,Client* client2,Game* game);
void match_destroy(Match* objet);
Match init_match(Client* c1, Client* c2,int actual_game);
void reject(Client* c1, Client* c2);
void play(Client * c,char* buffer,Match* matchs,int actual_match);
int checkConnected(Client* c,Client* clients,int actual);
void disconnect(Client* c);
void specGame(Match* matchs,int index_match,Client* c,int actual_match);
void stopSpecGame(Match* matchs, Client* c);
void remove_match(Match* matchs, int to_remove, int* actual_match);
void remove_spectator(Client** spectators, int to_remove, int* actual_spectator);
void listMatchs(Match* matchs, Client* c,int actual_game);
void resign(Match* m,Client* resigner,Client* opponent);
void answerOfferEndGame(Match* matchs,Match* m, Client* c, int stop,int actual_match);
void offerEndGame( Client* c);

#endif /* guard */
