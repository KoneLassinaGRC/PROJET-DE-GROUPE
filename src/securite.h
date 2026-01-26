#ifndef SECURITE_H
#define SECURITE_H

#include "graphe.h"

// Détecte s'il y a des boucles de routage dans le réseau
// Retourne 1 si un cycle est détecté, 0 sinon.
int detecter_cycles(Graphe* g);

#endif
