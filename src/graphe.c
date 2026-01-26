#include "graphe.h"

// 1. Création du graphe
Graphe* creer_graphe(int nb_noeuds_max) {
    // Allocation de la structure principale
    Graphe* g = (Graphe*)malloc(sizeof(Graphe));
    if (g == NULL) {
        printf("Erreur d'allocation mémoire pour le graphe\n");
        exit(1);
    }

    g->nb_noeuds = 0;
    g->capacite_max = nb_noeuds_max;

    // Allocation du tableau de noeuds
    g->tableau_noeuds = (Noeud*)malloc(sizeof(Noeud) * nb_noeuds_max);
    if (g->tableau_noeuds == NULL) {
        printf("Erreur d'allocation mémoire pour les noeuds\n");
        free(g); // On nettoie avant de quitter
        exit(1);
    }

    return g;
}

// 2. Ajout d'un noeud (ex: Abobo)
void ajouter_noeud(Graphe* g, int id, const char* nom) {
    if (g->nb_noeuds >= g->capacite_max) {
        printf("Erreur : Capacité maximale du graphe atteinte !\n");
        return;
    }

    // On récupère l'emplacement vide
    int index = g->nb_noeuds; 
    
    g->tableau_noeuds[index].id = id;
    // On copie le nom en sécurité (max 49 caractères + \0)
    strncpy(g->tableau_noeuds[index].nom, nom, 49);
    g->tableau_noeuds[index].nom[49] = '\0'; // Sécurité fin de chaîne
    
    // Au début, ce noeud n'est connecté à personne
    g->tableau_noeuds[index].aretes = NULL;

    g->nb_noeuds++;
}

// 3. Ajout d'une arête (Connexion)
void ajouter_arete(Graphe* g, int src, int dest, float latence, float bp, float cout, int sec) {
    // Étape A : Trouver le noeud source
    // (Ici on suppose que l'ID correspond à l'index pour simplifier au début)
    if (src < 0 || src >= g->nb_noeuds) {
        printf("Erreur : Noeud source %d invalide\n", src);
        return;
    }

    // Étape B : Créer la nouvelle arête en mémoire
    Arete* nouvelle_arete = (Arete*)malloc(sizeof(Arete));
    if (nouvelle_arete == NULL) {
        printf("Erreur malloc arête\n");
        exit(1);
    }

    // Étape C : Remplir les données [cite: 61, 62, 63, 64, 65]
    nouvelle_arete->destination = dest;
    nouvelle_arete->latence = latence;
    nouvelle_arete->bande_passante = bp;
    nouvelle_arete->cout = cout;
    nouvelle_arete->securite = sec;

    // Étape D : Insérer en TÊTE de liste (Le plus rapide O(1))
    // La nouvelle arête pointe vers l'ancienne première arête
    nouvelle_arete->suivant = g->tableau_noeuds[src].aretes;
    
    // Le noeud source pointe maintenant vers la nouvelle arête
    g->tableau_noeuds[src].aretes = nouvelle_arete;
}

// 4. Affichage (Pour vérifier que ça marche)
void afficher_graphe(Graphe* g) {
    printf("\n--- ETAT DU RESEAU ---\n");
    for (int i = 0; i < g->nb_noeuds; i++) {
        Noeud* n = &g->tableau_noeuds[i];
        printf("Noeud %d (%s) est connecte a :\n", n->id, n->nom);
        
        Arete* a = n->aretes;
        while (a != NULL) {
            printf("  -> Noeud %d [Lat: %.1fms | BP: %.1f | Cout: %.0f FCFA | Sec: %d]\n", 
                   a->destination, a->latence, a->bande_passante, a->cout, a->securite);
            a = a->suivant; // On passe au suivant
        }
        if (n->aretes == NULL) printf("  (Aucune connexion sortante)\n");
    }
    printf("----------------------\n");
}

// 5. Nettoyage mémoire (OBLIGATOIRE pour éviter les fuites [cite: 344])
void liberer_graphe(Graphe* g) {
    if (g == NULL) return;

    // Pour chaque noeud, on doit libérer sa liste d'arêtes
    for (int i = 0; i < g->nb_noeuds; i++) {
        Arete* a = g->tableau_noeuds[i].aretes;
        while (a != NULL) {
            Arete* a_supprimer = a;
            a = a->suivant;      // On sauvegarde le suivant
            free(a_supprimer);   // On supprime l'actuel
        }
    }

    // Libérer le tableau de noeuds et la structure graphe
    free(g->tableau_noeuds);
    free(g);
    printf("Memoire liberee avec succes.\n");
}
// Ajout dans graphe.c

void charger_graphe(Graphe* g, const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    char type_ligne[10];
    int id, src, dest, sec;
    char nom[50];
    float lat, bp, cout;

    printf("Chargement du fichier %s...\n", nom_fichier);

    // Format du fichier attendu :
    // NOEUD id nom
    // ARETE src dest latence bp cout securite
    while (fscanf(fichier, "%s", type_ligne) != EOF) {
        if (strcmp(type_ligne, "NOEUD") == 0) {
            fscanf(fichier, "%d %s", &id, nom);
            ajouter_noeud(g, id, nom);
        } else if (strcmp(type_ligne, "ARETE") == 0) {
            fscanf(fichier, "%d %d %f %f %f %d", &src, &dest, &lat, &bp, &cout, &sec);
            ajouter_arete(g, src, dest, lat, bp, cout, sec);
        }
    }

    fclose(fichier);
    printf("Chargement termine !\n");
}