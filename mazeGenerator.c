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
    int west;
    char *value;
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
        int index;
        for (int i = 0;i<mazeWidht;i++){
            for (int j = 0;j<mazeHeight;j++){
                index = i*mazeWidht+j;
                maze->mazeTab[index] = (Cell *)malloc(sizeof(Cell));
                if (!maze->mazeTab[index]) {
                    perror("erreur alocation mazeCell");
                    exit(1);
                }
                maze->mazeTab[index]->north = maze->mazeTab[index]->west = 1;
                maze->mazeTab[index]->value = " ";
            }
        }
    }

    return maze;
}

void printMaze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        // Top line north direction
        for (int j = 0; j < maze->width; j++) {
            int index = i * maze->width + j;
            printf("%s",maze->mazeTab[i*mazeWidht+j]->value);
            printf(maze->mazeTab[index]->north == 1 ? "_" : " ");
        }
        printf("\n");

        // west line , value
        for (int j = 0; j < maze->width; j++) {
            int index = i * maze->width + j;
            printf(maze->mazeTab[index]->west == 1 ? "|" : " "); // west wall
            printf("%s",maze->mazeTab[i*mazeWidht+j]->value);  // space
        }
        printf("|\n");  // Right wall, end of the line

        // south line
        if (i == maze->height - 1) {
            for (int j = 0; j < maze->width; j++) {
                int index = i * maze->width + j;
                printf(" _");
            }
            printf("\n");
        }
    }
}


int main(){
    Maze *maze;
    maze = initializeMaze(maze);
    printMaze(maze);



    return 0;
}