#include <stdlib.h>
#include <stdio.h>
#include "../includes/maze.h"

/*
create and alocate matrice for the maze and initialize every cell with all wall at 1
input : Width and Height of the maze
output : triple pointer of the alocated memory of the maze
*/
Maze* initializeMaze(int mazeHeight,int mazeWidth){
    Maze *maze = (Maze *)malloc(sizeof(Maze));
    if (!maze){
        exit(1);
    }
    else {
        maze->height = mazeHeight;
        maze->width = mazeWidth;
        Cell **newTab = (Cell **)malloc((maze->width * maze->height) * sizeof(Cell *));
        if (!newTab) {
            perror("erreur alocation mazeTab");
            free(maze);
            exit(1);
        }
        maze->mazeTab = newTab;
        int index;
        for (int i = 0;i<maze->width;i++){
            for (int j = 0;j<mazeHeight;j++){
                index = i*maze->width+j;
                maze->mazeTab[index] = (Cell *)malloc(sizeof(Cell));
                if (!maze->mazeTab[index]) {
                    perror("erreur alocation mazeCell");
                    exit(1);
                }
                maze->mazeTab[index]->north = maze->mazeTab[index]->west = 1;
                maze->mazeTab[index]->value = " ";
                maze->mazeTab[index]->visited = 0;
                maze->mazeTab[index]->x = i;
                maze->mazeTab[index]->y = j;
            }
        }
        maze->mazeTab[0]->west = 0;
    }

    return maze;
}

void printMaze(Maze *maze){
    int i = 0,j = 0;
    int index = i * maze->width + j;
    for (i=0;i<maze->height;i++){
        for (int k=0;k<2;k++){
            for (j=0;j<maze->width;j++){
                index = i * maze->width + j;
                if (k == 0){
                    printf((maze->mazeTab[index]->north)? "-+--" : "   ");
                }
                else{
                    printf((maze->mazeTab[index]->west)? " | " : "   ");
                    printf("%s",maze->mazeTab[index]->value);
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