#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"


#define MAX_LENGTH 100

typedef struct {
    char pseudo[MAX_LENGTH];
    char password[MAX_LENGTH];
} Credential;

int isPseudoTaken(const char *pseudo, FILE *file) {
    Credential user;
    rewind(file);
    while (fscanf(file, "%s", user.pseudo) == 1) {
        if (strcmp(user.pseudo, pseudo) == 0) { return 1; }  // Pseudo already taken
    }
    return 0;  // Pseudo available
}

int connection_inscription(int menu, char * pseudo, char * password){

    int i;
    int authSuccess = 0;
    Credential cred, user;

    FILE *file = fopen("credentials.txt", "r+");  
    if (file == NULL) {
        perror("Error opening the file.");
        return 0;
    }

    printf("Hi, welcome to Awale.\nPlease login [1] or create an account [2].\n");
    scanf("%d", &i);

    if (i == 1) {
        menu = 1;
        while (menu == 1) {
            printf("Please enter your pseudo : ");
            scanf("%s", pseudo);
            printf("Welcome %s ! ", pseudo);
            printf("Please enter your password : ");
            scanf("%s", password);

            rewind(file);
            while (fscanf(file, "%s %s", cred.pseudo, cred.password) == 2) {
                if (strcmp(pseudo, cred.pseudo) == 0 && strcmp(password, cred.password) == 0) {
                    authSuccess = 1;
                    break;
                }
            }
            
            if (authSuccess == 0) {
                printf("Your identification did not work.\n");
            } else {
                printf("Your identification worked !\n\n");
                menu = 3;
            }
        }
    } else if (i == 2) {
        do {
            printf("Enter your pseudo : ");
            scanf("%s", user.pseudo);

            if (isPseudoTaken(user.pseudo, file) != 0) {
                printf("This pseudo is already taken. Please choose another.\n");
            }else{ menu = 2;}
        } while (menu !=2);

        printf("Enter your password : ");
        scanf("%s", user.password);

        fseek(file, 0, SEEK_END);  
        if (fprintf(file, "\n%s %s", user.pseudo, user.password) < 0) {
            perror("Error writing to the file.");
            exit(EXIT_FAILURE);
        }
        
        strcpy(pseudo, user.pseudo);
        strcpy(password, user.password);
        printf("Your inscription worked !\n");
        menu = 3;
    } else {
        printf("You chose an out-of-range option.\n");
    }

    fclose(file);

    return menu;
}

int main() {

    int i;
    char *pseudo = malloc(64 * sizeof(char));
    char *password = malloc(64 * sizeof(char));
    int menu = connection_inscription(0, pseudo, password);
    printf("-------- %s %s \n", pseudo, password);

    while(menu==3){
        printf("\nWelcome to your Awale menu. What do you want to do? \n[1]Consult the ongoing games [2]Consult the online pseudo \n[3]Check your profile        [4]Challenge another player \n[5]Disconnect\n");
        scanf("%d", &i);

        if(i==1){
            printf("Here are the ongoing games :\nGive the id of the one you want to watch.\n");
        }else if(i==2){
            printf("Here are the online players :\nWhat do you want to do? [1]Add a friend [2]Chat with someone \n[3]Look at a bio\n");
        }else if(i==3){
            printf("Here are your profile :\nWhat do you want to do? [1]Change mode [2]Consult your biography\n[3]Consult yout list of friends\n");
            
            if(i==1){
                printf("You are in  mode. Do you want to change ? [1]Yes [2]No");
            }else if(i==2){

            }else if(i==3){

            }

        }else if(i==4){
            printf("Which player do you want to challenge ? :\n Give the pseudo of the one you want to challenge.\n");
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


    free(pseudo);
    free(password);
    return 0;
}