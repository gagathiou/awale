#ifndef PLAYER_H
#define PLAYER_H

// Définition de la structure représentant la "classe"
typedef struct {
    // Déclaration des membres de la classe
    char* pseudo;
    char* password;
    char* bio;
    int state;
    List* friends;
    
} Player;

// Déclaration des fonctions associées à la "classe"
Player* creer(char* name, char* pw){

    Player* p;
    p->pseudo=name;
    p->password=pw;
    p->bio="";
    p->state=0;
    p->friends=List.createList();
    
}
void Player_detruire(Player* objet){
    free(Player->pseudo);
    free(Player->bio);
    free(Player->pw);
    free(Player->friends)
    free(Player);

}
void Player_afficher(Player* objet){
    printf("pseudo : %s\npw : %s\nbio : %s\nstate : %i\n",Player->pseudo,Player->password,Player->bio,Player->state);
}

#endif  // PLAYER_H
