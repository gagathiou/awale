#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"

int main(){

    Player* p=player_create("Torvik","AgatheNul");
    player_print(p);
    Player* p2=player_create("Gagathe","VictorSuper");
    player_print(p2);

    Game* g=game_create(p,p2);

    game_print(g);

    player_destroy(p);

    

    return 0;
}