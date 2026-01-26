#include "bellman.h"

int algorithme_bellman_ford(Graphe* g, int id_depart, int id_arrivee) {
    // 1. INITIALISATION
    float* distances = (float*)malloc(sizeof(float) * g->nb_noeuds);
    int* parents = (int*)malloc(sizeof(int) * g->nb_noeuds);

    for (int i = 0; i < g->nb_noeuds; i++) {
        distances[i] = FLT_MAX;
        parents[i] = -1;
    }
    distances[id_depart] = 0.0;

    printf("\n--- LANCEMENT BELLMAN-FORD (De %d vers %d) ---\n", id_depart, id_arrivee);

    // 2. RELAXATION RÉPÉTÉE (V-1 fois)
    // C'est ici la différence majeure : on boucle brutalement sur tout le graphe
    for (int i = 1; i <= g->nb_noeuds - 1; i++) {
        int changement = 0; // Petite optimisation : si rien ne bouge, on arrête

        // On parcourt chaque noeud
        for (int u = 0; u < g->nb_noeuds; u++) {
            // On parcourt toutes les arêtes sortantes de ce noeud
            Arete* a = g->tableau_noeuds[u].aretes;
            while (a != NULL) {
                int v = a->destination;
                float poids = a->latence;

                // Si on a trouvé un chemin plus court vers V en passant par U
                if (distances[u] != FLT_MAX && distances[u] + poids < distances[v]) {
                    distances[v] = distances[u] + poids;
                    parents[v] = u;
                    changement = 1;
                }
                a = a->suivant;
            }
        }
        if (!changement) break; // Si plus rien ne change, on a fini plus tôt
    }

    // 3. DÉTECTION DE CYCLES NÉGATIFS (Étape de sécurité supplémentaire)
    // On refait un tour. Si on peut encore raccourcir un chemin, c'est qu'il y a une boucle infinie négative.
    for (int u = 0; u < g->nb_noeuds; u++) {
        Arete* a = g->tableau_noeuds[u].aretes;
        while (a != NULL) {
            int v = a->destination;
            float poids = a->latence;
            if (distances[u] != FLT_MAX && distances[u] + poids < distances[v]) {
                printf("ERREUR CRITIQUE : Cycle de poids negatif detecte !\n");
                free(distances);
                free(parents);
                return 0; // Échec
            }
            a = a->suivant;
        }
    }

    // 4. AFFICHAGE DU RÉSULTAT
    if (distances[id_arrivee] == FLT_MAX) {
        printf("Aucun chemin trouve.\n");
    } else {
        printf("CHEMIN TROUVE (Bellman-Ford) ! Latence : %.2f ms\n", distances[id_arrivee]);
        // Reconstruction simple du chemin
        printf("Arrivee %d", id_arrivee);
        int courant = id_arrivee;
        while (parents[courant] != -1) {
            printf(" <- %d", parents[courant]);
            courant = parents[courant];
        }
        printf("\n");
    }

    free(distances);
    free(parents);
    return 1; // Succès
}