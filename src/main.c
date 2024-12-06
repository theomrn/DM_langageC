#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../includes/mazeGenerator.h"
#include "../includes/mazeSolver.h"

int main(){
    int mazeHeigth = 10;
    int mazeWidth = 10;
    srand(time(NULL));

    Maze *maze = NULL;
    maze = initializeMaze(maze,mazeHeigth,mazeWidth);
    // printMaze(maze);
    generateMaze2(maze);
    printf("\nmaze generated : \n");
    printMaze(maze);
    // printf("\nmaze solver : \n");
    // backTrackingSolver(maze);
    // printMaze(maze);
    free(maze);
    return 1;
}
