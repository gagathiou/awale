#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <history.h>


History* history_create(Game * game){

    History* objet = (History*)malloc(sizeof(History));

    if (objet != NULL) {
        objet->moves = createList();
        objet->game = game;
        objet->state=0;
    }

    return objet;
}
void history_destroy(History* objet){
     free(objet);
}
void history_print(History* objet){
    printf("History | list of moves : \n objet->state");
    printList(objet->moves);
    printf("\n game: ");
    //player_print(objet->game);
    printf("\n state : %d\n", objet->state);

}
