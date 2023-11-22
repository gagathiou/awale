#ifndef MACLASSE_H
#define MACLASSE_H

// Définition de la structure représentant la "classe"
typedef struct {
    // Déclaration des membres de la classe
    List moves;
    Game game;
    int state;
} History;

// Déclaration des fonctions associées à la "classe"
MaClasse* MaClasse_creer(int valeur1, const char* valeur2);
void MaClasse_detruire(MaClasse* objet);
void MaClasse_afficher(MaClasse* objet);

#endif  // MACLASSE_H
