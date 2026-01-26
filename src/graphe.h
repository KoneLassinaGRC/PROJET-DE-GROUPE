#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- DÉFINITION DES STRUCTURES Imposées ---

// 1. L'Arête (Le lien entre deux nœuds)
typedef struct Arete {
    int destination;        // ID du nœud vers lequel on va
    float latence;          // Temps de trajet (ms)
    float bande_passante;   // Vitesse (Mbps)
    float cout;            // Prix (fcfz)
    int securite;           // Niveau de sécurité (0-10)
    struct Arete* suivant;  // Pointeur vers la prochaine arête
} Arete;

// 2. Le Nœud (L'ordinateur/Routeur)
typedef struct Noeud {
    int id;                 // Identifiant unique (ex: 0, 1, 2...)
    char nom[50];           // Nom (ex: "Serveur_Paris")
    Arete* aretes;          // Liste de toutes les connexions partant de ce nœud
} Noeud;

// 3. Le Graphe (Le réseau entier)
typedef struct Graphe {
    int nb_noeuds;          // Combien de machines au total ?
    int capacite_max;       // Pour gérer le tableau dynamique (interne)
    Noeud* tableau_noeuds;  // Tableau contenant tous les nœuds
    
} Graphe;

// --- PROTOTYPES DES FONCTIONS ---

// Créer un graphe vide
Graphe* creer_graphe(int nb_noeuds_max);

// Ajouter un nœud (ex: Ajouter "Routeur A")
void ajouter_noeud(Graphe* g, int id, const char* nom);

// Ajouter une arête (ex: Connecter A vers B)
void ajouter_arete(Graphe* g, int src, int dest, float latence, float bp, float cout, int sec);

// Afficher le graphe (pour vérifier que ça marche)
void afficher_graphe(Graphe* g);

// Libérer la mémoire (Très important en C !)
void liberer_graphe(Graphe* g);
void charger_graphe(Graphe* g, const char* nom_fichier);

#endif