#ifndef BELLMAN_H
#define BELLMAN_H

#include "graphe.h"
#include <float.h>

// Algorithme de Bellman-Ford
// Retourne 1 si un chemin est trouvé et qu'il n'y a pas de cycle négatif
// Retourne 0 s'il y a un cycle négatif (Anomalie)
int algorithme_bellman_ford(Graphe* g, int id_depart, int id_arrivee);

#endif