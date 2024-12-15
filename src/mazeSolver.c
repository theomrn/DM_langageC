#include <stdlib.h>
#include <stdio.h>
#include "../includes/mazeSolver.h"

/*
 * solve the maze using backtracking algorithm
 * input : maze not solve
 * output : no output but change the maze adding x in the path to the solution : this function return the maze with the solution in one call
 * not used in the program but can be use if you don't want to see the program solving the maze and see just the result
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

/*
 * fucntion that solve the maze : use the same algorithm than the previous fucntion but does it one step at the time
 * so it get a stack in input and output
 * it also has a "end" parameter to knwow when the program is solved
*/
Stack* StepByStepBackTrackingSolver(Maze *maze, Stack *stack, int *end) {
    int i, j;
    Cell *current;

    // initialisation of the stack (first call)
    if (!stack) {
        stack = (Stack *)malloc(sizeof(Stack));
        if (!stack) {
            perror("Erreur d'allocation de la pile");
            exit(EXIT_FAILURE);
        }
        stack->next = NULL;
        current = &maze->mazeTab[0][0]; // start at 0 0
        i = 0;
        j = 0;
        current->visited = 1;
        current->value = "x";
        push(&stack, current);
        return stack;
    }

    // else pop the stack
    current = pop(&stack);
    if (!current) {
        *end = 1;
        return stack;
    }

    i = current->i;
    j = current->j;

    // check if the maze is solved
    if (i == maze->height - 1 && j == maze->width - 1) {
        *end = 1;
        current->value = "x"; // mark the last cell
        return stack;
    }

    // chzeck unvisited neighbor
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

    // if there is univisited neighbor
    if (unvisitedDirection[4] > 0) {
        // choose one possible direction
        int direction = chooseRandomDirection(unvisitedDirection);
        Cell *neighbor = NULL;

        // choose a direction
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

        if (neighbor) {
            neighbor->visited = 1;
            neighbor->value = "x";
            push(&stack, current);
            push(&stack, neighbor);
        }
    } else {
        // no unvisited neighbor : unmarked the cell of the path
        current->value = " ";
    }

    return stack;
}
