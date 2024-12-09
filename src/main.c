#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../includes/mazeGenerator.h"
#include "../includes/mazeSolver.h"
#include "raylib.h"


int main(){
    int mazeHeigth = 50;
    int mazeWidth = 50;
    srand(time(NULL));

    Maze *maze = NULL;
    maze = initializeMaze(mazeHeigth,mazeWidth);
    generateMaze(maze);
    // printf("\nmaze generated : \n");
    // printMaze(maze);
    // printf("\nmaze solver : \n");

    // printMaze(maze);

    // Initialisation
    const int screenWidth = 800;   // Largeur de la fenêtre
    const int screenHeight = 600; // Hauteur de la fenêtre

    InitWindow(screenWidth, screenHeight, "Fenêtre avec Raylib"); // Initialisation de la fenêtre

    SetTargetFPS(60); // Définit le nombre d'images par seconde (FPS)
    const int wallThickness = 1; // Épaisseur des murs
    const int cellSize = 8;
    const Color wallColor = WHITE; // Couleur des murs
    const Color cellColor = GREEN; // Couleur pour les cellules contenant "x"


    // Boucle principale
    while (!WindowShouldClose()) { // Tant que l'utilisateur ne ferme pas la fenêtre
        // Début du dessin
        BeginDrawing();

        ClearBackground(BLACK); // Efface l'écran avec un fond blanc

        DrawText("Appuyez sur ESPACE pour générer un nouveau labyrinthe. \nAppuyez sur S pour le resoudre", 100, 50, 20, LIGHTGRAY); // Texte à l'écran

        // Vérifiez si l'utilisateur appuie sur la barre d'espace
        if (IsKeyPressed(KEY_SPACE)) {
            // Appel de la fonction generateMaze
            free(maze);
            maze = initializeMaze(mazeHeigth,mazeWidth);
            generateMaze(maze);
        }

        if (IsKeyPressed(KEY_S)) {
            // Appel de la fonction generateMaze
            backTrackingSolver(maze);
        }

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

                // Dessiner les cellules avec "x" en vert
                if (maze->mazeTab[i][j].value[0] == 'x') {
                    DrawRectangle(x + wallThickness + 225, y + wallThickness + 150,
                                  cellSize - wallThickness * 2,
                                  cellSize - wallThickness * 2, cellColor);
                }
            }
        }

        // Dessiner les murs extérieurs
        for (int i = 0; i < maze->width; i++) {
            int x = i * cellSize;
            int y = maze->height * cellSize;
            DrawRectangle(x + 225, y - wallThickness + 150, cellSize, wallThickness, wallColor); // Mur du bas
        }
        for (int i = 0; i < maze->height; i++) {
            int x = maze->width * cellSize;
            int y = i * cellSize;
            DrawRectangle(x - wallThickness + 225, y + 150, wallThickness, cellSize, wallColor); // Mur de droite
        }

        // Fin du dessin
        EndDrawing();
    }

    // Fermeture et nettoyage
    CloseWindow(); // Ferme la fenêtre et libère les ressources
    free(maze);
    return 1;
}
