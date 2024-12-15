#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/mazeGenerator.h"
#include "../includes/maze.h"

/*
 * push cell in the stack
 * input : stack and cell
 * output : Ø
 */
void push(Stack **stack,Cell *cell){
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    if (!newNode) {
        perror("Erreur d'allocation mémoire pour la pile");
        exit(1);
    }
    newNode->cell = cell;
    newNode->next = *stack; // Le nouvel élément pointe vers l'ancien sommet
    *stack = newNode;
}

/*
 * delete first cell of the stack
 * input : stack
 * output : 1 if it worked, 0 if not
 */
Cell *pop(Stack **stack){
    if (!*stack) return NULL;
    Stack *temp = *stack;
    *stack = (*stack)->next;
    Cell *cell = temp->cell;
    free(temp);
    return cell;
}

/*
 * check if the stack is empty
 * input : stack
 * output : 0 if empty, 1 if not
 */
int empty(Stack *stack){
    return stack == NULL;
}

/*
 * free the memory allocated for the stack
 * input : stack
 * output : Ø
 */
void freeStack(Stack *stack){
    Stack *temp = stack;
    while (stack){
        stack = stack->next;
        free(temp);
        temp = stack;
    }
}

/*
 * remove the wall between a cell and it's neighbor
 * input : direction
 * output : Ø
 */
void removeWall(Cell *current, Cell *neighbor, int direction){
    if (direction == 0) { // bottom
        neighbor->north = 0;
    } else if (direction == 1) { // top
        current->north = 0;
    } else if (direction == 2) { // right
        neighbor->west = 0;
    } else if (direction == 3) { // left
        current->west = 0;
    }
}

/*
 * choose a random direction
 * input : tab with valid direction
 * output : random valid direction
 */
int chooseRandomDirection(int unvisitedDirection[]){
    int possibleDirections[4];
    for (int j = 0;j<4;j++){
        possibleDirections[j] = 0;
    }
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (unvisitedDirection[i]) {
            possibleDirections[count++] = i;
        }
    }
    if (count == 0) return -1; // no valid direction
    int index = rand() % count;
    int result = possibleDirections[index];
    // printf("%d \n",result);
    return result;
}

/*
 * generate a perfect maze with backtracking algorithm ( only one solution )
 * input : maze
 * output : Ø
 */
void generateMaze(Maze *maze){
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
    while (!empty(stack)){
        Cell *current = pop(&stack);
        if (current == NULL){
            break;
        }
        i = current->i;
        j = current->j;

        // reset the tab
        unvisitedDirection[0] = unvisitedDirection[1] = unvisitedDirection[2] = unvisitedDirection[3] = unvisitedDirection[4] = 0;

        if ((i+1) < maze->height && (maze->mazeTab[i+1][j].visited == 0)){
            // check if the under cell  actual cell is unvisited
            unvisitedDirection[0] = 1;
            unvisitedDirection[4]++;
        }
        if ((i > 0) && (maze->mazeTab[i-1][j].visited == 0)){
            // check if the top cell actual cell is unvisited
            unvisitedDirection[1] = 1;
            unvisitedDirection[4]++;
        }
        if ((j+1) < maze->height && (maze->mazeTab[i][j+1].visited == 0)){
            // check if the right cell actual cell is unvisited
            unvisitedDirection[2] = 1;
            unvisitedDirection[4]++;
        }
        if ((j > 0) && (maze->mazeTab[i][j-1].visited == 0)){
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
                    neighbor->north = 0;
                    break;
                case 1: // Haut
                    neighbor = &maze->mazeTab[--i][j];
                    current->north = 0;
                    break;
                case 2: // Droite
                    neighbor = &maze->mazeTab[i][++j];
                    neighbor->west = 0;
                    break;
                case 3: // Gauche
                    neighbor = &maze->mazeTab[i][--j];
                    current->west = 0;
                    break;
                default:
                    break;
            }

            neighbor->visited = 1;
            push(&stack, neighbor); // Empilez la cellule voisine
        }
    }
    freeStack(stack); // free memory allocated for the stack
    for (i=0;i<maze->height;i++){
        for (j=0;j<maze->width;j++){
            maze->mazeTab[i][j].visited = 0;
        }
    }
}