#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"

#define MAX_LENGTH 100


int main(){

    typedef struct {
        char username[MAX_LENGTH];
        char password[MAX_LENGTH];
    } Credential;

    int i;
    int menu = 0;
    int authSuccess = 0;
    Credential cred;
    char * pseudo =malloc(64*sizeof(char));
    char * password = malloc(64*sizeof(char));
    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        perror("Error in the file's opening.");
        return 0; 
    }


    printf("Hi, welcome to Awale.\nPlease login [1] or create an account [2].\n");
    scanf("%d", &i);
    if(i==1){
        menu =1;
        while(menu==1){
            printf("Please enter your pseudo : ");
            scanf("%s", pseudo);
            printf("Welcome %s ! ", pseudo);
            printf("Please enter your password : ");
            scanf("%s", password);
            
            rewind(file);
            while (fscanf(file, "%s %s", cred.username, cred.password) == 2) {
                if (strcmp(pseudo, cred.username) == 0 && strcmp(password, cred.password) == 0) {
                    authSuccess = 1;  // Authentification réussie
                    break;
                }
            }
            if(authSuccess==0){
                printf("Your identification did not work.\n");
            }else{
                printf("Your identification worked !\n\n");
                menu = 3;
            }
        }
    }else if (i==2){
        menu = 2;
        printf("Please give us a pseudo to create your account.\n");
        scanf("%s", pseudo);

        // Vérifier si le pseudo existe déjà
        rewind(file);
        int usernameExists = 0;
        while (fscanf(file, "%s", pseudo) == 2) {
            if (strcmp(cred.username, pseudo) == 0) {
                usernameExists = 1;
                break;
            }
        }

        // if (usernameExists==0) {
        //     printf("This username already exists. Please choose another one.\n");
        // } else {
            printf("Username available! Please enter your password: ");
            scanf("%s", password);

            // Enregistrer les informations dans le fichier
            fprintf(file, "%s %s\n", pseudo, password);

            printf("Registration successful!\n");
            menu = 3;  // Vous pouvez mettre la valeur que vous souhaitez ici pour sortir de la boucle
        // }
    }else{
        printf("You chose an out of range option. \n");
    }

    fclose(file);


    while(menu==3){
        printf("\nWelcome to your Awale menu. What do you want to do? \n[1]Consult the ongoing games [2]Consult the online pseudo \n[3]Check your profile        [4]Challenge another player \n[5]Disconnect");
        scanf("%d", &i);

        if(i==1){
            printf("Here are the ongoing games :\n");
        }else if(i==2){
            printf("Here are the online players :\n");
        }else if(i==3){
            printf("Here are your profile :\n");
        }else if(i==4){
            printf("Which player do you want to challenge ? :\n");
            // Player* p=player_create("Torvik","AgatheNul");
            // player_print(p);
            // Player* p2=player_create("Gagathe","VictorSuper");
            // player_print(p2);
            // Game* g=game_create(p,p2);
            // game_print(g);
            // player_destroy(p);

            Player* p1=player_create("victor","ls");
            Player* p2=player_create("agathe","autier");
            Game* g=game_create(p1,p2);
            int joueur=0;
            
            while(game_isFinished(g,joueur)==0){
                
                game_printBoard(g);
                printf("quel coup jouer\n");
                int coup;
                scanf("%d",&coup);
                while(!game_isLegalMove(g,coup,joueur)){
                    printf("mauvais coup, quel coup jouer\n");
                    scanf("%d",&coup);
                }
                game_playMove(g,coup,joueur);

                joueur=(joueur+1)%2;
            }
        }else if(i==5){
            printf("You chose to disconnect, goodbye and see you soon on Awale.\n");
            menu = 4;
        }else{
            printf("You chose an out of range option.\n");
        }
    }

    return 0;
}