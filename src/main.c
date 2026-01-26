#include "graphe.h"
#include "dijkstra.h"
#include "bellman.h"
#include "securite.h"
#include "backtrack.h"

void afficher_menu() {
    printf("\n=== NETFLOW OPTIMIZER v1.5 ===\n"); // Version en fonction de l'implémention des 5 algorithmes
    printf("1. Charger le reseau depuis 'reseau.txt'\n");
    printf("2. Afficher la topologie\n");
    printf("3. Calculer chemin (Dijkstra)\n");
    printf("4. Calculer chemin (Bellman-Ford)\n");
    printf("5. Calculer chemin sous contraintes (Backtracking)\n");
    printf("6. Analyse de Securite (Cycles)\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

int main() {
    Graphe* reseau = creer_graphe(100); // Représente la taille de notre réseau, modifiable au besoin
    int choix;
    int depart, arrivee;
    float bp, cout_max;

    // Chargement automatique au démarrage pour gagner du temps
    charger_graphe(reseau, "reseau.txt"); 

    do {
        afficher_menu();
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                // Pour recharger si besoin
                liberer_graphe(reseau);
                reseau = creer_graphe(100);
                charger_graphe(reseau, "reseau.txt");
                break;
            case 2:
                afficher_graphe(reseau);
                break;
            case 3:
                printf("Noeud de depart ID : "); scanf("%d", &depart);
                printf("Noeud d'arrivee ID : "); scanf("%d", &arrivee);
                algorithme_dijkstra(reseau, depart, arrivee);
                break;
            case 4:
                printf("Noeud de depart ID : "); scanf("%d", &depart);
                printf("Noeud d'arrivee ID : "); scanf("%d", &arrivee);
                algorithme_bellman_ford(reseau, depart, arrivee);
                break;
            case 5:
                printf("Depart : "); scanf("%d", &depart);
                printf("Arrivee : "); scanf("%d", &arrivee);
                printf("Bande passante min (Mbps) : "); scanf("%f", &bp);
                printf("Cout max : "); scanf("%f", &cout_max);
                rechercher_chemin_contraintes(reseau, depart, arrivee, bp, cout_max);
                break;
            case 6:
                detecter_cycles(reseau);
                break;
            case 0:
                printf("Fermeture...\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    liberer_graphe(reseau);
    return 0;
}