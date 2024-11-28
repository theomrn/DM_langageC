#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

const int mazeHeight = 10; // hauteur
const int mazeWidht = 10; // largeur

/*
Define cell of the maze
1 if wall 0 if not
x,y are the coordonates of the cell
*/
typedef struct {
    int north;
    int west;
    char *value;
    int visited;
    int x;
    int y;
} Cell;


typedef struct {
    int width;
    int height;
    Cell **mazeTab;
} Maze;

typedef struct _Stack{
    Cell *cell;
    struct _Stack *next;
} Stack;

Maze* initializeMaze(Maze *maze);

void printMaze(Maze *maze);

void push(Stack **stack,Cell *cell);

Cell *pop(Stack **stack);

int empty(Stack *stack);

void freeStack(Stack *stack);

void removeWall(Cell *current, Cell *neighbor, int direction);

int chooseRandomDirection(int unvisitedDirection[]);

void generateMaze(Maze *maze);

#endif