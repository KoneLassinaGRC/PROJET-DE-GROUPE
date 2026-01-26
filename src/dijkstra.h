#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graphe.h"
#include "liste.h"
#include <float.h> // Pour utiliser FLT_MAX (l'infini)

// Trouve et affiche le chemin le plus court
void algorithme_dijkstra(Graphe* g, int id_depart, int id_arrivee);

#endif