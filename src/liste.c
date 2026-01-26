#include "liste.h"

// Création d'une file vide
FilePriorite* creer_file() {
    FilePriorite* f = (FilePriorite*)malloc(sizeof(FilePriorite));
    if (f) f->tete = NULL;
    return f;
}

// Vérifie si la file est vide
int est_vide(FilePriorite* f) {
    return (f == NULL || f->tete == NULL);
}

// Insertion triée (C'est le secret de la file de priorité !)
// On insère de façon à ce que le coût le plus faible soit toujours en tête.
void enfiler(FilePriorite* f, int id_noeud, float cout) {
    ElementFile* nouvel_element = (ElementFile*)malloc(sizeof(ElementFile));
    nouvel_element->id_noeud = id_noeud;
    nouvel_element->cout_total = cout;
    nouvel_element->suivant = NULL;

    // Cas 1 : La file est vide OU le nouvel élément est plus prioritaire que la tête
    if (f->tete == NULL || cout < f->tete->cout_total) {
        nouvel_element->suivant = f->tete;
        f->tete = nouvel_element;
        return;
    }

    // Cas 2 : On cherche la bonne place dans la liste
    ElementFile* courant = f->tete;
    while (courant->suivant != NULL && courant->suivant->cout_total <= cout) {
        courant = courant->suivant;
    }

    // On insère après 'courant'
    nouvel_element->suivant = courant->suivant;
    courant->suivant = nouvel_element;
}

// Récupère et supprime l'élément le plus prioritaire (la tête)
int defiler(FilePriorite* f, float* cout_out) {
    if (est_vide(f)) return -1; // Code d'erreur

    ElementFile* a_supprimer = f->tete;
    int id = a_supprimer->id_noeud;
    
    // Si l'utilisateur veut récupérer le coût, on le remplit
    if (cout_out != NULL) *cout_out = a_supprimer->cout_total;

    f->tete = a_supprimer->suivant;
    free(a_supprimer);
    return id;
}

// Nettoyage
void liberer_file(FilePriorite* f) {
    while (!est_vide(f)) {
        defiler(f, NULL);
    }
    free(f);
}