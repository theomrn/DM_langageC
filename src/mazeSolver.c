#include <stdlib.h>
#include <stdio.h>
#include "../includes/maze.h"
#include "../includes/mazeGenerator.h"

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