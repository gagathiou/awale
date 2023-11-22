#ifndef HISTORY_H
#define HISTORY_H

#include <List.h>

// Définition de la structure représentant la "classe"
typedef struct {
    // Déclaration des membres de la classe
    List moves;
    Game game;
    int state;
} History;

// Déclaration des fonctions associées à la "classe"
History* creer(int valeur1, const char* valeur2);
void detruire(History* objet);
void afficher(History* objet);

#endif  // HISTORY_H
