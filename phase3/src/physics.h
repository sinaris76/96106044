#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.


void makegraph(const Map *map,int* adj);

void insert_queue(int vertex,int* front,int* rear, int queue[10000][3],int root,int mainroot);

int delete_queue(int *front,int queue[10000][3]);

int BFS(int root, int destin, int *edges, const Map* map,int *levelcount );

int isEmpty_queue(int front, int rear);
Direction decidePacman(const Map* map, Pacman* pacman, Action action);

Direction decideGhost(const Map* map, Ghost* ghost,Pacman* pacman, Ghost* blinky);
#endif