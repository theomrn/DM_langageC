#ifndef DM_MAZESOLVER_H
#define DM_MAZESOLVER_H

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"
#include "../includes/mazeGenerator.h"

void backTrackingSolver(Maze *maze);

Stack* StepByStepBackTrackingSolver(Maze *maze,Stack *stack,int *end);

#endif

#endif //DM_MAZESOLVER_H
