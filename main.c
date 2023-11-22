#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"

int main(){

    int i;
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
        printf("Please enter your pseudo : ");
        scanf("%s", pseudo);
        printf("Welcome %s ! ", pseudo);
        printf("Please enter your password : ");
        scanf("%s", password);
        printf("Your password is %s.\n", password);

        // Credential cred;
        // int authSuccess = 0;
        // if (strcmp(username, cred.username) == 0 && strcmp(password, cred.password) == 0) {
        //     authSuccess = 1;  // Authentification réussie
        // }

    }else if (i==2){
        printf("Please give us a pseudo to create your account.\n");
    }else{
        printf("You chose an out of range option. \n");
    }

    Player* p=player_create("Torvik","AgatheNul");
    player_print(p);
    Player* p2=player_create("Gagathe","VictorSuper");
    player_print(p2);

    Game* g=game_create(p,p2);

    game_print(g);

    player_destroy(p);

    

    return 0;
}