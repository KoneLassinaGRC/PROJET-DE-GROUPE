#include "backtrack.h"

// Variables globales temporaires pour simplifier la récursivité
// (Dans un projet pro, on passerait tout en arguments, mais ici on reste simple)
int chemin_actuel[100];
int visite[100]; // Pour éviter de tourner en rond
Solution meilleure_solution;

void explorer(Graphe* g, int u, int dest, float min_bp, float max_cout, 
              float latence_acc, float cout_acc, int profondeur) {
    
    // 1. ELAGAGE (Optimisation)
    // Si on a déjà dépassé le coût max, on arrête TOUT DE SUITE
    if (cout_acc > max_cout) return;

    // Si on a déjà trouvé un chemin complet ailleurs qui est plus rapide que notre trajet actuel,
    // ça ne sert à rien de continuer ici.
    if (meilleure_solution.trouve && latence_acc >= meilleure_solution.latence_totale) return;

    // On note qu'on passe par ici
    chemin_actuel[profondeur] = u;
    visite[u] = 1;

    // 2. CAS DE BASE : On est arrivé !
    if (u == dest) {
        // On a trouvé un chemin valide !
        // Comme on a passé l'élagage ci-dessus, il est forcément meilleur ou égal au précédent.
        meilleure_solution.trouve = 1;
        meilleure_solution.latence_totale = latence_acc;
        meilleure_solution.cout_total = cout_acc;
        meilleure_solution.longueur_chemin = profondeur + 1;
        
        // On sauvegarde ce chemin comme étant le nouveau champion
        for(int i=0; i<=profondeur; i++) {
            meilleure_solution.chemin[i] = chemin_actuel[i];
        }
    } else {
        // 3. RECURSIVITE : On explore les voisins
        Arete* a = g->tableau_noeuds[u].aretes;
        while (a != NULL) {
            int v = a->destination;

            // On n'y va que si :
            // - Pas déjà visité (pour ne pas tourner en rond)
            // - La bande passante est suffisante (Contrainte stricte)
            if (!visite[v] && a->bande_passante >= min_bp) {
                explorer(g, v, dest, min_bp, max_cout, 
                         latence_acc + a->latence, 
                         cout_acc + a->cout, 
                         profondeur + 1);
            }
            a = a->suivant;
        }
    }

    // 4. BACKTRACKING : On ressort du noeud (pour permettre d'autres chemins de passer par là)
    visite[u] = 0;
}

Solution rechercher_chemin_contraintes(Graphe* g, int depart, int arrivee, float min_bp, float max_cout) {
    // Initialisation
    meilleure_solution.trouve = 0;
    meilleure_solution.latence_totale = FLT_MAX;
    
    for(int i=0; i<g->nb_noeuds; i++) visite[i] = 0;

    printf("\n--- RECHERCHE AVANCEE (Backtracking) ---\n");
    printf("Contraintes : BP >= %.0f Mbps, Cout <= %.0f\n", min_bp, max_cout);

    // Lancement de la récursion
    explorer(g, depart, arrivee, min_bp, max_cout, 0.0, 0.0, 0);

    // Affichage résultat
    if (meilleure_solution.trouve) {
        printf(">>> SUCCES : Chemin valide ! Latence : %.2f ms | Facture : %.0f FCFA\n",
            meilleure_solution.latence_totale, 
            meilleure_solution.cout_total);
        printf(">>> Trajet : ");
        for (int i = 0; i < meilleure_solution.longueur_chemin; i++) {
            printf("%d ", meilleure_solution.chemin[i]);
            if(i < meilleure_solution.longueur_chemin - 1) printf("-> ");
        }
        printf("\n");
    } else {
        printf("Echec : Aucun chemin ne respecte ces contraintes.\n");
    }

    return meilleure_solution;
}