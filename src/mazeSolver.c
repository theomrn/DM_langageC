#include <stdlib.h>
#include <stdio.h>
#include "../includes/mazeSolver.h"

void printStack(Stack *stack){
    Stack *cell = stack;
    int i = 0;
    while (cell->next){
        printf("   index : %d \n",i);
        printf("   visited : %d \n",cell->cell->visited);
        cell = cell->next;
        i++;
    }
}

/*
 * solve the maze using backtracking algorithm
 * input : maze
 * output : Ø
 */
void backTrackingSolver(Maze *maze){
    int i = 0, j = 0;
    int unvisitedDirection[5] = {0,0,0,0,0};
    int direction;
    maze->mazeTab[i][j].visited = 1;
    Stack *stack = NULL;
    stack = (Stack *)malloc(sizeof(Stack));

    if (!stack){
        perror("erreur stack");
        exit(EXIT_FAILURE);
    }

    push(&stack,&maze->mazeTab[i][j]);
    while ((i != maze->width-1) || (j != maze->height-1)){
        Cell *current = pop(&stack);
        if (current == NULL){
            break;
        }
        i = current->i;
        j = current->j;
        current->value = "x";

        // reset the tab
        unvisitedDirection[0] = unvisitedDirection[1] = unvisitedDirection[2] = unvisitedDirection[3] = unvisitedDirection[4] = 0;

        if ((i+1) < maze->height && (maze->mazeTab[i+1][j].visited == 0) && (maze->mazeTab[i+1][j].north == 0)){
            // check if the under cell  actual cell is unvisited
            unvisitedDirection[0] = 1;
            unvisitedDirection[4]++;
        }
        if ((i > 0) && (maze->mazeTab[i-1][j].visited == 0) && (maze->mazeTab[i][j].north == 0)){
            // check if the top cell actual cell is unvisited
            unvisitedDirection[1] = 1;
            unvisitedDirection[4]++;
        }
        if ((j+1) < maze->height && (maze->mazeTab[i][j+1].visited == 0) && (maze->mazeTab[i][j+1].west == 0)){
            // check if the right cell actual cell is unvisited
            unvisitedDirection[2] = 1;
            unvisitedDirection[4]++;
        }
        if ((j > 0) && (maze->mazeTab[i][j-1].visited == 0) && (maze->mazeTab[i][j].west == 0)){
            // check if the left cell actual cell is unvisited
            unvisitedDirection[3] = 1;
            unvisitedDirection[4]++;
        }
        if (unvisitedDirection[4] > 0) {
            push(&stack, current);  // Remettre la cellule actuelle
            // Choisissez une direction aléatoire valide
            direction = chooseRandomDirection(unvisitedDirection);

            Cell *neighbor = NULL;
            switch (direction) {
                case 0: // Bas
                    neighbor = &maze->mazeTab[++i][j];
                    break;
                case 1: // Haut
                    neighbor = &maze->mazeTab[--i][j];
                    break;
                case 2: // Droite
                    neighbor = &maze->mazeTab[i][++j];
                    break;
                case 3: // Gauche
                    neighbor = &maze->mazeTab[i][--j];
                    break;
                default:
                    break;
            }

            neighbor->visited = 1;
            push(&stack, neighbor); // Empilez la cellule voisine
        }
        else {
            current->value = " ";
        }
    }
    maze->mazeTab[maze->height-1][maze->width-1].value = "x";
    freeStack(stack); // free memory allocated for the stack
}

Stack* StepByStepBackTrackingSolver(Maze *maze, Stack *stack, int *end) {
    int i, j;
    Cell *current;

    // Initialisation de la pile si elle est NULL (premier appel)
    if (!stack) {
        stack = (Stack *)malloc(sizeof(Stack));
        if (!stack) {
            perror("Erreur d'allocation de la pile");
            exit(EXIT_FAILURE);
        }
        stack->next = NULL; // Initialiser la pile vide
        current = &maze->mazeTab[0][0]; // Commencer au point de départ
        i = 0;
        j = 0;
        current->visited = 1; // Marquer comme visitée
        current->value = "x"; // Marquer comme faisant partie du chemin
        push(&stack, current); // Ajouter la cellule de départ à la pile
        return stack; // Retourner après cette première étape
    }

    // Sinon, dépiler pour obtenir la cellule courante
    current = pop(&stack);
    if (!current) {
        *end = 1; // Si la pile est vide, la résolution est terminée
        return stack;
    }

    i = current->i;
    j = current->j;

    // Vérifier si on a atteint la fin du labyrinthe
    if (i == maze->height - 1 && j == maze->width - 1) {
        *end = 1; // Marquer que la fin est atteinte
        current->value = "x"; // Marquer la cellule finale
        return stack;
    }

    // Vérifier les voisins non visités
    int unvisitedDirection[5] = {0, 0, 0, 0, 0};
    if ((i + 1) < maze->height && !maze->mazeTab[i + 1][j].visited && !maze->mazeTab[i + 1][j].north) {
        unvisitedDirection[0] = 1; // Bas
        unvisitedDirection[4]++;
    }
    if (i > 0 && !maze->mazeTab[i - 1][j].visited && !maze->mazeTab[i][j].north) {
        unvisitedDirection[1] = 1; // Haut
        unvisitedDirection[4]++;
    }
    if ((j + 1) < maze->width && !maze->mazeTab[i][j + 1].visited && !maze->mazeTab[i][j + 1].west) {
        unvisitedDirection[2] = 1; // Droite
        unvisitedDirection[4]++;
    }
    if (j > 0 && !maze->mazeTab[i][j - 1].visited && !maze->mazeTab[i][j].west) {
        unvisitedDirection[3] = 1; // Gauche
        unvisitedDirection[4]++;
    }

    // Si des voisins non visités existent
    if (unvisitedDirection[4] > 0) {
        // Choisir une direction aléatoire parmi les directions possibles
        int direction = chooseRandomDirection(unvisitedDirection);
        Cell *neighbor = NULL;

        // Déterminer la cellule voisine en fonction de la direction
        switch (direction) {
            case 0: // Bas
                neighbor = &maze->mazeTab[i + 1][j];
                break;
            case 1: // Haut
                neighbor = &maze->mazeTab[i - 1][j];
                break;
            case 2: // Droite
                neighbor = &maze->mazeTab[i][j + 1];
                break;
            case 3: // Gauche
                neighbor = &maze->mazeTab[i][j - 1];
                break;
        }

        // Marquer la cellule voisine comme visitée et empiler
        if (neighbor) {
            neighbor->visited = 1;
            neighbor->value = "x"; // Marquer comme faisant partie du chemin
            push(&stack, current);  // Remettre la cellule actuelle
            push(&stack, neighbor); // Empiler la cellule voisine
        }
    } else {
        // Aucun voisin non visité, retirer cette cellule du chemin valide
        current->value = " "; // Effacer la marque du chemin
    }

    return stack; // Retourner l'état actuel de la pile
}
