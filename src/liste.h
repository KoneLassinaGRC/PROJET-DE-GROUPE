#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>

// Structure d'un élément dans la file (un noeud en attente d'exploration)
typedef struct ElementFile {
    int id_noeud;           // Quel noeud ?
    float cout_total;       // Quelle distance depuis le départ ? (Priorité)
    struct ElementFile* suivant;
} ElementFile;

// Structure de la file (pointeur vers le début)
typedef struct FilePriorite {
    ElementFile* tete;      // Le premier élément est toujours le plus prioritaire (cout le plus bas)
} FilePriorite;

// Prototypes
FilePriorite* creer_file();
int est_vide(FilePriorite* f);
void enfiler(FilePriorite* f, int id_noeud, float cout);
int defiler(FilePriorite* f, float* cout_out); // Renvoie l'ID et stocke le coût dans cout_out
void liberer_file(FilePriorite* f);

#endif