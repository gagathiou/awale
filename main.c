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
        fclose(file);

    }else if (i==2){
        printf("Please give us a pseudo to create your account.\n");
    }else{
        printf("You chose an out of range option. \n");
    }



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
            Player* p=player_create("Torvik","AgatheNul");
            player_print(p);
            Player* p2=player_create("Gagathe","VictorSuper");
            player_print(p2);
            Game* g=game_create(p,p2);
            game_print(g);
            player_destroy(p);
        }else if (i==5){
            printf("You chose to disconnect, goodbye and see you soon on Awale.\n");
            menu = 4;
        }else{
            printf("You chose an out of range option.\n");
        }
    }

    return 0;
}