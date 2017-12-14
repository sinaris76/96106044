#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Direction decideGhost(const Map* map, Ghost* ghost) {
    int intghostx,intghosty;
    intghostx=ghost->x/1;
    intghosty=ghost->y/1;
    int dir;
    Direction Dir;
    if(ghost->x==intghostx && ghost->y==intghosty ){
        dir=(int)(((double)rand()/RAND_MAX)*5+1);
        if(dir==5)
            dir=-1;

    if(dir==1) {
        if(ghost->y-1<0 && map->cells[(int)(ghost->x)][map->height-1]==CELL_BLOCK)
            dir=-1;
        else if (map->cells[(int)(ghost->x)][(int)ghost->y-1]==CELL_BLOCK )
            dir=-1;
    }
     if(dir==2) {
         if(ghost->x+1>map->width-1 && map->cells[0][(int)(ghost->y)]==CELL_BLOCK)
             dir=-1;
         else if (map->cells[(int)(ghost->x)+1][(int)(ghost->y)]==CELL_BLOCK )
            dir=-1;
        }
     if(dir==3) {
         if(ghost->y+1>map->height-1 && map->cells[(int)(ghost->x)][0]==CELL_BLOCK)
             dir=-1;
         else if (map->cells[(int)(ghost->x)][(int)ghost->y+1]==CELL_BLOCK)
            dir=-1;
        }
     if(dir==4) {
         if(ghost->x-1<0 && map->cells[map->width-1][(int)ghost->y]==CELL_BLOCK)
             dir=-1;
         else if (map->cells[(int)(ghost->x)-1][(int)ghost->y]==CELL_BLOCK)
             dir=-1;
        }
        Dir=dir;
        return Dir;

}}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int intpacmanx=pacman->x/1;
    int intpacmany=pacman->y/1;
    int dir;
    Direction Dir;
    if(pacman->x==intpacmanx && pacman->y==intpacmany ){
        if(action==2){
            if(pacman->y-1<0 && map->cells[(int)(pacman->x)][map->height-1]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(map->height-1)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else if (map->cells[(int)(pacman->x)][(int)pacman->y-1]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
            dir=1;
    }
        else if (action==6){
            if(pacman->x+1>map->width-1 && map->cells[0][(int)(pacman->y)]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[0][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else if (map->cells[(int)(pacman->x)+1][(int)(pacman->y)]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=2;
        }
        else if(action==10){
            if(pacman->y+1>map->height-1 && map->cells[(int)(pacman->x)][0]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][0]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else if (map->cells[(int)(pacman->x)][(int)pacman->y+1]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                dir=-1;
                else
                dir=pacman->dir;
            else
                dir=3;
        }
        else if(action==14){
            if(pacman->x-1<0 && map->cells[map->width-1][(int)pacman->y]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[map->width-1][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else if (map->cells[(int)(pacman->x)-1][(int)pacman->y]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=4;
        }
        else
            if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][(int)pacman->y+(pacman->dir-2)]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[(int)(pacman->x)-(pacman->dir-3)][(int)pacman->y]==CELL_BLOCK))
                dir=-1;
            else
              dir=pacman->dir;
    }
    Dir=dir;
    return Dir;
}
