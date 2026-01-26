#include "securite.h"

// Fonction "cachée" (helper) qui fait le travail récursif
int dfs_cycle_recursif(Graphe* g, int u, int* etats, int* parent) {
    // On marque le noeud actuel comme "En cours de visite" (GRIS = 1)
    etats[u] = 1;

    Arete* a = g->tableau_noeuds[u].aretes;
    while (a != NULL) {
        int v = a->destination;

        // Cas 1 : On tombe sur un noeud "GRIS" -> C'est un cycle !
        if (etats[v] == 1) {
            printf("[ALERTE SECURITE] Cycle de routage detecte : %s -> %s\n", 
                   g->tableau_noeuds[u].nom, g->tableau_noeuds[v].nom);
            return 1; // Vrai, il y a un cycle
        }

        // Cas 2 : On tombe sur un noeud "BLANC" -> On continue l'exploration
        if (etats[v] == 0) {
            parent[v] = u;
            if (dfs_cycle_recursif(g, v, etats, parent)) {
                return 1; // Si l'enfant a trouvé un cycle, on remonte l'info
            }
        }
        
        // Cas 3 : Noeud "NOIR", on ignore (déjà traité)
        a = a->suivant;
    }

    // Fin de l'exploration pour ce noeud, on le marque "Terminé" (NOIR = 2)
    etats[u] = 2;
    return 0;
}

int detecter_cycles(Graphe* g) {
    // Allocation du tableau d'états (tout à 0 au début)
    int* etats = (int*)calloc(g->nb_noeuds, sizeof(int));
    int* parent = (int*)malloc(g->nb_noeuds * sizeof(int));
    int cycle_trouve = 0;

    printf("\n--- ANALYSE DE SECURITE (Recherche de cycles) ---\n");

    // On doit lancer le DFS sur chaque noeud non visité
    // (car le graphe peut être en plusieurs morceaux déconnectés)
    for (int i = 0; i < g->nb_noeuds; i++) {
        if (etats[i] == 0) {
            if (dfs_cycle_recursif(g, i, etats, parent)) {
                cycle_trouve = 1;
                // On ne s'arrête pas, on cherche tous les cycles potentiels
                // ou on break si on veut juste savoir s'il y en a un.
                break; 
            }
        }
    }

    if (!cycle_trouve) {
        printf("Reseau sain : Aucun cycle de routage detecte.\n");
    }

    free(etats);
    free(parent);
    return cycle_trouve;
}