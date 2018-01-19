#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

void makegraph(const Map *map,int* adj);
Direction decidePacman(const Map* map, Pacman* pacman, Action action);


Direction decideGhost(const Map* map, Ghost* ghost);
#endif