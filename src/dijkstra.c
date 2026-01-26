#include "dijkstra.h"

void algorithme_dijkstra(Graphe* g, int id_depart, int id_arrivee) {
    // 1. INITIALISATION
    // On crée des tableaux pour noter nos découvertes
    float* distances = (float*)malloc(sizeof(float) * g->nb_noeuds);
    int* parents = (int*)malloc(sizeof(int) * g->nb_noeuds);
    int* visites = (int*)calloc(g->nb_noeuds, sizeof(int)); // Tout à 0 (Faux)

    // Au début, toutes les distances sont infinies, sauf le départ
    for (int i = 0; i < g->nb_noeuds; i++) {
        distances[i] = FLT_MAX; // Infini
        parents[i] = -1;        // Pas de parent
    }
    distances[id_depart] = 0.0;

    // On prépare notre file de priorité avec le point de départ
    FilePriorite* file = creer_file();
    enfiler(file, id_depart, 0.0);

    printf("\n--- LANCEMENT DE DIJKSTRA (De %d vers %d) ---\n", id_depart, id_arrivee);

    // 2. BOUCLE PRINCIPALE (Tant qu'il y a des nœuds à explorer)
    while (!est_vide(file)) {
        // A. Choisir le nœud avec la plus petite distance connue
        float dist_actuelle;
        int u = defiler(file, &dist_actuelle);

        // Si on a déjà traité ce nœud (via un chemin plus court trouvé avant), on saute
        if (dist_actuelle > distances[u]) continue;
        
        // Si on est arrivé à destination, on peut s'arrêter (optimisation)
        if (u == id_arrivee) break; 

        visites[u] = 1;

        // B. Explorer les voisins
        Arete* a = g->tableau_noeuds[u].aretes;
        while (a != NULL) {
            int v = a->destination;
            float poids = a->latence; // ICI on choisit de minimiser la LATENCE

            // RELAXATION : Est-ce que passer par U est plus court pour aller à V ?
            if (!visites[v] && distances[u] + poids < distances[v]) {
                distances[v] = distances[u] + poids;
                parents[v] = u; // On note qu'on vient de U
                enfiler(file, v, distances[v]);
            }
            a = a->suivant;
        }
    }

   // 3. RECONSTRUCTION ET AFFICHAGE
    if (distances[id_arrivee] == FLT_MAX) {
        printf("Aucun chemin trouve entre %d et %d.\n", id_depart, id_arrivee);
    } else {
        // --- NOUVEAU : CALCUL DU PRIX TOTAL ---
        float cout_total_calcule = 0;
        int parcours = id_arrivee;
        while (parents[parcours] != -1) {
            int ancetre = parents[parcours];
            // On cherche l'arête qui relie l'ancêtre au noeud actuel pour savoir son prix
            Arete* a = g->tableau_noeuds[ancetre].aretes;
            while (a != NULL) {
                if (a->destination == parcours) {
                    cout_total_calcule += a->cout;
                    break;
                }
                a = a->suivant;
            }
            parcours = ancetre;
        }
        // --------------------------------------

        printf("CHEMIN TROUVE ! Temps : %.2f ms | Cout : %.0f FCFA\n", distances[id_arrivee], cout_total_calcule);
        
        printf("Trajet (a lire de bas en haut) :\n");
        int courant = id_arrivee;
        while (courant != -1) {
            printf(" <- %s (%d)\n", g->tableau_noeuds[courant].nom, courant);
            courant = parents[courant];
        }
    }

    // 4. NETTOYAGE (Très important)
    free(distances);
    free(parents);
    free(visites);
    liberer_file(file);
}