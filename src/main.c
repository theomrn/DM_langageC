#include <stdlib.h>
#include <stdio.h>
#include "../includes/mazeGenerator.h"
#include "../includes/mazeSolver.h"
#include <time.h>

int main(){
    int mazeHeigth = 5;
    int mazeWidth = 5;

    srand(time(NULL));
    Maze *maze = NULL;
    maze = initializeMaze(maze,mazeHeigth,mazeWidth);
    printMaze(maze);
    generateMaze(maze);
    printf("\nmaze generated : \n");
    printMaze(maze);
    // printf("\nmaze solver : \n");
    // backTrackingSolver(maze);
    //printMaze(maze);
    free(maze);
    return 1;
}
