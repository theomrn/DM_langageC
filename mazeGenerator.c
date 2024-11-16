#include <stdio.h>
#include <stdlib.h>

const int mazeHeight = 10; // hauteur
const int mazeWidht = 10; // largeur

/* 
Define cell of the maze
1 if wall 0 if not
x,y are the coordonates of the cell
*/
typedef struct{
    int north;
    int south;
    int est;
    int west;
} Cell;


typedef struct {
    int width;
    int height;
    Cell **mazeTab;
} Maze;


/*
create and alocate matrice for the maze and initialize every cell with all wall at 1
input : Width and Height of the maze
output : triple pointer of the alocated memory of the maze
*/
Maze* initializeMaze(Maze *maze){
    maze = (Maze *)malloc(sizeof(Maze));
    if (!maze){
        exit(1);
    }
    else {
        maze->height = mazeHeight;
        maze->width = mazeWidht;
        Cell **newTab = (Cell **)malloc((maze->width * maze->height) * sizeof(Cell *));
        if (!newTab) {
            perror("erreur alocation mazeTab");
            free(maze);
            exit(1);
        }
        maze->mazeTab = newTab;
        for (int i = 0;i<mazeWidht;i++){
            for (int j = 0;j<mazeHeight;j++){
                int index = i*mazeHeight+j;
                maze->mazeTab[index] = (Cell *)malloc(sizeof(Cell));
                if (!maze->mazeTab[index]) {
                    perror("erreur alocation mazeCell");
                    exit(1);
                }
                maze->mazeTab[index]->est = maze->mazeTab[index]->north = maze->mazeTab[index]->south = maze->mazeTab[index]->west = 1;
            }
        }
    }

    return maze;
}

int main(){
    Maze *maze;
    maze = initializeMaze(maze);


    return 0;
}