#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

void makegraph(const Map *map,int* adj);
void insert_queue(int vertex, int *front, int *rear, int queue[10000][3], int root, int mainroot);
int delete_queue(int *front, int (*queue)[3]);
int isEmpty_queue(int front, int rear);
int BFS(int root, int destin, int *edges, const Map *map,int* levelcount);
Direction finddir(const Map *map,int *edges,Ghost *ghost,int node1, int node2,int *level0);
int convert2node(const Map* map,double y,double x,int flag);
int pinkynode(const Map* map,Pacman* pacman,int i);

Direction decidePacman(const Map* map, Pacman* pacman, Action action);


Direction decideGhost(const Map* map, Ghost* ghost, Pacman *pacman, Ghost *blinky);
#endif