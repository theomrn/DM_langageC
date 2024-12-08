#include <stdlib.h>
#include <stdio.h>
#include "../includes/maze.h"

/*
create and alocate matrice for the maze and initialize every cell with all wall at 1
input : Width and Height of the maze
output : triple pointer of the alocated memory of the maze
*/
Maze* initializeMaze(Maze *maze,int mazeHeight,int mazeWidth){
    maze = (Maze *)malloc(sizeof(Maze));
    if (!maze){
        perror("erreur maze");
        exit(EXIT_FAILURE);
    }
    else {
        maze->height = mazeHeight;
        maze->width = mazeWidth;
        maze->mazeTab = (Cell **)malloc(maze->height * sizeof(Cell *));
        if (!maze->mazeTab){
            perror("erreur alocation mazeTab");
            exit(EXIT_FAILURE);
        }
        for (int i = 0;i<maze->height;i++){
            maze->mazeTab[i] = (Cell *)malloc(maze->width * sizeof(Cell));
            if (!maze->mazeTab[i]){
                perror("erreur alocation mazeTab");
                exit(EXIT_FAILURE);
            }
            for (int j = 0;j<maze->width;j++){
                maze->mazeTab[i][j].north = 1;
                maze->mazeTab[i][j].west = 1;
                maze->mazeTab[i][j].value = " ";
                maze->mazeTab[i][j].visited = 0;
                maze->mazeTab[i][j].i = i;
                maze->mazeTab[i][j].j = j;
            }
        }
        maze->mazeTab[0][0].west = 0;
    }

    return maze;
}

void printMaze(Maze *maze){
    int i,j,k;
    for (i=0;i<maze->height;i++){
        for (k=0;k<2;k++){
            for (j=0;j<maze->width;j++){
                if (k == 0){
                    printf((maze->mazeTab[i][j].north)? "-+--" : "    ");
                }
                else{
                    printf((maze->mazeTab[i][j].west)? " | " : "   ");
                    printf("%s",maze->mazeTab[i][j].value);
                }
            }
            if (j != (maze->width-1) && k!=1){
                printf("\n");
            }
        }
        printf((i!=maze->height-1)? " |\n" : "  \n");
    }
    for (j=0;j<maze->width;j++){
        printf("----");
    }
}