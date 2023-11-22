#include <stdio.h>
#include <stdlib.h>
#include "player.h"

int main(){

    Player* p=player_create("Torvik","AgatheNul");
    player_print(p);
    player_destroy(p);

    return 0;
}