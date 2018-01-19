#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void makegraph(const Map *map, int *adj) {
    int i,j;
    int h=map->height;
    int w=map->width;
    for(i=0;i<w*h;i++){
        for(j=0;j<w*h;j++){
            *(adj+i*10000+j)=0;

        }}
    for(i=0;i<w*h;i++){
        if(map->cells[((i+1)%w+(i/w)*w)%w][((i+1)%w+(i/w)*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i+1)%w+(i/w)*w)=1;
        if(map->cells[((i-1)%w+(i/w)*w)%w][((i-1)%w+(i/w)*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i-1)%w+(i/w)*w)=1;
        if(map->cells[((i+w)-(i+w>=w*h))%w][((i+w)-(i+w>=w*h))/w]!=CELL_BLOCK)
            *(adj+i*10000+(i+w)-(i+w>=w*h)*w*h)=1;
        if(map->cells[((i-w)+(i-w<0)*h*w)%w][((i-w)+(i-w<0)*h*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i-w)+(i-w<0)*h*w)=1;
    }
}

Direction decideGhost(const Map* map, Ghost* ghost) {


}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int intpacmanx=pacman->x/1;
    int intpacmany=pacman->y/1;
    int dir;
    int w=map->width, h=map->height;
    Direction Dir;
    if(pacman->x==intpacmanx && pacman->y==intpacmany ){
        int a=(int)pacman->y+(pacman->dir-2);
        int b= (int)(pacman->x)-(pacman->dir-3);
        if(action==2){
            if (map->cells[(int)(pacman->x)][(int)pacman->y-1+(intpacmany-1<0)*h]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=1;
        }
        else if (action==6){
            if (map->cells[(int)(pacman->x)+1-(intpacmanx+1>=w)*w][(int)(pacman->y)]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=2;
        }
        else if(action==10){
            if (map->cells[(int)(pacman->x)][(int)pacman->y+1-(intpacmany+1>=h)*h]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=3;
        }
        else if(action==14){
            if (map->cells[(int)(pacman->x)-1+(intpacmanx-1<0)*w][(int)pacman->y]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=4;
        }
        else
        if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
            dir=-1;
        else
            dir=pacman->dir;
    }
    Dir=dir;
    return Dir;
}