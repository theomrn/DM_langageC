#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

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
                maze->mazeTab[index]->value = "x";
                maze->mazeTab[index]->visited = 0;
                maze->mazeTab[index]->x = i;
                maze->mazeTab[index]->y = j;
            }
        }
        maze->mazeTab[0]->west = 0;
    }

    return maze;
}

void printMaze(Maze *maze) {
    int i = 0,j = 0;
    int index = i * maze->width + j;
    for (i=0;i<mazeHeight;i++){
        for (int k=0;k<2;k++){
            for (j=0;j<mazeWidht;j++){
                index = i * maze->width + j;
                if (k == 0){
                    printf((maze->mazeTab[index]->north)? "   _" : "   ");
                }
                else{
                    printf((maze->mazeTab[index]->west)? " | " : "   ");
                    printf("%s",maze->mazeTab[index]->value);
                }
            }
            if (j != (mazeWidht-1) && k!=1){
                printf("\n");
            }
        }
        printf((i!=mazeHeight-1)? " |\n" : "  \n");
    }
    for (j=0;j<mazeWidht;j++){
        printf("   _");
    }
}

/*
 * push cell in the stack
 * input : stack and cell
 * output : Ø
 */
void push(Stack **stack,Cell *cell){
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    if (!newNode) {
        perror("Erreur d'allocation mémoire pour la pile");
        exit(1);
    }
    newNode->cell = cell;
    newNode->next = *stack; // Le nouvel élément pointe vers l'ancien sommet
    *stack = newNode;
}

/*
 * delete first cell of the stack
 * input : stack
 * output : 1 if it worked, 0 if not
 */
Cell *pop(Stack **stack){
    if (!*stack) return NULL;
    Stack *temp = *stack;
    *stack = (*stack)->next;
    Cell *cell = temp->cell;
    free(temp);
    return cell;
}

/*
 * check if the stack is empty
 * input : stack
 * output : 0 if empty, 1 if not
 */
int empty(Stack *stack){
    return stack == NULL;
}

void freeStack(Stack *stack){
    Stack *temp = stack;
    while (stack){
        stack = stack->next;
        free(temp);
        temp = stack;
    }
}

void removeWall(Cell *current, Cell *neighbor, int direction) {
    if (direction == 0) { // Bas
        neighbor->north = 0;
    } else if (direction == 1) { // Haut
        current->north = 0;
    } else if (direction == 2) { // Droite
        neighbor->west = 0;
    } else if (direction == 3) { // Gauche
        current->west = 0;
    }
}

int chooseRandomDirection(int unvisitedDirection[]) {
    int possibleDirections[4];
    int count = 0;
    for (int d = 0; d < 4; d++) {
        if (unvisitedDirection[d]) {
            possibleDirections[count++] = d;
        }
    }
    if (count == 0) return -1; // Pas de direction valide
    return possibleDirections[rand() % count];
}

void generateMaze(Maze *maze){
    int i = 0, j = 0;
    int index = 0;
    int unvisitedDirection[5] = {0,0,0,0,0};
    int direction;
    maze->mazeTab[index]->visited = 1;
    Stack *stack = NULL;
    stack = (Stack *)malloc(sizeof(Stack));
    if (!stack){
        exit(0);
    }
    push(&stack,maze->mazeTab[index]);
    while (!empty(stack)){
        Cell *current = pop(&stack);
        if (current == NULL) {
            break;
        }
        i = current->x;
        j = current->y;
        index = i * mazeWidht + j;

        // reset the tab
        unvisitedDirection[0] = unvisitedDirection[1] = unvisitedDirection[2] = unvisitedDirection[3] = unvisitedDirection[4] = 0;
        if (i+1 < mazeWidht && maze->mazeTab[(i+1) * mazeWidht + j]->visited == 0){
            // check if the under cell  actual cell is unvisited
            unvisitedDirection[0] = 1;
            unvisitedDirection[4]++;
        }
        if (i-1 >= 0 && maze->mazeTab[(i-1) * mazeWidht + j]->visited == 0){
            // check if the top cell actual cell is unvisited
            unvisitedDirection[1] = 1;
            unvisitedDirection[4]++;
        }
        if (j+1 < mazeHeight && maze->mazeTab[i * mazeWidht + j+1]->visited == 0){
            // check if the right cell actual cell is unvisited
            unvisitedDirection[2] = 1;
            unvisitedDirection[4]++;
        }
        if (j-1 >= 0 && maze->mazeTab[i * mazeWidht + j-1]->visited == 0){
            // check if the left cell actual cell is unvisited
            unvisitedDirection[3] = 1;
            unvisitedDirection[4]++;
        }
        if (unvisitedDirection[4] > 0) {
            // Choisissez une direction aléatoire valide
            direction = chooseRandomDirection(unvisitedDirection);

            Cell *neighbor = NULL;
            switch (direction) {
                case 0: // Bas
                    neighbor = maze->mazeTab[(i + 1) * mazeWidht + j];
                    removeWall(current, neighbor, direction);
                    i++;
                    break;
                case 1: // Haut
                    neighbor = maze->mazeTab[(i - 1) * mazeWidht + j];
                    removeWall(current, neighbor, direction);
                    i--;
                    break;
                case 2: // Droite
                    neighbor = maze->mazeTab[i * mazeWidht + (j + 1)];
                    removeWall(current, neighbor, direction);
                    j++;
                    break;
                case 3: // Gauche
                    neighbor = maze->mazeTab[i * mazeWidht + (j - 1)];
                    removeWall(current, neighbor, direction);
                    j--;
                    break;
                default:
                    break;
            }

            neighbor->visited = 1;
            push(&stack, current);  // Remettre la cellule actuelle
            push(&stack, neighbor); // Empilez la cellule voisine
        }
        else {
            current = pop(&stack);
            i = current->x;
            j = current->y;
        }

    }
    freeStack(stack);
}

int main(){
    Maze *maze = NULL;
    maze = initializeMaze(maze);
    printMaze(maze);
    generateMaze(maze);
    printf("\nmaze generated : \n");
    printMaze(maze);
    free(maze);
    return 0;
}