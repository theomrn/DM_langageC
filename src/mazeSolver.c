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

void backTrackingSolver(Maze *maze){
    int i = 0, j = 0;
    int index = 0;
    for (i=0;i<maze->height;i++){
        for (j=0;j<maze->width;j++){
            index = i * maze->height + j;
            maze->mazeTab[index]->visited = 0;
        }
    }
    index = i = j = 0;
    int unvisitedDirection[5] = {0,0,0,0,0};
    int direction;
    maze->mazeTab[index]->visited = 1;
    Stack *stack = NULL;
    stack = (Stack *)malloc(sizeof(Stack));
    if (!stack){
        exit(EXIT_FAILURE);
    }
    stack->next = NULL;
    push(&stack,maze->mazeTab[index]);
    int finalIndex = (maze->height - 1) * maze->width + (maze->width - 1);
    while (index != finalIndex && stack->cell){
        // printf("Coo = %d  \n",index);
        Cell *current = pop(&stack);
        if (!current) exit(EXIT_FAILURE);
        current->value = "x";
        i = current->x;
        j = current->y;
        index = i * maze->width + j;

        // reset the tab
        unvisitedDirection[0] = unvisitedDirection[1] = unvisitedDirection[2] = unvisitedDirection[3] = unvisitedDirection[4] = 0;
        if (i+1 < maze->height && maze->mazeTab[(i+1) * maze->width + j]->visited == 0 && maze->mazeTab[(i+1) * maze->width + j]->north == 0){
            // check if the under cell  actual cell is unvisited
            unvisitedDirection[0] = 1;
            unvisitedDirection[4]++;
        }
        if (i-1 >= 0 && maze->mazeTab[(i-1) * maze->width + j]->visited == 0 && maze->mazeTab[i * maze->width + j]->north == 0){
            // check if the top cell actual cell is unvisited
            unvisitedDirection[1] = 1;
            unvisitedDirection[4]++;
        }
        if (j+1 < maze->width && maze->mazeTab[i * maze->width + j+1]->visited == 0 && maze->mazeTab[i * maze->width + j+1]->west == 0){
            // check if the right cell actual cell is unvisited
            unvisitedDirection[2] = 1;
            unvisitedDirection[4]++;
        }
        if (j-1 >= 0 && maze->mazeTab[i * maze->width + j-1]->visited == 0 && maze->mazeTab[i * maze->width + j]->west == 0){
            // check if the left cell actual cell is unvisited
            unvisitedDirection[3] = 1;
            unvisitedDirection[4]++;
        }
        /*
        for (int a=0;a<4;a++){
            printf("direction %d\n",unvisitedDirection[a]);
        }
         */
        if (unvisitedDirection[4] > 0) {
            // choose a random valid direction
            direction = chooseRandomDirection(unvisitedDirection);

            Cell *neighbor = NULL;
            switch (direction) {
                case 0: // bottom
                    neighbor = maze->mazeTab[(i + 1) * maze->width + j];
                    break;
                case 1: // top
                    neighbor = maze->mazeTab[(i - 1) * maze->width + j];
                    break;
                case 2: // right
                    neighbor = maze->mazeTab[i * maze->width + (j + 1)];
                    break;
                case 3: // left
                    neighbor = maze->mazeTab[i * maze->width + (j - 1)];
                    break;
                default:
                    break;
            }

            neighbor->visited = 1;
            push(&stack, current);  // push actual cell
            push(&stack, neighbor); // push neighbor cell
            i = neighbor->x;
            j = neighbor->y;
            //printf("stack : \n");
            //printStack(stack);
        }
        else {
            //current->value = " ";
            current = pop(&stack);
            i = current->x;
            j = current->y;
            printf("stack poped : \n");
            printStack(stack);
        }
    }
    freeStack(stack); // free memory allocated for the stack
}