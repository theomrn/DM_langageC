#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../includes/mazeGenerator.h"
#include "../includes/mazeSolver.h"
#include "raylib.h"


int main(){
    // define default size of the maze
    int mazeHeigth = 50;
    int mazeWidth = 50;

    // initialize seed for randomness
    srand(time(NULL));

    // initialize the maze
    Maze *maze = NULL;
    maze = initializeMaze(mazeHeigth,mazeWidth);
    generateMaze(maze);
    // uncoment to see the maze in the terminal
    // printf("\nmaze generated : \n");
    // printMaze(maze);
    // printf("\nmaze solver : \n");

    // printMaze(maze);

    // Window initialisation
    const int screenWidth = 800;   // Largeur de la fenêtre
    const int screenHeight = 600; // Hauteur de la fenêtre

    InitWindow(screenWidth, screenHeight, "Fenêtre avec Raylib"); // Initialisation de la fenêtre

    SetTargetFPS(60); // set the fps

    // initialize the parameters of the maze
    const int wallThickness = 1;
    int cellSize = 8;
    const Color wallColor = WHITE;
    const Color cellColor = GREEN;

    Stack *stack = NULL;

    int solving = 0;
    int end = 0;
    Stack *temp = NULL;

    double startTime = 0.0;
    double elapsedTime = 0.0;
    bool timerRunning = false;


    // Main boucle
    while (!WindowShouldClose()) { // while user don't close the window
        BeginDrawing();

        ClearBackground(BLACK); // reset the window to a black one

        DrawText("pour générer un nouveau labyrinthe \n(10x10 = A, 30x30 = Z , 50x50 = E , 100x100 = R ) . \nAppuyez sur S pour le resoudre ", 50, 50, 20, LIGHTGRAY);

        // diferents touch to change the maze and solve it (touch in qwerty but in the game in azerty)
        if (IsKeyPressed(KEY_Q)){
            DrawText("touche A appuyer",20,20,20,LIGHTGRAY);
            mazeHeigth = 10;
            mazeWidth = 10;
            cellSize = 40;
            free(maze);
            maze = initializeMaze(mazeHeigth,mazeWidth);
            generateMaze(maze);
            solving = 0;
            end = 0;
            freeStack(stack);
            stack = NULL;
        }

        if (IsKeyPressed(KEY_W)){
            mazeHeigth = 30;
            mazeWidth = 30;
            cellSize = 13;
            free(maze);
            maze = initializeMaze(mazeHeigth,mazeWidth);
            generateMaze(maze);
            solving = 0;
            end = 0;
            freeStack(stack);
            stack = NULL;
        }

        if (IsKeyPressed(KEY_E)) {
            mazeHeigth = 50;
            mazeWidth = 50;
            cellSize = 8;
            free(maze);
            maze = initializeMaze(mazeHeigth,mazeWidth);
            generateMaze(maze);
            solving = 0;
            end = 0;
            freeStack(stack);
            stack = NULL;
        }

        if (IsKeyPressed(KEY_S)) {
            // solve the maze
            solving = 1;
            timerRunning = true;
            startTime = GetTime();
        }

        if (IsKeyPressed(KEY_R)) {
            solving = false;
            startTime = 0.0;
            mazeHeigth = 100;
            mazeWidth = 100;
            cellSize = 4;
            free(maze);
            maze = initializeMaze(mazeHeigth,mazeWidth);
            generateMaze(maze);
            solving = 0;
            end = 0;
            freeStack(stack);
            stack = NULL;
        }

        if (timerRunning) {
            elapsedTime = GetTime() - startTime;
        }

        if (solving && !end){
            stack = StepByStepBackTrackingSolver(maze,stack,&end);
        }

        if (end) {
            DrawText("Labyrinthe résolu !", 200, 100, 50, GREEN);
            timerRunning = false;
        }

        // print the timmer
        char timerText[50];
        sprintf(timerText, "Time: %.2f s", elapsedTime);
        DrawText(timerText, 10, 10, 20, RAYWHITE);

        // print the maze
        for (int i = 0; i < maze->height; i++) {
            for (int j = 0; j < maze->width; j++) {
                int x = j * cellSize;
                int y = i * cellSize;

                // Dessiner les murs
                if (maze->mazeTab[i][j].north) {
                    DrawRectangle(x + 225, y + 150, cellSize, wallThickness, wallColor); // Mur du haut
                }
                if (maze->mazeTab[i][j].west) {
                    DrawRectangle(x + 225, y + 150, wallThickness, cellSize, wallColor); // Mur de gauche
                }

                // draw in green the cell where the solver think it's the best path
                if (maze->mazeTab[i][j].value[0] == 'x') {
                    DrawRectangle(x + wallThickness + 225, y + wallThickness + 150,
                                  cellSize - wallThickness * 2,
                                  cellSize - wallThickness * 2, cellColor);
                }
            }
        }

        // draw extern wall
        for (int i = 0; i < maze->width; i++) {
            int x = i * cellSize;
            int y = maze->height * cellSize;
            DrawRectangle(x + 225, y - wallThickness + 150, cellSize, wallThickness, wallColor); // Mur du bas
        }
        for (int i = 0; i < maze->height-1; i++) {
            int x = maze->width * cellSize;
            int y = i * cellSize;
            DrawRectangle(x - wallThickness + 225, y + 150, wallThickness, cellSize, wallColor); // Mur de droite
        }

        EndDrawing();
    }

    // clear the memory and close the window
    CloseWindow();
    free(maze);
    freeStack(stack);
    return EXIT_SUCCESS;
}
