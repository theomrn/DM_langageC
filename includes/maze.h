#ifndef MAZE_H
#define MAZE_H

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

Maze* initializeMaze(Maze *maze,int mazeHeight,int mazeWidth);

void printMaze(Maze *maze);

#endif