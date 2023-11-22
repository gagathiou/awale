#ifndef GAME_H
#define GAME_H

// Définition de la structure représentant la "classe"
typedef struct {
    // Déclaration des membres de la classe
    int board [12];
    Player p1;
    Player p2;
    int scores[2];
    History move_played;
} Game;

// Déclaration des fonctions associées à la "classe"
MaClasse* MaClasse_creer(int valeur1, const char* valeur2);
void MaClasse_detruire(MaClasse* objet);
void MaClasse_afficher(MaClasse* objet);

#endif  // GAME_H
