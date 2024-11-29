#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"
#include "mazeGenerator.h"

typedef struct _Stack{
    Cell *cell;
    struct _Stack *next;
} Stack;

void push(Stack **stack, Cell *cell);

Cell *pop(Stack **stack);

int empty(Stack *stack);

void freeStack(Stack *stack);

void removeWall(Cell *current, Cell *neighbor, int direction);

int chooseRandomDirection(int unvisitedDirection[]);

void generateMaze(Maze *maze);

#endif