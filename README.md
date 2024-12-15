Maze Solver 🧩 </br>
  Ce projet est une application interactive développée en C utilisant la bibliothèque Raylib, permettant de générer, résoudre et visualiser des labyrinthes. Il offre une visualisation pas-à-pas des algorithmes de génération et de résolution de labyrinthes, idéale pour l'apprentissage et la compréhension des algorithmes de backtracking.

<img width="800" alt="Capture d’écran 2024-12-15 à 17 05 11" src="https://github.com/user-attachments/assets/f2aa2db8-33bb-4de1-8b20-d5f113cfab0e" />


</br>
Fonctionnalités 🚀</br>
  Génération aléatoire de labyrinthes de différentes tailles.
  Visualisation interactive de la résolution étape par étape.
  Réinitialisation facile du labyrinthe avec une taille personnalisée.
  Affichage d'un timer pour mesurer le temps de résolution.

</br>
Algorithmes Implémentés 🧠</br>
  1. Génération de Labyrinthe : Algorithme de Backtracking</br>
  L'algorithme de génération de labyrinthe est basé sur une méthode de backtracking récursive :
  Principe :</br>
    Partir d'une cellule initiale et la marquer comme visitée.
    Visiter ses voisins de manière aléatoire en creusant un chemin.
    Revenir en arrière (backtrack) lorsque toutes les cellules voisines ont été visitées.
    Cette méthode garantit un labyrinthe parfait, c'est-à-dire qu'il n'y a aucun cycle et un unique chemin entre deux points.</br>
  2. Résolution de Labyrinthe : Backtracking Étape par Étape</br>
  Principe :</br>
    Utiliser une pile (stack) pour explorer chaque cellule et marquer le chemin en avançant.
    Si un cul-de-sac est rencontré, revenir en arrière en dépilant jusqu'à trouver une cellule non explorée.
    La solution est marquée avec des cellules visitées (x), permettant de visualiser le chemin.</br>
</br>
Librairies Utilisées 📚</br>
  Raylib 🖼️</br>
  Utilisée pour gérer l'affichage graphique du labyrinthe, des cellules et du timer.
  Fournit des fonctionnalités simples pour dessiner, gérer les événements clavier et mettre à jour l'écran.
  Standard C Library 🛠️
  stdlib.h et stdio.h pour la gestion mémoire dynamique, les erreurs et les entrées/sorties.
