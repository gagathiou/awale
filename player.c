#ifndef PLAYER_H
#define PLAYER_H

// Définition de la structure représentant la "classe"
typedef struct {
    // Déclaration des membres de la classe
    char* Pseudo;
    char* bio;
    int state;
    List friends;
    
} Player;

// Déclaration des fonctions associées à la "classe"
Player* creer(char* pseudo){
    
}
void Player_detruire(Player* objet);
void Player_afficher(Player* objet);

#endif  // PLAYER_H
