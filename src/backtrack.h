#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "graphe.h"
#include <float.h>

// Structure pour stocker le résultat
typedef struct Solution {
    int trouve;             // 1 si un chemin est trouvé, 0 sinon
    float latence_totale;   // La latence du meilleur chemin
    int chemin[100];        // La liste des noeuds (IDs)
    float cout_total;       // Le coût
    int longueur_chemin;    // Nombre de noeuds dans le chemin
} Solution;

// Fonction principale
Solution rechercher_chemin_contraintes(Graphe* g, int depart, int arrivee, float min_bp, float max_cout);

#endif