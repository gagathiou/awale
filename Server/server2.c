#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server2.h"


static void init(void)
{
#ifdef WIN32
   WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      puts("WSAStartup failed !");
      exit(EXIT_FAILURE);
   }
#endif
}

static void end(void)
{
#ifdef WIN32
   WSACleanup();
#endif
}

static void app(void)
{
   SOCKET sock = init_connection();
   char buffer[BUF_SIZE];
   /* the index for the array */
   int actual = 0;
   int actual_match=0;
   int max = sock;
   /* an array for all clients */
   Client clients[MAX_CLIENTS];
   Match matchs[MAX_CLIENTS];

   fd_set rdfs;

   while(1)
   {
      int i = 0;
      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add the connection socket */
      FD_SET(sock, &rdfs);

      /* add socket of each client */
      for(i = 0; i < actual; i++)
      {
         FD_SET(clients[i].sock, &rdfs);
      }

      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      /* something from standard input : i.e keyboard */
      if(FD_ISSET(STDIN_FILENO, &rdfs))
      {
         /* stop process when type on keyboard */
         break;
      }
      else if(FD_ISSET(sock, &rdfs))
      {
         /* new client */
         SOCKADDR_IN csin = { 0 };
         size_t sinsize = sizeof csin;
         int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
         if(csock == SOCKET_ERROR)
         {
            perror("accept()");
            continue;
         }

         /* after connecting the client sends its name */
         if(read_client(csock, buffer) == -1)
         {
            /* disconnected */
            continue;
         }

         /* what is the new maximum fd ? */
         max = csock > max ? csock : max;

         FD_SET(csock, &rdfs);

         Client c = { csock };
         strncpy(c.name, buffer, BUF_SIZE - 1);
         clients[actual] = c;
         clients[actual].state=0;
         show_menu(&(clients[actual]));
         actual++;
      }
      else
      {
         int i = 0;
         for(i = 0; i < actual; i++)
         {
            /* a client is talking */
            if(FD_ISSET(clients[i].sock, &rdfs))
            {
               Client* client = &(clients[i]);
               int c = read_client(clients[i].sock, buffer);
               /* client disconnected */
               if(c == 0)
               {
                  closesocket(clients[i].sock);
                  remove_client(clients, i, &actual);
                  strncpy(buffer, client->name, BUF_SIZE - 1);
                  strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                  send_message_to_all_clients(clients, *client, actual, buffer, 1);
               }
               else
               {
                  char* etat[10];
                  sprintf(etat, "%d", client->state);
                  write_client(client->sock,etat);
                  switch(client->state){

                     case 0 : //menu de sélection

                        if(strcmp("1",buffer)==0){
                           client->state=1;
                           write_client(client->sock,"Ecrivez le pseudo que vous voulez défier");
                        }
                        

                        break;
                     
                     case 1 : //choisit qui défier

                        defy(clients,client,buffer,actual);

                        break;
                     
                     case 2 : //en attente de la réponse de l'adversaire

                        

                        break;

                     case 3 : //répond à une demande de défi

                        if(strcmp("1",buffer)==0){
                              
                              matchs[actual_match]=init_match(client,client->opponent,actual_match);
                              actual_match++;

                        }else if(strcmp("2",buffer)==0){

                              reject(client,client->opponent);

                        }

                        break;

                     case 4 : //en partie
                        Match* m = &(matchs[client->index_actual_game]);
                        int connection=checkConnected(m->c1,clients,actual)+checkConnected(m->c2,clients,actual);
                           if(connection!=2){
                              surrender(client);
                           }
                        if((client==m->c1&&m->g->turn==0)||(client==m->c2&&m->g->turn==1)){
                           
                           play(client,buffer,matchs);
                        }
                        

                        break;


                     default :

                        break;

                  }
               }
               break;
            }
         }
      }
   }

   clear_clients(clients, actual);
   end_connection(sock);
}

void show_menu(Client* client){

   write_client(client->sock,"Veuillez choisir ce que vous voulez faire : \n");
   write_client(client->sock,"1. Défier quelqu'un\n");
}

Match init_match(Client* c1, Client* c2,int actual_game){

   c1->state=4;
   c2->state=4;
   c1->index_actual_game=actual_game;
   c2->index_actual_game=actual_game;


   Game* g=game_create();

   Match* m=match_create(c1,c2,g);

   write_client(m->c1->sock,game_printBoard(g));
   write_client(m->c2->sock,game_printBoard(g));
   write_client(m->c2->sock,"En attente du coup de l'autre joueur\n");

   return *m;

}

void surrender(Client* c){
   write_client(c->sock,"Votre adversaire s'est déconnecté, appuyez sur n'importe quelle touche pour retourner au menu\n");
   c->state=0;
   show_menu(c);
}

void play(Client * c,char* buffer,Match* matchs){
   Match* m=&(matchs[c->index_actual_game]);
   int move=atoi(buffer);
   if(game_isLegalMove(m->g,move)){
      game_playMove(m->g,move);
      int res=game_isFinished(m->g);
      if(res==0){
         if(m->g->turn==0){
            m->g->turn=1;
            write_client(m->c1->sock,"En attente du coup de l'autre joueur\n");
            write_client(m->c2->sock,"A vous de jouer (nombre entre 6 et 11)\n");
            write_client(m->c1->sock,game_printBoard(m->g));
            write_client(m->c2->sock,game_printBoard(m->g));            
            for(int i=0;i<(m->nb_spectators);i++){
               write_client(m->spectators[i].sock,game_printBoard(m->g));
            }
         }else{
            m->g->turn=0;
            write_client(m->c1->sock,"A vous de jouer (nombre entre 0 et 5)\n");
            write_client(m->c2->sock,"En attente du coup de l'autre joueur\n");
            write_client(m->c1->sock,game_printBoard(m->g));
            write_client(m->c2->sock,game_printBoard(m->g));
            for(int i=0;i<(m->nb_spectators);i++){
               write_client(m->spectators[i].sock,game_printBoard(m->g));
            }
         }
      }else if(res==1||res==2){
         char winner[2];
         sprintf(winner, "%d", res);
         
         write_client(m->c1->sock,game_printBoard(m->g));
         write_client(m->c2->sock,game_printBoard(m->g));
         for(int i=0;i<(m->nb_spectators);i++){
            write_client(m->spectators[i].sock,game_printBoard(m->g));
            write_client(m->spectators[i].sock,strcat(strcat("Le gagnant est le joueur ",winner),"\n"));
         }
         
         write_client(m->c1->sock,strcat(strcat("Le gagnant est le joueur ",winner),"\n"));
         write_client(m->c2->sock,strcat(strcat("Le gagnant est le joueur ",winner),"\n"));
         m->c1->state=5;
         m->c2->state=5;
      }
      else{
         write_client(m->c1->sock,game_printBoard(m->g));
         write_client(m->c2->sock,game_printBoard(m->g));
         for(int i=0;i<(m->nb_spectators);i++){
            write_client(m->spectators[i].sock,game_printBoard(m->g));
            write_client(m->spectators[i].sock,"Egalité\n");
         }
         write_client(m->c1->sock,"Egalité\n");
         write_client(m->c2->sock,"Egalité\n");
         m->c1->state=5;
         m->c2->state=5;
      }
   }else{
      if(m->g->turn==0){
         write_client(m->c1->sock,"Vous ne pouvez pas jouer ce coup, choisissez en un autre\n");
      }else{
         write_client(m->c2->sock,"Vous ne pouvez pas jouer ce coup, choisissez en un autre\n");
      }
      
   }
}

void reject(Client* c1, Client* c2){
   write_client(c2->sock,"L'adversaire a refusé le défi, retour au menu\n");
   c1->state=0;
   c2->state=0;
   show_menu(c1);
   show_menu(c2);
}

void defy(Client* clients,Client* c, const char* buffer, int actual){

   printf("appel a defy\n");

   for (int i=0;i<actual;i++){
      if(strcmp(clients[i].name,buffer)==0){
         if(clients[i].state!=0){
            write_client(c->sock,"Le joueur est occcupé, retour au menu\n");
            c->state=0;
            show_menu(c);
            break;
         }else{
            c->state=2;
            write_client(clients[i].sock,strcat(c->name," vous a défié, 1 pour accepter et 2 pour refuser\n"));
            clients[i].state=3;
            clients[i].opponent=c;
            c->opponent=&(clients[i]);
            break;
         }
      }
   }
   if(c->state==1){
      write_client(c->sock,"Le client n'existe pas ou n'est pas connecté, retour au menu\n");
      c->state=0;
      show_menu(c);      
   }
}

static void clear_clients(Client *clients, int actual)
{
   int i = 0;
   for(i = 0; i < actual; i++)
   {
      closesocket(clients[i].sock);
   }
}

static void remove_client(Client *clients, int to_remove, int *actual)
{
   /* we remove the client in the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
   /* number client - 1 */
   (*actual)--;
}

static void send_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server)
{
   int i = 0;
   char message[BUF_SIZE];
   message[0] = 0;
   for(i = 0; i < actual; i++)
   {
      /* we don't send message to the sender */
      if(sender.sock != clients[i].sock)
      {
         if(from_server == 0)
         {
            strncpy(message, sender.name, BUF_SIZE - 1);
            strncat(message, " : ", sizeof message - strlen(message) - 1);
         }
         strncat(message, buffer, sizeof message - strlen(message) - 1);
         write_client(clients[i].sock, message);
      }
   }
}

static int init_connection(void)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   sin.sin_addr.s_addr = htonl(INADDR_ANY);
   sin.sin_port = htons(PORT);
   sin.sin_family = AF_INET;

   if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }

   if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static int read_client(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
}

static void write_client(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

int checkConnected(Client* c,Client* clients,int actual){
   for(int i=0;i<actual;i++){
      if ((clients+i)==c){
         return 1;
      }
   }
   return 0;
}

Match* match_create(Client* client1,Client* client2,Game* game){
    Match* objet = (Match*)malloc(sizeof(Match));

    //assignation aléatoire, c1 est le premier à jouer

    if(objet!=NULL){

        srand(time(NULL));
        if(rand()%2==0){
            objet->c1=client1;
            objet->c2=client2;
        }else{
            objet->c2=client1;
            objet->c1=client2;
        }

        objet->g=game;
        objet->nb_spectators=0;


    }
    
    return objet;
}

// Fonction pour détruire une instance de la "classe"
void match_destroy(Match* objet) {
    free(objet);
}

int main()
{
   init();

   app();

   end();

   return EXIT_SUCCESS;
}
