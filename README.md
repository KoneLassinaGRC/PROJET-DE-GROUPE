# NetFlow Optimizer & Security Analyzer
### Projet ALC2101 – Algorithmique et Complexité

## 📌 Description
Ce projet académique consiste à concevoir et implémenter un système
d’optimisation et d’analyse de réseaux informatiques en langage C.

Le réseau est modélisé sous forme de graphe pondéré et permet :
- le calcul de chemins optimaux,
- l’analyse de la sécurité du réseau,
- la gestion de files de paquets,
- la recherche de chemins sous contraintes.

---

## 🎯 Objectifs pédagogiques
- Maîtriser les structures de données (graphes, listes, files)
- Implémenter des algorithmes classiques de graphes
- Analyser la complexité temporelle et spatiale
- Travailler en équipe sur un projet structuré

---

## 🛠️ Fonctionnalités principales
- Représentation du graphe (listes & matrices d’adjacence)
- Algorithmes de routage :
  - Dijkstra
  - Bellman-Ford
- Chemins avec contraintes (backtracking)
- Analyse de sécurité :
  - cycles
  - points d’articulation
  - ponts
  - composantes fortement connexes
- Gestion des files de paquets (file de priorité)

---

## 📁 Organisation du projet
- `src/` : code source
- `docs/` : rapport, présentation et vidéo
- `data/` : fichiers réseau
- `tests/` : tests unitaires

---

## ▶️ Compilation et exécution
```bash
make
./netflow
